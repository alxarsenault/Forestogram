source("Biclustering.R")
library(rgl)
library(bclust)
source('Function.R')

# data(gaelle)
# a <- gaelle
# b = 1:55
# c = seq(4, 55, 4)
# d = c(1)
# b <- b[-c]
# b <- b[-d]
# a <- a[-b,]

# Matrix size.
n_row = 4
n_col = 2


size = c(n_row, n_col)

# data = c(1, 2, 3, 4, 5, 6, 7, 8, 9)

# data = c(0.5, 1.0,
# 		 1.0, 0.5,
# 		 1.0, 1.0)

data = c(0, 0,
		 0, 2,
		 5, 0,
		 6, 0)

		 # 1.0, 1.5,
		 # 1.5, 1.0,
		 # 2.0, 2.5,
		 # 2.5, 2.5,
		 # 2.5, 3.0,
		 # 2.5, 3.5,
		 # 4.0, 1.0,
		 # 4.5, 0.5,
		 # 4.5, 1.0,
		 # 4.5, 1.5,
		 # 4.5, 2.0)


	# points[0] = RPoint(0.5, 1.0);
	# points[1] = RPoint(1.0, 0.5);
	# points[2] = RPoint(1.0, 1.0);
	# points[3] = RPoint(1.0, 1.5);
	# points[4] = RPoint(1.5, 1.0);
	# points[5] = RPoint(2.0, 2.5);
	# points[6] = RPoint(2.5, 2.5);
	# points[7] = RPoint(2.5, 3.0);
	# points[8] = RPoint(2.5, 3.5);
	# points[9] = RPoint(4.0, 1.0);
	# points[10] = RPoint(4.5, 0.5);
	# points[11] = RPoint(4.5, 1.0);
	# points[12] = RPoint(4.5, 1.5);
	# points[13] = RPoint(4.5, 2.0);


k = matrix(data, nrow = n_row, ncol= n_col, byrow = FALSE)
# row_ord = c(6, 7, )

clus = BiClustering(k, n_row, n_col)

merges_row <- matrix(clus$merge, nrow = n_row-1, ncol=2, byrow = TRUE)
heights_row <- clus$height

# heights_row
k2 = t(k)

# k2
clus2 = BiClustering(k2, n_col, n_row)
merges_col <- matrix(clus2$merge, nrow = n_col-1, ncol=2, byrow = TRUE)
heights_col <- clus2$height


info_matrix = CombineMerges(size, 
							merges_row, 
						    merges_col, 
						    heights_row, 
						    heights_col)

# info_matrix
total_length = size[1] + size[2] - 2
l_vec = 1:total_length

merge_matrix <- info_matrix[l_vec, -c(3, 4)]
height_vector <- info_matrix[l_vec, -c(1, 2, 4)]
height_vector <- height_vector + abs(min(height_vector))

rowcol_vector <- info_matrix[l_vec, -c(1, 2, 3)]
rowcol_vector <- rowcol_vector + abs(min(rowcol_vector))

Forestogramme(size, merge_matrix, 
              height_vector, 
              rowcol_vector,
              data=data, 
              row_permutation=row_ord,
              cut_height = 2,
              draw_cut = FALSE, 
              draw_side_tree = TRUE, 
              draw3D = TRUE,
              draw2D_grid = TRUE,
              line_width = 4,
              line_width_2D = 1)  


