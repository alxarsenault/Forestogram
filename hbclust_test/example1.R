




# ranges <- matrix(c(5.0, 7.5,
# 				   12.0, 20.0,
# 				   3.0, 15.8,
# 				   3.0, 30.5,
# 				   20.0, 21.2,
# 				   8.0, 12.0,
# 				   5.0, 16.0,
# 				   6.0, 9.2,
# 				   15.0, 20.0,
# 				   10.0, 11.0), nrow = 10, ncol = 2, byrow = TRUE)

# vec = c();

# for(i in seq(1, 10))
# {
# 	vec = c(vec, runif(20, ranges[i, 1], ranges[i, 2]));
# }

# data <- matrix(vec, nrow = 10, ncol = 20, byrow = TRUE)
# row_names <- seq(1, 10, 1);
# col_names <- seq(1, 20, 1);
# dimnames(data) <- list(row_names, col_names)


library(hbiclust)
load("Data.RData")

# data <- b

ch=80
hbiclust.plot(b, cut_height = ch);

forestogram(b, cut_height = ch, 
line_width = 3.0, 
interpolate_tree_colors = FALSE, 
cut_base_alpha = 0.4,
draw_only_from_cut =T);


# v <- hbiclust(data);

# forestogram(v, cut_height = 11.0, 
# 			line_width = 3.0, 
# 			interpolate_tree_colors = FALSE, 
# 			cut_base_alpha = 0.4,
# 			draw_only_from_cut = TRUE);

# # hbiclust.plot(v, cut_height = 11);

# # d <- dist(t(gaelle), method = "euclidean")
# # hc <- hclust(d, method = "complete")
# # plot(hc);

# # library(rpanel)
# # x <- rnorm(25)
# # panel <- rp.control(v = 0, x = x)
# # rp.tkrplot(panel, plot, draw, pos="right")
# # rp.slider(panel, v, min(x), max(x), redraw, name = "slider")
# # rp.doublebutton(panel, v, diff(range(x))/100, action=redraw1)