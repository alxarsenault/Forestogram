source("r_source/SimpleExample.R")

value = 89
# vec = c(2, 3, 5) 
vec = matrix(data = c(1, 2, 3, 4, 5, 6), nrow = 2, ncol = 3, byrow = TRUE)

answer = PrintMatrix(vec)
# answer = SimpleExample(value, vec)


# if(is.matrix(vec) == TRUE) {
# 	print("Is matrix")
# 	print(dim(vec))

# 	matrix_size = dim(vec)
# 	matrix_dim = length(matrix_size)

# 	print(matrix_dim)

# 	print("Row")
# 	print(matrix_size[1])
# 	print("Col")
# 	print(matrix_size[2])
# } else {
# 	print("Is vec")
# 	print(length(vec))
# }


# print(vec)
# print(length(vec))

# print(is.matrix(vec))

# print("Dim :")
# print(dim(vec))