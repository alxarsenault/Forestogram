source('my_func.R')

power(5)
cube(5)

# v = c(1, 2, 3, 4, 5, 6)

# t = mytest(v)

data = c(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
k = matrix(data, nrow = 5, ncol=2, byrow = FALSE) 

g = mytest(k)