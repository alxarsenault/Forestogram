# library(ellipse)

N = 500


#----------------------------------------------------------
# Cluster 1.
#----------------------------------------------------------
x1 = rnorm(N, mean=4.5, sd=4.0)
y1 = rnorm(N, mean=0.8, sd=0.3)

avr_x1 = mean(x1)
avr_y1 = mean(y1)

sd_x1 = sd(x1)
sd_y1 = sd(y1)

r_x1 = 4.5
r_y1 = 0.8

#cat("Clust 1 = ", avr_x1, " ", avr_y1, "\n")
#cat("Clust 1 = ", sd_x1, " ", sd_y1, "\n")
colors_1 = rep(rgb(0.0, 1.0, 0.0), N)


# #----------------------------------------------------------
# # Cluster 2.
# #----------------------------------------------------------
x2 = rnorm(N, mean=15, sd=5.0)
y2 = rnorm(N, mean=2.8, sd=0.6)

r_x2 = 15
r_y2 = 2.8

avr_x2 = mean(x2)
avr_y2 = mean(y2)
cat("Clust 2 = ", avr_x2, " ", avr_y2, "\n")

colors_2 = rep(rgb(1.0, 0.0, 0.0), N)
#----------------------------------------------------------
# Cluster 3.
#----------------------------------------------------------
x3 = rnorm(N, mean=7, sd=1.0)
y3 = rnorm(N, mean=5, sd=0.5)

r_x3 = 15
r_y3 = 2.8

avr_x3 = mean(x3)
avr_y3 = mean(y3)
# cat("Clust 2 = ", avr_x2, " ", avr_y2, "\n")

colors_3 = rep(rgb(0.0, 0.0, 1.0), N)
#----------------------------------------------------------



x = c(x1, x2, x3)
y = c(y1, y2, y3)
colors = c(colors_1, colors_2, colors_3)


# old.par <- par(mfrow=c(1, 2))

plot(x, y, col=colors, pch=20)
points(c(avr_x1,  avr_x2, avr_x3), c(avr_y1, avr_y2, avr_y3), pch=3, col=rgb(0.0, 0.0, 0.0))


# a <- 5
# b <- 1
# x0 <- 1
# y0 <- 1
# alpha <- atan(0.1)
# theta <- seq(0, 2 * pi, length=(1000))

# x_e <- x0 + a * cos(theta) * cos(alpha) - b * sin(theta) * sin(alpha)
# y_e <- y0 + a * cos(theta) * sin(alpha) + b * sin(theta) * cos(alpha)

# points(x_e, y_e, col="blue")
# ellipse(c(0, 0), c(1), 1.0, center.pch=19, center.cex=1.5, 
#   segments=51, add=TRUE, xlab="", ylab="", 
#    las=par('las'), col="blue", lwd=2, lty=1)
# ellipse(x, scale = c(1, 1), centre = c(avr_x1, avr_y1), level = 0.95, col = rgb(1.0, 1.0, 0.0))
# ellipse(h=0.5, angle=30)

# points(r_x1, r_y1, pch=21, col=rgb(0.0, 0.0, 1.0), cex= sd_x1)
# points(r_x2, r_y2, pch=21, col=rgb(0.0, 0.0, 1.0), cex= 5.0)

# title(main = "Real clusters")


# #km = kmeans(c(x, y), 3)
# km = kmeans(c(x, y), 3)
# plot(x, y, col=km$cluster)
# title(main = "Kmean clusters")

# par(old.par)
