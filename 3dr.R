
f = function(x, y)
{
  sqrt(x^2 + y^2)
}

g = function(x, y)
{
	(0.5)
}
                                                                             
x = seq(-1, 1,length = 21)
y = x
z = outer(x, y, f)
#z = seq(0.5, 0.4, length = 21)
open3d(windowRect = c(0,0, 600, 600) )

rgl.clear()
rgl.clear("lights")
rgl.light(theta = 0, phi = 90)

rgl.surface(x, y, z, color="seagreen", smooth=TRUE,
            specular = "#444444",
            ambient="#555555",
            front = "fill",
            back = "fill",
            alpha = 0.4)

i <- seq(-1, 1)
j <- seq(-1, 1)
k = 1

planes3d(0, 0, 1, 1, alpha=0.7, col="blue")

# planes3d(0, 0, 10, 1, alpha=0.7, col="blue")


# rgl.surface(i, j, k, color="seagreen", smooth=TRUE,
#             specular = "#FF4444",
#             ambient="#555555",
#             front = "fill",
#             back = "fill",
#             alpha = 0.4)

# rgl.surface(x, y, z, color="seagreen", smooth=TRUE,
#             specular = "#444444",
#             ambient="#555555",
#             front = "fill",
#             back = "fill",
#             alpha = 0.4)

# rgl.surface(y, x, z, color="seagreen", smooth=TRUE,
#             specular = "#444444",
#             ambient="#555555",
#             front = "fill",
#             back = "fill")

# rgl.surface(x, y, z + 0.01, color="black", smooth=TRUE,
#             specular = "#000000",
#             ambient="#555555",
#             front = "line",
#             back = "line")

grid3d(c("x", "y", "z"))