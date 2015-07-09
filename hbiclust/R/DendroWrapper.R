ProcessRowDendrogram <- function(n_merge, merge_matrix, height_vector, order, cut_hight)
{
    # dyn.load("lib/hbiclust.so");
	matrix_dim = 0
	nrow = 0
	ncol = 0


	answer = vector(mode="numeric", length = n_merge * 16);
	ans_matrix = matrix(answer,  nrow = n_merge,  ncol = 16, byrow = TRUE)

	answer_limits = vector(mode="numeric", length =n_merge + 1);

	out <- .C("ProcessRightSideDendrogram", 
			  n_merge = as.integer(n_merge), 
			  merge = merge_matrix, 
			  height = height_vector,
			  order = order,
			  cut_hight = cut_hight,
			  line_points = ans_matrix,
			  answer_limits = answer_limits,
			  PACKAGE='hbiclust');


	return(list(lines = matrix(out$line_points, 
				  nrow = n_merge,
	   			  ncol = 16,
	   			  byrow = FALSE), limits = out$answer_limits));
}	

ProcessColDendrogram <- function(n_merge, merge_matrix, height_vector, order, cut_hight)
{
    # dyn.load("lib/hbiclust.so");

	matrix_dim = 0
	nrow = 0
	ncol = 0

	answer = vector(mode="numeric", length = n_merge * 16);
	ans_matrix = matrix(answer,  nrow = n_merge,  ncol = 16, byrow = TRUE)

	answer_limits = vector(mode="numeric", length =n_merge + 1);
	# limits_matrix = matrix(answer_limits,  nrow = n_merge + 1,  ncol = 2);

	out <- .C("ProcessColDendrogram", 
			  n_merge = as.integer(n_merge), 
			  merge = merge_matrix, 
			  height = height_vector,
			  order = order,
			  cut_hight = cut_hight,
			  line_points = ans_matrix,
			  answer_limits = answer_limits,
			  PACKAGE='hbiclust');

	# print(out$answer_limits);

	return(list(lines = matrix(out$line_points, 
				  nrow = n_merge,
	   			  ncol = 16,
	   			  byrow = FALSE), limits = out$answer_limits));
	# return(matrix(out$line_points, 
	# 			  nrow = n_merge,
	#    			  ncol = 16,
	#    			  byrow = FALSE));

	# return(out$answer);
}






# void ProcessClusterOnRect(int* size, double* size_ratio, double* margin)
ProcessClusterOnRect <- function(size, size_ratio, margin, row_limits, col_limits)
{
	# dyn.load("lib/hbiclust.so");

	n_clust = sum(row_limits) * sum(col_limits);


	# Format :
	# Rectangle : 
	# [1] : x1
	# [2] : y1
	# [3] : x2
	# [4] : y2
	# Color : 
	# [5] : r
	# [6] : g
	# [7] : b
	answer = vector(mode="numeric", length = n_clust * 7);
	ans_matrix = matrix(answer,  nrow = n_clust,  ncol = 7, byrow = TRUE)

	out <- .C("ProcessClusterOnRect", 
			  size = size,
			  size_ratio = size_ratio,
			  margin = margin,
			  row_limits = row_limits,
			  col_limits = col_limits,
			  rect_points = ans_matrix,
			  PACKAGE='hbiclust');

	return(list(rect_points=out$rect_points,
				n_clust = n_clust));
}


