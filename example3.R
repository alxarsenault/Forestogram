# library(hclust)
source('Forestogram.R')

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

	# N = 
	for(i in 1:merge_n_row)
	{
		r_height_delta = 0;
		
    	if(index_row > (size[1]-1))
		{
			r_height_delta = 1000000;
		}
		else
		{
			r_height_delta = row_height[index_row];
		}


		
		c_height_delta = 1000000000;

		if(index_col < size[2])
		{
			c_height_delta = col_height[index_col];
		}
		# else
		# {
			
		# }

		

		# test_bool_value = r_height_delta < c_height_delta;
		# print(r_height_delta)
		# print(c_height_delta)

		# print("BOOL")
		# print(test_bool_value)


		if(r_height_delta < c_height_delta)
		{
			data[index] = row[index_row_two]
			data[index+1] = row[index_row_two+1]
			data[index+2] = row_height[index_row]
			data[index+3] = 0

			index_row <- index_row + 1
			index_row_two <- index_row_two + 2
			#delta <- r_height_delta
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
	   					          ncol = 4,
	   					          byrow = TRUE) # fill matrix by rows 

	return(merge_matrix)
}

BiClust <- function(data)
{
	d <- dist(data, method = "euclidean")
	v <- hclust(d, method = "complete")

	row_merge = as.vector(t(v$merge));
	row_order = v$order;
	row_height = v$height;

	# print(row_merge)
	# print(row_height)

	# print(v$merge)

	d2 <- dist(t(data), method = "euclidean")
	v2 <- hclust(d2, method = "complete")

	col_merge = as.vector(t(v2$merge));
	col_order = v2$order;
	col_height = v2$height;

	# print(col_merge)
	# print(col_height)

	info_matrix <- CombineRowAndColMergeAndHeight(dim(data), row_merge, col_merge, row_height, col_height);


	size = dim(data);
	total_length = size[1] + size[2] - 2;
	l_vec = 1:total_length;

	merge_matrix <- info_matrix[l_vec, -c(3, 4)]
	height_vector <- info_matrix[l_vec, -c(1, 2, 4)]
	# height_vector <- height_vector

	rowcol_vector <- info_matrix[l_vec, -c(1, 2, 3)]
	# rowcol_vector <- rowcol_vector


	newList <- list("row_col" = rowcol_vector, 
					"merge" = merge_matrix, 
					"height" = height_vector, 
					"dim" = size,
					"row_order" = row_order,
					"col_order" = col_order);


	# print(newList) 
	# return(test_value);
	# print("INFO_MATRIX")
	# print(v)
	return(newList);
}

Forestogram.plot <- function(data)
{
	clust_info <- BiClust(data)

	Forestogramme(clust_info$dim, 
				  clust_info$merge, 
	              clust_info$height, 
	              clust_info$row_col,
	              data, 
	              clust_info$row_order, 
	              clust_info$col_order,
	              cut_height = 90,
	              draw_cut = TRUE, 
	              draw_side_tree = TRUE, 
	              draw3D = TRUE,
	              draw2D_grid = TRUE,
	              line_width = 2,
	              line_width_2D = 1)
}





library(bclust)
data(gaelle)

# a <- gaelle

# vec_data <- c(12, 2, 3, 4,   #v1
# 			  25, 6, 7, 8,   #v2
# 			  9, 2, 3, 5,   #v3
# 			  1, 2, 1, 2); #v4

# data = matrix(vec_data, nrow = 4, ncol = 4, byrow = TRUE)


Forestogram.plot(gaelle);


# d <- dist(t(a), method = "euclidean")
# v <- hclust(d, method = "complete")
# plot(v);

