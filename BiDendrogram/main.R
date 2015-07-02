source("r_source/SimpleExample.R")

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

	d2 <- dist(t(data), method = "euclidean")
	v2 <- hclust(d2, method = "complete")

	col_merge = as.vector(t(v2$merge));
	col_order = v2$order;
	col_height = v2$height;

	info_matrix <- CombineRowAndColMergeAndHeight(dim(data), 
												  row_merge, 
												  col_merge, 
												  row_height, 
												  col_height);

	size = dim(data);
	total_length = size[1] + size[2] - 2;
	l_vec = 1:total_length;

	merge_matrix <- info_matrix[l_vec, -c(3, 4)]
	height_vector <- info_matrix[l_vec, -c(1, 2, 4)]
	rowcol_vector <- info_matrix[l_vec, -c(1, 2, 3)]

	newList <- list("row_col" = rowcol_vector, 
					"merge" = merge_matrix, 
					"height" = height_vector, 
					"dim" = size,
					"row_order" = row_order,
					"col_order" = col_order);

	return(newList);
}

DrawBottomRect <- function(size, size_ratio)
{
	col_pallet = heat.colors(10, alpha = 1);

	for(j in seq(0, size[1] - 1))
	{
		y_pos_bottom = (j / size[1]) * size_ratio[1];
		y_pos_top = ((j+1) / size[1]) * size_ratio[1];

		for(i in seq(0, size[2] - 1))
		{
			x_pos_left = (i / size[2]) * size_ratio[2];
			x_pos_right = ((i+1) / size[2]) * size_ratio[2];

			rect(x_pos_left, y_pos_bottom, x_pos_right, y_pos_top, col=col_pallet[i + 1])
		}	
	}
}

MergeMatrix <- function(size, data)
{
	merge_n_row = ((size[1] -1) + (size[2] -1))

	merge_matrix = matrix(data,
	   					  nrow = merge_n_row,
	   					  ncol=2,
	   					  byrow = TRUE) # fill matrix by rows 

	return(merge_matrix);
}

SplitVectors <-function(size, merge_matrix, height_vector, rowcol_vector)
{
	row_merge = vector(mode="numeric", length=(size[1] - 1) * 2);
	row_hight = vector(mode="numeric", length=size[1] - 1);

	col_merge = vector(mode="numeric", length=(size[2] - 1) * 2);
	col_hight = vector(mode="numeric", length=size[2] - 1);

	total_merges = ((size[1] -1) + (size[2] -1));
	index_row_merge = 0;
	index_col_merge = 0;

	n_merge = 0;

	for(i in 1:total_merges)
	{
		if(rowcol_vector[i] == 0)
		{
			row_merge[index_row_merge * 2 + 1] = merge_matrix[n_merge + 1, 1];
			row_merge[index_row_merge * 2 + 2] = merge_matrix[n_merge + 1, 2];
			row_hight[index_row_merge + 1] = height_vector[n_merge + 1];

			index_row_merge = index_row_merge + 1;

		} else {
			col_merge[index_col_merge * 2 + 1] = merge_matrix[n_merge + 1, 1];
			col_merge[index_col_merge * 2 + 2] = merge_matrix[n_merge + 1, 2];
			col_hight[index_col_merge + 1] = height_vector[n_merge + 1];

			index_col_merge = index_col_merge + 1;
		}

		n_merge = n_merge + 1;
	}

	return(list(row_merge = matrix(row_merge, nrow = size[1] - 1, ncol = 2, byrow = TRUE),
				row_hight = row_hight,
				col_merge = matrix(col_merge, nrow = size[2] - 1, ncol = 2, byrow = TRUE),
				col_hight = col_hight));
}

DrawRowDendrogram <-function(size, merge_info, size_ratio, order)
{
	n_row_merge = size[1] - 1;
	lines = ProcessRowDendrogram(n_row_merge, 
								 merge_info$row_merge, 
								 merge_info$row_hight, 
								 order);

	lines[, c(1, 3, 5, 7, 9, 11)] = lines[, c(1, 3, 5, 7, 9, 11)] * (1.0 - size_ratio[2]);
	lines[, c(1, 3, 5, 7, 9, 11)] = lines[, c(1, 3, 5, 7, 9, 11)] + size_ratio[2];
	lines[, c(2, 4, 6, 8, 10, 12)] = lines[, c(2, 4, 6, 8, 10, 12)] * size_ratio[1];

	for(l in 1:n_row_merge)
	{
		segments(lines[l, 1], lines[l, 2], lines[l, 3], lines[l, 4]);
		segments(lines[l, 5], lines[l, 6], lines[l, 7], lines[l, 8]);
		segments(lines[l, 9], lines[l, 10], lines[l, 11], lines[l, 12]);
	}
}

DrawColDendrogram <-function(size, merge_info, size_ratio, order)
{
	n_col_merge = size[2] - 1;
	lines = ProcessColDendrogram(n_col_merge, merge_info$col_merge, merge_info$col_hight, order);

	# RIGHT SIDE DENDROGRAM.
	lines[, c(1, 3, 5, 7, 9, 11)] = lines[, c(1, 3, 5, 7, 9, 11)] * size_ratio[2];
	lines[, c(2, 4, 6, 8, 10, 12)] = lines[, c(2, 4, 6, 8, 10, 12)] * (1.0 - size_ratio[1]);
	lines[, c(2, 4, 6, 8, 10, 12)] = lines[, c(2, 4, 6, 8, 10, 12)] + size_ratio[1];


	for(l in 1:n_col_merge)
	{
		segments(lines[l, 1], lines[l, 2], lines[l, 3], lines[l, 4]);
		segments(lines[l, 5], lines[l, 6], lines[l, 7], lines[l, 8]);
		segments(lines[l, 9], lines[l, 10], lines[l, 11], lines[l, 12]);
	}
}


Dendrogram2D.plot <- function(data, size_ratio = c(0.5, 0.5))
{
	plot.new()
	frame()

	size = dim(data);

	DrawBottomRect(size, size_ratio);

	clust_info <- BiClust(data);

	merge_info = SplitVectors(size, 
							  clust_info$merge, 
							  clust_info$height, 
							  clust_info$row_col);

	DrawRowDendrogram(size, merge_info, size_ratio, clust_info$row_order);
	DrawColDendrogram(size, merge_info, size_ratio, clust_info$col_order);
}

# # Random values (r_row * n_col).
data = matrix(c(-1, -2, -3, -2, 
				-5, -6, -7, -8, 
				-9, -1, -12, -2), 
			  nrow = size[1], 
			  ncol = size[2], 
			  byrow = TRUE);

library(bclust)
data(gaelle)

Dendrogram2D.plot(gaelle);
# Dendrogram2D.plot(data);

