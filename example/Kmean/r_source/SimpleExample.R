
CudaKMean <- function(data, nCluster)
{
	dyn.load("lib/SimpleExample.so")

	# print("R CudaKMean")

	matrix_dim = 0
	nrow = 0
	ncol = 0

	if(is.matrix(data) == TRUE) {
		matrix_size = dim(data)
		matrix_dim = length(matrix_size)
		nrow = matrix_size[1]
		ncol = matrix_size[2]

	} else {

		if(is.null(dim(data)))
		{
			print("IS VECTOR")
			matrix_dim = 1
			nrow = 1
			ncol = length(data)
		} else
		{
			print("PROBLEME")
			matrix_size = dim(data)
			matrix_dim = length(matrix_size)
			nrow = matrix_size[1]
			ncol = matrix_size[2]

			# data = matrix(data = data, nrow = nrow, ncol = ncol)
		}
	}

	# nnn = matrix(nrow = nCluster, ncol = ncol)
	nnn = vector(length=nCluster * ncol, mode="numeric")

	out <- .C("CudaKMean", 
			  data = data, 
			  dim = as.integer(matrix_dim), 
			  nrow = as.integer(nrow), 
			  ncol = as.integer(ncol), 
			  nCluster = as.integer(nCluster),
			  answer = nnn)

	# return(out)

	# vv <- c(1, 2, 3)
	# return(answer)
	# return out[1]
	# return(c(1, 2, 3))
	# return(nnn)
	return(out)
}

# SimpleExample <- function(value)
# {
# 	dyn.load("lib/SimpleExample.so")
    
# 	out <- .C("SimpleExample", x = as.double(value))
# 	return(out)
# }	

# # void PrintMatrix(double* data, int* dim, int* nrow, int* ncol)
# PrintMatrix <- function(data)
# {
# 	dyn.load("lib/SimpleExample.so")

# 	matrix_dim = 0
# 	nrow = 0
# 	ncol = 0

# 	if(is.matrix(vec) == TRUE) {
# 		matrix_size = dim(data)
# 		matrix_dim = length(matrix_size)
# 		nrow = matrix_size[1]
# 		ncol = matrix_size[2]

# 	} else {
# 		matrix_dim = 1
# 		nrow = 1
# 		ncol = length(data)
# 	}

# 	out <- .C("PrintMatrix", data = data, dim = as.integer(matrix_dim), nrow = as.integer(nrow), ncol = as.integer(ncol))

# 	return(out)
# }