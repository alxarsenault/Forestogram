

# SimpleExample <- function(value)
# {
# 	dyn.load("lib/SimpleExample.so")
    
# 	out <- .C("SimpleExample", x = as.double(value))
# 	return(out)
# }	

# void PrintMatrix(double* data, int* dim, int* nrow, int* ncol)
# int* n_merge, 
# double* merge, 
# double* height, 
# double* line_points
ProcessRowDendrogram <- function(n_merge, merge_matrix, height_vector, order)
{
	dyn.load("lib/SimpleExample.so");

	matrix_dim = 0
	nrow = 0
	ncol = 0

	if(is.matrix(vec) == TRUE) {
		matrix_size = dim(data)
		matrix_dim = length(matrix_size)
		nrow = matrix_size[1]
		ncol = matrix_size[2]

	} else {
		matrix_dim = 1
		nrow = 1
		ncol = length(data)
	}

	answer = vector(mode="numeric", length = n_merge * 12);
	ans_matrix = matrix(answer,  nrow = n_merge,  ncol = 12, byrow = TRUE)

	out <- .C("ProcessRightSideDendrogram", 
			  n_merge = as.integer(n_merge), 
			  merge = merge_matrix, 
			  height = height_vector,
			  order = order,
			  line_points = ans_matrix);


	return(matrix(out$line_points, 
				  nrow = n_merge,
	   			  ncol = 12,
	   			  byrow = FALSE));

	# return(out$answer);
}	







ProcessColDendrogram <- function(n_merge, merge_matrix, height_vector, order)
{
	dyn.load("lib/SimpleExample.so");

	matrix_dim = 0
	nrow = 0
	ncol = 0

	if(is.matrix(vec) == TRUE) {
		matrix_size = dim(data)
		matrix_dim = length(matrix_size)
		nrow = matrix_size[1]
		ncol = matrix_size[2]

	} else {
		matrix_dim = 1
		nrow = 1
		ncol = length(data)
	}

	answer = vector(mode="numeric", length = n_merge * 12);
	ans_matrix = matrix(answer,  nrow = n_merge,  ncol = 12, byrow = TRUE)

	out <- .C("ProcessColDendrogram", 
			  n_merge = as.integer(n_merge), 
			  merge = merge_matrix, 
			  height = height_vector,
			  order = order,
			  line_points = ans_matrix);


	return(matrix(out$line_points, 
				  nrow = n_merge,
	   			  ncol = 12,
	   			  byrow = FALSE));

	# return(out$answer);
}