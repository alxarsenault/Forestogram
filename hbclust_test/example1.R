# library(rgl)
library(hbiclust)


library(bclust)
data(gaelle)

v <- hbiclust(gaelle);

forestogram(v, cut_height = 9.0);
plot.hbiclust(v, cut_height = 9.0);
			