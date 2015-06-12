# Simple example of Forestogram drawing.
source('Forestogram.R')


# Matrix size (row, col).
size = c(3, 4)

# Wich index of row or column to merge.
merge_matrix = MergeMatrix(size, c(-1, -2, 
   						     	   -1, -2, 
   						      		1, -3, 
   						      		2, -4, 
   						      		1, -3))

# Determine if the merge matrix is a row merge or 
# column merge (0 = Row, 1 = Col).
rowcol_vector = c(0, 1, 1, 1, 0)

# Dertermine the height of each merge.
height_vector = c(1, 1.3, 4, 7, 10)

# Random values (r_row * n_col).
data = matrix(c(-1, -2, -3, -4, 
				-5, -6, -7, -8, 
				-9, -20, -30, -50), 
			  nrow = size[1], 
			  ncol = size[2], 
			  byrow = TRUE)

# Draw Forestogram.
Forestogramme(size, 
			  merge_matrix, 
			  height_vector, 
			  rowcol_vector, 
			  data, 
			  cut_height = 3, 
			  draw_cut = TRUE, 
			  draw_side_tree = TRUE, 
			  draw3D = TRUE,
			  draw2D_grid = TRUE,
			  line_width = 4,
			  line_width_2D = 1, 
			  base_contour_width = 1,
			  cut_base_contour_width = 1)
			