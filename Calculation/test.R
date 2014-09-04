 # A = matrix( 
# c(1, 1, 1, 2, 2, 1, 2, 2, 3, 1, 6, 6, 6, 7, 7, 7, 7, 8, 8, 7, 8, 8), # the data elements 


# X = c(0.5, 
#   1.0, 
#   1.0, 
#   1.0, 
#   1.5, 
#   2.0, 
#   2.5, 
#   2.5, 
#   2.5, 
#   4.0, 
#   4.5, 
#   4.5, 
#   4.5, 
#   4.5)

# Y = c(1.0,
# 0.5,
# 1.0,
# 1.5,
# 1.0,
# 2.5,
# 2.5,
# 3.0,
# 3.5,
# 1.0,
# 0.5,
# 1.0,
# 1.5,
# 2.0)



X = c(
  4.4, 
  1.61111
  )
  	

Y = c(
  1.2,
  1.83333)




b <- dist(A, diag = FALSE, upper = TRUE, p = 2)

png("img11.png")
plot(X, Y, col=rgb(0, 0, 0), pch=20, panel.first= grid(nx = NULL, ny = NULL, col = "black", lty = "dotted"))
# segments(1, 1, 2.375, 2.875, col="red")
# segments(2.25, 2.5, 2.5, 3.25, col="red")
# segments(4.33333333, 0.83333333, 4.5, 1.75, col="red")
# segments(4.0, 1.0, 4.5, 1.0, col="red")
# segments(4.5, 1.5, 4.5, 2.0, col="red")

library(calibrate)
textxy(X, Y, c(11, 12), cex = 0.8)

# grid(nx = NULL, ny = NULL, col = "lightgray", lty = "dotted",
#      lwd = par("lwd"), equilogs = TRUE)
# points(X, Y, pch=20, col=rgb(0.0, 0.0, 0.0))

dev.off()