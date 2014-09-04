CombineMerges <- function(size, row, col, row_height, col_height)
{
	nMerges = size[1] + size[2] - 2
	data = vector(mode="numeric", length=0)
	k = 1

	# cat("ROW HIEGHT : \n")
	# cat(row_height)

	nRowMerge <- length(row_height)
	nColMerge <- length(col_height)

	index_row = 1
	index_col = 1

	for(i in 1:nMerges)
	{
		# cat("Merge :", row_height[index_row], " and ", col_height[index_col], "\n")
		if(row_height[index_row] < col_height[index_col])
		{
			data[k] = row[index_row, 1]
			data[k+1] = row[index_row, 2]
			data[k+2] = row_height[index_row]
			data[k+3] = 0

			index_row <- index_row + 1

			if(index_row > nRowMerge)
			{
				row_height[index_row-1] <- 10000000.0
				index_row <- index_row - 1
			}

		}
		else
		{
			data[k] = col[index_col, 1]
			data[k+1] = col[index_col, 2]
			data[k+2] = col_height[index_col]
			data[k+3] = 1

			index_col <- index_col + 1

			if(index_col > nColMerge)
			{
				col_height[index_col-1] <- 10000000.0
				index_col <- index_col - 1
			}
		}

		k <- k + 4

	}

	merge_matrix = matrix(data,
   					  nrow = nMerges,
   					  ncol=4,
   					  byrow = TRUE) # fill matrix by rows 

	return(merge_matrix)

}

CombineRowAndColMergeAndHeight <- function(size, row, col, row_height, col_height)
{
	merge_n_row = ((size[1] -1) + (size[2] -1))

	index_row = 1
	index_col = 1
	index_row_two = 1
	index_col_two = 1
	index = 1

	delta = 0
	data = vector(mode="numeric", length=0)

	for(i in 1:(merge_n_row))
	{
		r_height_delta = 0
		
    	if(index_row > (size[1]-1))
		{
			r_height_delta = 1000000
		}

		else
		{
			r_height_delta = row_height[index_row]
		}

		if(index_col > size[2]-1)
		{
			c_height_delta = 10000000;
		}
		else
		{
			c_height_delta = col_height[index_col]
		}
		

		# cat("Test : ", r_height_delta, " and  : ",  c_height_delta, "\n")

		if(r_height_delta < c_height_delta)
		{
			data[index] = row[index_row_two]
			data[index+1] = row[index_row_two+1]
			data[index+2] = row_height[index_row]
			data[index+3] = 0

			index_row <- index_row + 1
			index_row_two <- index_row_two + 2
			index <- index + 4
		}

		else
		{
			data[index] = col[index_col_two]
			data[index+1] = col[index_col_two+1]
			data[index+2] = col_height[index_col]
			data[index+3] = 1

			index_col <- index_col + 1
			index_col_two <- index_col_two + 2
			index <- index + 4
		}
	}

	merge_matrix = matrix(data,
	   					  nrow = merge_n_row,
	   					  ncol=4,
	   					  byrow = TRUE) # fill matrix by rows 

	return(merge_matrix)
}

BiClustering <- function(x, nrow, ncol) 
{
	dyn.load("ClusteringAlgorithm.so")
	# if (!is.numeric(x))
	# {
	#    stop("argument x must be numeric")
	# }	
	m = vector(length=(nrow-1) * 2, mode="numeric")
	h = vector(length=(nrow-1), mode="numeric")

	out <- .C("BiClustering", x = x, 
			  nrow = as.integer(nrow), 
			  ncol = as.integer(ncol),
			  merge = m,
			  height = h)
	return(out)
}	