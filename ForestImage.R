# library(png)

SavePlotImage <- function(file_name)
{
	snapshot3d(file_name)
	# Replace the directory and file information with your info
	# ima <- readPNG(file_name)

	# # Set up the plot area
	# plot(1:2, type='n', main="Forestogramme", axes=FALSE)

	# #Get the plot information so the image will fill the plot box, and draw it
	# lim <- par()
	# rasterImage(ima, lim$usr[1], lim$usr[3], lim$usr[2], lim$usr[4])
		
	# legend.col <- function(col, lev, x_pos = 1)
	# {
	 
	# 	opar <- par
		 
	# 	n <- length(col)
		 
	# 	by <- par("usr")
		 
	# 	box.cy <- c(by[2] + (by[2] - by[1]) / 100,	by[2]) #+ (by[2] - by[1]) / 1000 + (by[2] - by[1]) / 50)
	# 	box.cx <- c(by[3], by[3])
	# 	box.sx <- (by[4] - by[3]) / n
		 
	# 	yy <- rep(box.cy - x_pos, each = 2)

	# 	par(xpd = TRUE)
	# 	for(i in 1:n)
	# 	{
		 
	# 		xx <- c(box.cx[1] + (box.sx * (i - 1)),
	# 		box.cx[1] + (box.sx * (i)),
	# 		box.cx[1] + (box.sx * (i)),
	# 		box.cx[1] + (box.sx * (i - 1)))

	# 		polygon(xx, yy, col = col[i], border = col[i])
	# 		#polygon(xx, yy, col = test[i], border = test[i])
		 
	# 	}
	# 	par(new = TRUE)
	# }

	# data = 1:100
	 
	# legend.col(col = heat.colors(100), lev = data, x_pos = 1)
	# legend.col(col = cm.colors(100), lev = data, x_pos = 1.08)
	# legend.col(col = rainbow(100, start = 0.3, end = 0.6), lev = data, x_pos = 1.16)
}

