DrawSquares <- function(size, height, index_x, index_y)
{
	ratio = size[1] / size[2]

	ratio_x = (index_x-1) / size[1];
	ratio_y = (index_y-1) / size[2];
	ratio_x2 = (index_x) / size[1];
	ratio_y2 = (index_y) / size[2];

	pos_x_left = -1.0 * ratio + (ratio + 1.0) * ratio_x;
	pos_x_right = -1.0 * ratio + (ratio + 1.0) * ratio_x2;

	pos_y_left = -1.0 + 2.0 * ratio_y;
	pos_y_right = -1.0 + 2.0 * ratio_y2;
	
	# Draw floor plane.
	square <- c( 
	  pos_x_left, pos_y_left, height, 1.0,
	  pos_x_right, pos_y_left, height, 1.0,
	  pos_x_right,  pos_y_right, height, 1.0,
	 pos_x_left,  pos_y_right, height, 1.0
	)

	return (square);
}

CreatePlaneGridDrawingVectors <- function(size)
{
	data = matrix(NA, nrow = 3,  ncol=(size[1] + size[2] + 2)*2, byrow = TRUE)

	index = 1

	ratio = size[1] / size[2]
	
	#Draw floor lines (row).
	for (i in 1:(size[1]+1))
	{
		x_line_pos = (i-1) / size[1] * (1.0 * ratio + 1) - 1 * ratio
		
		data[1,index] = x_line_pos
		data[1, index+1] = x_line_pos

		data[2,index] = -1
		data[2, index+1] = 1

		data[3,index] = 0
		data[3, index+1] = 0

		index <- index + 2
	}

	# Draw floor lines (col).
	for (i in 1:(size[2]+1)) 
	{
		y_line_pos = (i-1) / (size[2]) * (2) - 1

		data[1,index] = -1 * ratio
		data[1, index+1] = 1

		data[2,index] = y_line_pos
		data[2, index+1] = y_line_pos

		data[3,index] = 0
		data[3, index+1] = 0

		index <- index + 2
	}

	return (data)
}

# DrawSquaresWithMiddleAndNbRowCol <- function(size, height, pos_x, pos_y, nRow, nCol)
# {
# 	ratio = size[1] / size[2]
# 	one_square_size_x = 1.0 / (ratio + 1.0)
# 	one_square_size_y = 1.0 / 2.0

# 	delta_x = (one_square_size_x * nRow) * 0.5
# 	delta_y = (one_square_size_y * nCol) * 0.5

# 	pos_x_left = pos_x + delta_x
# 	pos_y_left = pos_y + delta_y


# 	pos_x_right = pos_x - delta_x
# 	pos_y_right = pos_y - delta_y
	
# 	# Draw floor plane.
# 	square <- c( 
# 	  pos_x_left, pos_y_left, height, 1.0,
# 	  pos_x_right, pos_y_left, height, 1.0,
# 	  pos_x_right,  pos_y_right, height, 1.0,
# 	 pos_x_left,  pos_y_right, height, 1.0
# 	)

# 	return (square)
# }

DrawSquaresWithDimensionOfSquare <- function(size, height, 
									 pos_x_left, 
									 pos_x_right, 
									 pos_y_left, 
									 pos_y_right,
									 line_width = 1)
{
	# ratio = size[1] / size[2]
	# one_square_size_x = 1.0 / (ratio + 1.0)
	# one_square_size_y = 1.0 / 2.0

	# delta_x = (one_square_size_x * nRow) * 0.5
	# delta_y = (one_square_size_y * nCol) * 0.5

	# pos_x_left = pos_x + delta_x
	# pos_y_left = pos_y + delta_y


	# pos_x_right = pos_x - delta_x
	# pos_y_right = pos_y - delta_y
	
	# Draw floor plane.
	square = c( 
	  pos_x_left, pos_y_left, height, 1.0,
	  pos_x_right, pos_y_left, height, 1.0,
	  pos_x_right,  pos_y_right, height, 1.0,
	 pos_x_left,  pos_y_right, height, 1.0
	)

	alpha = 0.6
	segments3d(c(pos_x_left, pos_x_left),  c(pos_y_left, pos_y_right), c(height, height), col=rgb(0, 0, 0), lwd=line_width, alpha=alpha)
	segments3d(c(pos_x_right, pos_x_right),  c(pos_y_left, pos_y_right), c(height, height), col=rgb(0, 0, 0), lwd=line_width, alpha=alpha)
	segments3d(c(pos_x_left, pos_x_right), c(pos_y_left, pos_y_left), c(height, height), col=rgb(0, 0, 0), lwd=line_width, alpha=alpha)
	segments3d(c(pos_x_left, pos_x_right), c(pos_y_right, pos_y_right), c(height, height), col=rgb(0, 0, 0), lwd=line_width, alpha=alpha)
	return (square)
}

CreateRowPlaneViewDrawingVectors <- function(info_plane_row, v1, v2, height, z = 0)
{
	data = matrix(NA, nrow = 3,  ncol=6, byrow = TRUE)

	index = 1

	# Vertical line.
	data[1,index] = info_plane_row[v1, 1]
	data[1, index+1] = info_plane_row[v1, 1]

	data[2, index] = 1 + info_plane_row[v1, 3]
	data[2, index+1] = 1 + height

	data[3, index] = z
	data[3, index+1] = z

	index <- index + 2

	# Middle line.
	data[1, index] = info_plane_row[v1, 1]
	data[1, index+1] = info_plane_row[v2, 1]

	data[2, index] = 1.0 + height
	data[2, index+1] = 1.0 + height

	data[3, index] = z
	data[3, index+1] = z

	index <- index + 2

	# Vertical line.
	data[1,index] = info_plane_row[v2, 1]
	data[1, index+1] = info_plane_row[v2, 1]

	data[2, index] = 1 + info_plane_row[v2, 3]
	data[2, index+1] = 1 + height

	data[3, index] = z
	data[3, index+1] = z

	index <- index + 2

	return (data)
}


CreateRowDrawingVectors <- function(info_array, v1, v2, height, col_names, cut_bottom = 0)
{
	data = matrix(NA, nrow = 3,  ncol=length(col_names) * 6, byrow = TRUE)

	index = 1

	for(i in col_names)
	{
		# Vertical line.
		data[1, index] = info_array[v1, i, 1]
		data[1, index+1] = info_array[v1, i, 1]

		data[2, index] = info_array[v1, i, 2]
		data[2, index+1] = info_array[v1, i, 2]

		data[3, index] = info_array[v1, i, 3]
		data[3, index+1] = height

		if(cut_bottom != 0)
		{
			if(data[3, index] < cut_bottom)
			{
				data[3, index] = cut_bottom;
			}
		}

		index <- index + 2

		# Middle line.
		data[1, index] = info_array[v1, i, 1]
		data[1, index+1] = info_array[v2, i, 1]

		data[2, index] = info_array[v1, i, 2]
		data[2, index+1] = info_array[v1, i, 2]

		data[3, index] = height
		data[3, index+1] = height

		index <- index + 2

		# Vertical line.
		data[1, index] = info_array[v2, i, 1]
		data[1, index+1] = info_array[v2, i, 1]

		data[2, index] = info_array[v2, i, 2]
		data[2, index+1] = info_array[v2, i, 2]

		data[3, index] = info_array[v2, i, 3]
		data[3, index+1] = height

		if(cut_bottom != 0)
		{
			if(data[3, index] < cut_bottom)
			{
				data[3, index] = cut_bottom;
			}
		}

		index <- index + 2
	}

	return (data)
}



CreateColPlaneViewDrawingVectors <- function(info_plane_col, v1, v2, height, z = 0)
{
	data = matrix(NA, nrow = 3,  ncol=6, byrow = TRUE)

	index = 1

	# Vertical line.
	data[1,index] = 1.0 + info_plane_col[v1, 3]
	data[1, index+1] = 1 + height

	data[2, index] = info_plane_col[v1, 2]
	data[2, index+1] = info_plane_col[v1, 2]

	data[3, index] = z
	data[3, index+1] = z

	index <- index + 2

	# Middle line.
	data[1, index] = 1.0 + height
	data[1, index+1] = 1.0 + height

	data[2, index] = info_plane_col[v1, 2]
	data[2, index+1] = info_plane_col[v2, 2]

	data[3, index] = z
	data[3, index+1] = z

	index <- index + 2

	# Vertical line.
	data[1,index] = 1.0 + info_plane_col[v2, 3]
	data[1, index+1] = 1 + height

	data[2, index] = info_plane_col[v2, 2]
	data[2, index+1] = info_plane_col[v2, 2]

	data[3, index] = z
	data[3, index+1] = z

	index <- index + 2

	return (data)
}



CreateColDrawingVectors <- function(info_array, v1, v2, height, row_names, cut_bottom = 0)
{
	data = matrix(NA, nrow = 3,  ncol=length(row_names) * 6, byrow = TRUE)

	index = 1

	for(i in row_names)
	{
		# Vertical line.
		data[1,index] = info_array[i, v1, 1]
		data[1, index+1] = info_array[i, v1, 1]

		data[2, index] = info_array[i, v1, 2]
		data[2, index+1] = info_array[i, v1, 2]

		data[3, index] = info_array[i, v1, 3]
		data[3, index+1] = height

		if(cut_bottom != 0)
		{
			if(data[3, index] < cut_bottom)
			{
				data[3, index] = cut_bottom;
			}
		}
		

		index <- index + 2

		# Middle line.
		data[1, index] = info_array[i, v1, 1]
		data[1, index+1] = info_array[i, v1, 1]

		data[2, index] = info_array[i, v1, 2]
		data[2, index+1] = info_array[i, v2, 2]

		data[3, index] = height
		data[3, index+1] = height

		index <- index + 2

		# Vertical line.
		data[1, index] = info_array[i, v2, 1]
		data[1, index+1] = info_array[i, v2, 1]

		data[2, index] = info_array[i, v2, 2]
		data[2, index+1] = info_array[i, v2, 2]

		data[3, index] = info_array[i, v2, 3]
		data[3, index+1] = height

		if(cut_bottom != 0)
		{
			if(data[3, index] < cut_bottom)
			{
				data[3, index] = cut_bottom;
			}
		}

		index <- index + 2
	}

	return (data)
}