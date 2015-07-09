library(rgl)
#source('ForestGLDraw.R')
#source('ForestDrawingVectors.R')
#source('ForestUtils.R')
#source('ForestRowColPermute.R')
#source('ForestImage.R')

CreatePlaneColors <- function(data, color_range = 10)
{
	plane_colors = 0
	data_min = min(data)
	plane_colors <- data - data_min
	data_max = max(plane_colors)
	plane_colors <- plane_colors / data_max
	plane_colors <- plane_colors * (color_range - 1) + 1

	return (plane_colors)
}

##### COULD BE MADE IN C++ 
UpdateRowInInfoArray <- function(info_array, col_names, v1, v2, i, height_vector)
{
	#--------------------------------------------------------------
	# Resize info_array with new middle points.
	for(k in col_names)
	{
		# Change only x position and height (x and z).
		x_pos = (info_array[v1, k, 1] + info_array[v2, k, 1]) * 0.5

		info_array[v1, k, 1] = x_pos
		info_array[v1, k, 3] = height_vector[i]

		info_array[v1, k, 4] = info_array[v1, k, 4] + info_array[v2, k, 4]

		# Find min and max position.
		if(info_array[v2, k, 6] < info_array[v1, k, 6])
		{
			info_array[v1, k, 6] = info_array[v2, k, 6]  # x left.
		}

		if(info_array[v2, k, 7] > info_array[v1, k, 7])
		{
			info_array[v1, k, 7] = info_array[v2, k, 7]  # x right.
		}

		# Find min and max position.
		if(info_array[v2, k, 8] < info_array[v1, k, 8])
		{
			info_array[v1, k, 8] = info_array[v2, k, 8]  # y left.
		}

		if(info_array[v2, k, 9] > info_array[v1, k, 9])
		{
			info_array[v1, k, 9] = info_array[v2, k, 9]  # y right.
		}


		info_array[v1, k, 10] = (info_array[v1, k, 10] + info_array[v2, k, 10]) * 0.5
	}

	return (info_array)
}

AddRGLTranslationWithRightButton <-function()
{
	#------------------------------------------------
	# Add translation to rgl.
	#------------------------------------------------
	pan3d <- function(button) 
	{
		start <- list()

		begin <- function(x, y) 
		{
			start$userMatrix <<- par3d("userMatrix")
			start$viewport <<- par3d("viewport")
			start$scale <<- par3d("scale")
			start$projection <<- rgl.projection()
			start$pos <<- rgl.window2user( x/start$viewport[3], 1 - y/start$viewport[4], 0.5, 
			                              projection=start$projection)
		}

		update <- function(x, y) 
		{
			xlat <- (rgl.window2user( x/start$viewport[3], 1 - y/start$viewport[4], 0.5,
		                         projection = start$projection) - start$pos)*start$scale
			mouseMatrix <- translationMatrix(xlat[1], xlat[2], xlat[3])
			par3d(userMatrix = start$userMatrix %*% t(mouseMatrix) )
		}

		rgl.setMouseCallbacks(button, begin, update)
		#cat("Callbacks set on button", button, "of rgl device",rgl.cur(),"\n")
	}

	pan3d(2)
}

Forestogramme <- function(size, merge_matrix, 
						  height_vector, 
						  rowcol_vector, 
						  data = 0,
						  row_permutation = 0, 
						  col_permutation = 0,
						  cut_height = 100000,
						  draw_cut = TRUE,
						  draw_side_tree = TRUE,
						  draw3D = TRUE,
						  draw2D_grid = TRUE,
						  line_width = 4,
						  line_width_2D = 4,
						  base_contour_width = 2,
						  cut_base_contour_width = 2)
{
    library(rgl);
	# Start rgl engine.
	open3d(windowRect = c(0, 0, 600, 600) )  
	AddRGLTranslationWithRightButton()

	#rgl.viewpoint(theta = 0, phi = -90)
	#rgl.light( theta = 0, phi = 0, viewpoint.rel = TRUE, ambient = "#FF0000", 
    #       diffuse = "#FFFFFF", specular = "#FFFFFF", x = NULL, y = NULL, z = NULL)

	
	if(draw3D == TRUE)
	{
		rgl.clear()
		rgl.clear("lights")
		rgl.light(theta = 30, phi = 100)
	}
	else
	{
		rgl.clear()
		rgl.clear("lights")
		rgl.light(theta = 0, phi = 50)
		view3d( theta = 0, phi = 0)
	}


	

	#-----------------------------------------------------------------------------
	# PROCESS INPUT.
	#-----------------------------------------------------------------------------
	color_range = 10
	plane_colors = CreatePlaneColors(data, color_range)

	# Normalize height vector.
	height_vector <- ScaleFromZeroToOne(height_vector)

	# Create nodes array. Position in 3D point for each elements in (row * col).
	info_array = CreateInfoArray(size, data)
	info_plane_row = info_array[, 1, ]
	info_plane_col = info_array[1, , ]

	row_names = DoRowPermutation(size, row_permutation) # Row permutation.
	col_names = DoColPermutation(size, col_permutation) # Column permutation.
	row_name_count = 0
	col_name_count = 0

	if(draw_side_tree == TRUE)
	{
		if(draw2D_grid == TRUE)
		{
			Draw2DAxes(size, 0.3)
		}
	}	

	array_size = size
	len = length(height_vector)

	red_color = c(1.0, 0.0, 0.0)
	yellow_color = c(248.0 / 255.0, 239.0/255.0, 0.0)

	# red_color = c(0.0, 1.0, 0.0)
	# yellow_color = c(0.0, 0.0, 1.0)

	#-----------------------------------------------------------------------------
	# DRAW BOTTOM PLAIN AND GRID.
	#-----------------------------------------------------------------------------
	DrawPlaneAndGrid(size, line_width = base_contour_width) # Draw square base and grid.
	DrawSquaresOnPlane(size, 0, cm.colors(color_range + 1, alpha = 0.5), plane_colors)		
		

	# Create tree (All merges).
	for(i in 1:len)
	{
		s1 = toString(merge_matrix[i, 1])
		s2 = toString(merge_matrix[i, 2])

		# Interpolate color.
		color = rgb(yellow_color[1]+height_vector[i]*(red_color[1] - yellow_color[1]), 
					yellow_color[2]+height_vector[i]*(red_color[2] - yellow_color[2]),
					0.0)

		# Interpolate transparence.
		alpha = 0.5 + 0.5 * i / len
		
		# Row.
		if(rowcol_vector[i] == 0)
		{
			# Names of row to merge together.
			v1 = row_names[s1]
			v2 = row_names[s2]
			
			#-----------------------------------------------------------------------------
			# DRAWING ROW MERGE.
			#-----------------------------------------------------------------------------
			if(draw3D == TRUE)
			{
				# Draw row merge on 3D plot.
				DrawTwoRow(info_array, v1, v2, height_vector[i], 
							array_size, col_names, color, alpha, line_width)
			}

			# Draw row merge on 2D plane.
			if(draw_side_tree == TRUE)
			{
				MergeTwoRowOnPlaneView(info_plane_row, v1, v2, 
									   height_vector[i], 
									   array_size, line_width_2D = line_width_2D)
			}

			#-----------------------------------------------------------------------------
			# RESIZE ARRAY SECTION.
			#-----------------------------------------------------------------------------
			# Resize info_array with new middle points.
			info_array <- UpdateRowInInfoArray(info_array, 
											   col_names, v1, v2, i, 
											   height_vector)

			# Resize info_plane_row.
			x_pos = (info_plane_row[v1, 1] + info_plane_row[v2, 1]) * 0.5
			info_plane_row[v1, 1] = x_pos
			info_plane_row[v1, 3] = height_vector[i]
			
			# Increment global row name counter.
			row_name_count <- row_name_count + 1
			
			# Add new row to row names.
			row_names[toString(row_name_count)] = row_names[s1]

			# Copie row_names except the two rows that were merge.
			row_names <- CopieExceptTwoName(s1, s2, row_names)

			# Change array row size.
			array_size[1] <- array_size[1] - 1

		}
		#----------------------------------------------------
		# Col.
		#----------------------------------------------------
		else
		{
			v1 = col_names[s1] 
			v2 = col_names[s2]

			if(draw3D == TRUE)
			{
				MergeTwoColumn(info_array, v1, v2, 
							   height_vector[i], 
							   array_size,
							   row_names, color, alpha, line_width)
			}

			if(draw_side_tree == TRUE)
			{
				MergeTwoColumnOnPlaneView(info_plane_col, v1, v2, 
							   			  height_vector[i], 
							   			  array_size, line_width_2D)
			}


			# Resize info_array with new middle points.
			for(k in row_names)
			{
				y_pos = (info_array[k, v1, 2] + info_array[k, v2, 2]) * 0.5
				info_array[k, v1, 2] = y_pos
				info_array[k, v1, 3] = height_vector[i]

				info_array[k, v1, 5] = info_array[k, v1, 5] + info_array[k, v2, 5]

				# Find min and max position.
				if(info_array[k, v2, 6] < info_array[k, v1, 6])
				{
					info_array[k, v1, 6] = info_array[k, v2, 6]  # x left.
				}

				if(info_array[k, v2, 7] > info_array[k, v1, 7])
				{
					info_array[k, v1, 7] = info_array[k, v2, 7]  # x right.
				}

				# Find min and max position.
				if(info_array[k, v2, 8] < info_array[k, v1, 8])
				{
					info_array[k, v1, 8] = info_array[k, v2, 8]  # y left.
				}

				if(info_array[k, v2, 9] > info_array[k, v1, 9])
				{
					info_array[k, v1, 9] = info_array[k, v2, 9]  # y right.
				}


				info_array[k, v1, 10] = (info_array[k, v1, 10] + info_array[k, v2, 10]) * 0.5
			}

			# Resize info_plane_col.
			y_pos = (info_plane_col[v1, 2] + info_plane_col[v2, 2]) * 0.5
			info_plane_col[v1, 2] = y_pos
			info_plane_col[v1, 3] = height_vector[i]

			# Increment global column name counter.
			col_name_count <- col_name_count + 1

			# Add new row to col names.
			col_names[toString(col_name_count)] = col_names[s1]
	
			col_names <- CopieExceptTwoName(s1, s2, col_names)
	
			array_size[2] <- array_size[2] - 1

		}

		# DRAW CUT PLANE.
		if(draw_cut == TRUE)
		{
			if(i == cut_height)
			{
				height = height_vector[i]

				indices = c(1, 2, 3, 4)

				l = length(row_names) + length(col_names)
				colors = rainbow(l, start = 0.3, end = 0.6)
				color_index = 1
				ratio = size[1] / size[2]
				
				if(draw_side_tree == TRUE)
				{
					# Draw plane line cup on row.
					segments3d(c(-1.0 * ratio, 1.0), c(1.0 + height, 1.0 + height), c(0, 0), col=rgb(1.0, 0, 0), lwd=2, alpha=0.5)
	
					# Draw plane line cup on row.
					segments3d(c(1.0 + height, 1.0 + height), c(-1.0, 1.0), c(0, 0), col=rgb(1.0, 0, 0), lwd=2, alpha=0.5)
				}

				#if(draw3D == TRUE)
				{
					for(n in row_names)
					{
						for(c in col_names)
						{
							square = DrawSquaresWithDimensionOfSquare(size, height, 
															  		  info_array[n, c, 6],
															  		  info_array[n, c, 7],
															  		  info_array[n, c, 8],
															  		  info_array[n, c, 9],
															  		  line_width = cut_base_contour_width)

							shade3d( qmesh3d(square,indices), alpha=0.6, col=colors[color_index])
							color_index <- color_index + 1
						}
					}
				}
			}
		}

		#snapshot3d("Test.png")
	}


}




