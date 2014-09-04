 # A = matrix( 
# c(1, 1, 1, 2, 2, 1, 2, 2, 3, 1, 6, 6, 6, 7, 7, 7, 7, 8, 8, 7, 8, 8), # the data elements 


X = c(
0.5, 
  1.0, 
  1.0, 
  1.0, 
  1.5, 
  2.0, 
  2.5, 
  2.5, 
  2.5, 
  4.0, 
  4.5, 
  4.5, 
  4.5, 
  4.5)

Y = c(
1.0,
0.5,
1.0,
1.5,
1.0,
2.5,
2.5,
3.0,
3.5,
1.0,
0.5,
1.0,
1.5,
2.0)


b <- dist(A, diag = FALSE, upper = TRUE, p = 2)

# plot(X, Y, col=rgb(0, 0, 0), pch=20, panel.first= grid(nx = NULL, ny = NULL, col = "black", lty = "dotted"))
# grid(nx = NULL, ny = NULL, col = "lightgray", lty = "dotted",
#      lwd = par("lwd"), equilogs = TRUE)
# points(X, Y, pch=20, col=rgb(0.0, 0.0, 0.0))