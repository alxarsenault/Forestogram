source("r_source/SimpleExample.R")


# iris_data <- iris
# iris_data$Species <- NULL
# print(iris_data)

# value = 89
# vec = c(2, 3, 5) 
# print(dim(vec))



# # Initial list:
# List <- list()

# # Now the new experiments
# for(i in 1:3){
#   List[[length(List)+1]] <- list(sample(1:3))
# }

# List


# vec = <-List()


# ncol = 3

# 1.010001	2.27	3.1
# 4.9	5	6
# 7.4	8.879999	9

# l1 <- runif(ncol, 5.0, 7.5)
# l2 <- runif(ncol, 5.0, 7.5)
# l3 <- runif(ncol, 5.0, 7.5)
# l4 <- runif(ncol, 5.0, 7.5)
# l5 <- runif(ncol, 5.0, 7.5)
# l6 <- runif(ncol, 5.0, 7.5)

# Row vector matrix.
# vec = matrix(data = c(1.010001,	2.27, 3.1, 4.9,	5,	6, 7.4,	8.879999,	9), nrow = 3, ncol = ncol, byrow=TRUE)

ncol = 5

l1 <- runif(ncol, 5.0, 7.5)
l2 <- runif(ncol, 5.0, 7.5)
l3 <- runif(ncol, 5.0, 7.5)
l4 <- runif(ncol, 5.0, 7.5)
l5 <- runif(ncol, 5.0, 7.5)
l6 <- runif(ncol, 5.0, 7.5)

# Row vector matrix.
vec = matrix(data = c(l1, l2, l3, l4, l5, l6), nrow = 6, ncol = ncol, byrow=TRUE)


# # Row vector matrix.
# # vec = matrix(data = c(1, 2, 3, 4, 5, 
# # 					  6, 7, 8, 9, 10), nrow = 2, ncol = 5, byrow=TRUE)


nCluster = 3;

# # # print(vec)
answer = CudaKMean(vec, nCluster)

# print(answer)

ddd = matrix(data = answer$answer, nrow = nCluster, ncol = ncol, byrow=FALSE)

# print(ddd)

# print("TEST")
gg <- ddd[ order( ddd[,1]), ]
# gg <- sort(ddd, method = "quick")

# sort(ddd(1,:));


# ddd[order(ddd$V1),]

print(gg)

# algorithm = c("Hartigan-Wong", "Lloyd", "Forgy",
#                      "MacQueen")
# # Needs column vector.
answerKMean = kmeans(vec, nCluster, iter.max = 10,)# algorithm = c("Hartigan-Wong"))
ddd = matrix(data = answerKMean$centers, nrow = nCluster, ncol = ncol, byrow=FALSE)
# print(answerKMean$centers)
# print(ddd)
gg <- ddd[ order( ddd[,1]), ]
print(gg)

