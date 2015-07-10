DrawPlaneAndGrid <- function(size, line_width = 2)
{
	data = CreatePlaneGridDrawingVectors(size)
	segments3d(data[1, ], data[2, ], data[3, ], col=rgb(0, 0, 0), lwd=line_width, alpha=1.0)
}

DrawSquaresOnPlane <- function(size, height, colors = cm.colors(10, alpha = 1), color_index )
{
	ratio = size[1] / size[2]

	data = matrix(NA, nrow = 3, ncol= size[1] * size[2] * 4)
	vector_colors = vector()

	#cat("\n Matrix nb cols : ", size[1] * size[2] * 4)
	height = 0
	index_i = 1
	index_vec_colors = 1

	for(j in 1:size[1])
	{
		for( i in 1:size[2])
		{
			ratio_x = (j-1) / size[1]
			ratio_y = (i-1) / size[2]
			ratio_x2 = (j) / size[1]
			ratio_y2 = (i) / size[2]

			pos_x_left = -1.0 * ratio + (ratio + 1.0) * ratio_x
			pos_x_right = -1.0 * ratio + (ratio + 1.0) * ratio_x2

			pos_y_left = -1.0 + 2.0 * ratio_y
			pos_y_right = -1.0 + 2.0 * ratio_y2

			data[1, index_i+0] = pos_x_left
			data[1, index_i+1] = pos_x_right
			data[1, index_i+2] = pos_x_right
			data[1, index_i+3] = pos_x_left

			data[2, index_i+0] = pos_y_left
			data[2, index_i+1] = pos_y_left
			data[2, index_i+2] = pos_y_right
			data[2, index_i+3] = pos_y_right

			data[3, index_i+0] = height
			data[3, index_i+1] = height
			data[3, index_i+2] = height
			data[3, index_i+3] = height
			
			index_i <- index_i + 4
			color = as.integer(color_index[j, i])

			vector_colors[index_vec_colors] = colors[color]
			vector_colors[index_vec_colors+1] = colors[color]
			vector_colors[index_vec_colors+2] = colors[color]
			vector_colors[index_vec_colors+3] = colors[color]

			index_vec_colors <- index_vec_colors + 4
		}
	}
	quads3d(data[1, ], data[2, ], data[3, ], col=vector_colors)
}

DrawLegend <- function()
{	
	red_color = c(1.0, 0.0, 0.0)
	yellow_color = c(248.0 / 255.0, 239.0/255.0, 0.0)

	colors = rgb(seq(248.0 / 255.0, 1.0, by=0.0001),
				 seq(239.0/255.0, 0.0, by=-0.0001), 0)

	lines3d(2.0, 0, seq(0, 0.8, by=0.0001), col=colors, lwd=20)
}

MergeTwoRowOnPlaneView <- function(info_plane_row, v1, v2, height, size, color = rgb(0.0, 0.0, 0.0), alpha = 1.0, line_width_2D = 2, z = 0)
{
	data = CreateRowPlaneViewDrawingVectors(info_plane_row, v1, v2, height, z = z);
	segments3d(data[1, ], data[2, ], data[3, ], col=color, lwd=line_width_2D, alpha=alpha)
}

DrawTwoRow <- function(info_array, v1, v2, height, size, col_names, color = rgb(0.0, 0.0, 0.0), alpha = 0.5, line_width = 4, cut_bottom = 0)
{
	data = CreateRowDrawingVectors(info_array, v1, v2, height, col_names, cut_bottom = cut_bottom)
	segments3d(data[1, ], data[2, ], data[3, ], col=color, lwd=line_width, alpha=alpha)
}

MergeTwoColumnOnPlaneView <- function(info_plane_col, v1, v2, height, size, alpha = 1.0, line_width_2D = 2, color = rgb(0.0, 0.0, 0.0), z = 0)
{
	data = CreateColPlaneViewDrawingVectors(info_plane_col, v1, v2, height, z = z);
	segments3d(data[1, ], data[2, ], data[3, ], col=color, lwd=line_width_2D, alpha=alpha)
}


MergeTwoColumn <- function(info_array, v1, v2, height, size, row_names, color = rgb(0.0, 0.0, 0.0), alpha = 0.5, line_width = 4, cut_bottom = 0)
{
	data = CreateColDrawingVectors(info_array, v1, v2, height, row_names, cut_bottom)
	segments3d(data[1, ], data[2, ], data[3, ], col=color, lwd=line_width, alpha=alpha)
}

Draw2DAxes <- function(size, alpha = 1.0, z = 0)
{
	data = matrix(NA, nrow = 3,  ncol=(20*2), byrow = TRUE)
	ratio = size[1]/size[2]
	grid_alpha = alpha


	index_i = 1

	segments3d(c(-1.0 * ratio, -1.0 * ratio), c(1.0, 2.0), c(z, z), col=rgb(0.4, 0.4, 0.4), lwd=1, alpha=grid_alpha)
	segments3d(c(1.0, 1.0), c(1.0, 2.0), c(z, z), col=rgb(0.4, 0.4, 0.4), lwd=1, alpha=grid_alpha)
	segments3d(c(1.0, 2.0), c(1.0, 1.0), c(z, z), col=rgb(0.4, 0.4, 0.4), lwd=1, alpha=grid_alpha)
	segments3d(c(1.0, 2.0), c(-1.0, -1.0), c(z, z), col=rgb(0.4, 0.4, 0.4), lwd=1, alpha=grid_alpha)

	for( v in 1:10)
	{
		data[1, index_i+0] = -1.0 * ratio
		data[1, index_i+1] = 1.0

		data[2, index_i+0] = 1.0 + 0.1 * v
		data[2, index_i+1] = 1.0 + 0.1 * v

		data[3, index_i+0] = z
		data[3, index_i+1] = z
		index_i <- index_i + 2
		# ----------------------------------------------------------
		data[1, index_i+0] = 1.0 + 0.1 * v
		data[1, index_i+1] = 1.0 + 0.1 * v

		data[2, index_i+0] = 1.0
		data[2, index_i+1] = 1.0 - 2.0

		data[3, index_i+0] = z
		data[3, index_i+1] = z
		index_i <- index_i + 2
	}

	segments3d(data[1,], data[2, ], data[3, ] , col=rgb(0.4, 0.4, 0.4), lwd=1, alpha=grid_alpha)
}