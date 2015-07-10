library(hbiclust)

ranges <- matrix(c(5.0, 7.5,
				   12.0, 20.0,
				   3.0, 15.8,
				   3.0, 30.5,
				   20.0, 21.2,
				   8.0, 12.0,
				   5.0, 16.0,
				   6.0, 9.2,
				   15.0, 20.0,
				   10.0, 11.0), nrow = 10, ncol = 2, byrow = TRUE)

vec = c();

for(i in seq(1, 10))
{
	vec = c(vec, runif(20, ranges[i, 1], ranges[i, 2]));
}

data <- matrix(vec, nrow = 10, ncol = 20, byrow = TRUE)
row_names <- seq(1, 10, 1);
col_names <- seq(1, 20, 1);
dimnames(data) <- list(row_names, col_names)


v <- hbiclust(data);

forestogram(v, cut_height = 11.0);
# hbiclust.plot(v, cut_height = 11);

# d <- dist(t(gaelle), method = "euclidean")
# hc <- hclust(d, method = "complete")
# plot(hc);