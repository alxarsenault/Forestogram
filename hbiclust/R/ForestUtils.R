CreateRowNames <- function(n_row)
{
	v = vector(mode="numeric", length=0)

	for(i in 1:n_row)
	{
		val = toString(-i)
		v[val] = i
	}

	return (v)
}

CreateColNames <- function(n_col)
{
	v = vector(mode="numeric", length=0)

	for(i in 1:n_col)
	{
		val = toString(-i);
		v[val] = n_col - (i - 1);
	}

	return (v)
}

CopieExceptTwoName <- function(s1, s2, vec)
{
	tmp = vector(mode="numeric", length=0)

	for(l in 1:length(vec))
	{
		if(names(vec)[l] != s2 && names(vec)[l] != s1)
		{
			tmp[names(vec)[l]] = vec[names(vec)[l]]
		}
	}

	return(tmp)
}

MergeMatrix <- function(size, data)
{
	merge_n_row = ((size[1] -1) + (size[2] -1))

	merge_matrix = matrix(data,
	   					  nrow = merge_n_row,
	   					  ncol=2,
	   					  byrow = TRUE) # fill matrix by rows 

	return(merge_matrix)
}

# DONE IN CPP (RStudio).
MiddleSquarePoint <- function(row, col, size)
{
	ratio = size[1] / size[2];

	delta = (1.0 * ratio + 1);

	delta_over_size = delta / size[1];

##!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
##!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	x = 1.0 - 1.0 / size[2] * (2 * col - 1.0);
	# x = 1.0 / size[2] * (2 * col - 1.0);
##!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
##!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	y = (row * delta_over_size - 1 * ratio) - 0.5 * delta_over_size;
	# y = 1.0 - y;

	return(c(y, x));
	# return(c(x, y));
}


#----------------------------------------------------
# InfoArray
#----------------------------------------------------
# Size : nrows x ncols x 9
# 1 : Middle point x position.
# 2 : Middle point y position.
# 3 : Middle point z position.
# 4 : Number of row merges.
# 5 : Number of col merges.
# 6 : Square left x position.
# 7 : Square right x position.
# 8 : Square left y position.
# 9 : Square right y position.
#10 : Value.
#----------------------------------------------------
CreateInfoArray <- function(size, data_matrix)
{
	info_array <- array(data = NA, 
						dim = c(size[1], size[2], 10), 
						dimnames = NULL)

	data_matrix_index = 1

	# Row.
	for(j in 1:size[1])
	{
		# Column.
		for(i in 1:size[2])
		{
			point = MiddleSquarePoint(j, i, size);

			ratio = size[1] / size[2]
			ratio_y = (size[2] - i) / size[2]
			ratio_x = (j-1) / size[1]

			ratio_y2 = (size[2] - i + 1) / size[2]
			ratio_x2 = (j) / size[1]

			pos_x_left = -1.0 * ratio + (ratio + 1.0) * ratio_x
			pos_x_right = -1.0 * ratio + (ratio + 1.0) * ratio_x2

			pos_y_left = -1.0 + 2.0 * ratio_y
			pos_y_right = -1.0 + 2.0 * ratio_y2

			##!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			##!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			# pos_y_left = 1.0 - pos_y_left
			# pos_y_right = 1.0 - pos_y_right
			##!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			##!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

			info_array[j, i, 1] = point[1]    # x
			info_array[j, i, 2] = point[2]    # y
			info_array[j, i, 3] = 0 	      # z
			info_array[j, i, 4] = 1           # nb row
			info_array[j, i, 5] = 1           # nb col
			info_array[j, i, 6] = pos_x_left  # x left.
			info_array[j, i, 7] = pos_x_right # x right.
			info_array[j, i, 8] = pos_y_left  # y left.
			info_array[j, i, 9] = pos_y_right # y right.
			info_array[j, i, 10] = data_matrix[data_matrix_index]#data_matrix[j][i] # Value.

			data_matrix_index <- data_matrix_index + 1
		}
	}

	return(info_array)
}

ScaleFromZeroToOne <- function(height_vector)
{
	max = max(height_vector);
	return(height_vector / max);
}