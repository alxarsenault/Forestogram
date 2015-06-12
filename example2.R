library(rgl)
library(bclust)
source('Forestogram.R')

CombineRowAndColMergeAndHeight <- function(size, row, col, row_height, col_height)
{
	merge_n_row = ((size[1] -1) + (size[2] -1))

	index_row = 1
	index_col = 1
	index_row_two = 1
	index_col_two = 1
	index = 1

	delta = 0
	data = vector(mode="numeric", length=0)

	for(i in 1:55)
	{
		r_height_delta = 0#abs(row_height[index_row] - delta)
		
    if(index_row > (size[1]-1))
		{
			r_height_delta = 1000000
			#cat("SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS")
		}
		else
		{
			#cat("\nINDEX RO ::: ", index_row)
      #EEREURR
			r_height_delta = row_height[index_row]
		}

		c_height_delta = col_height[index_col]#abs(col_height[index_col] - delta)

		if(r_height_delta < c_height_delta)
		{
			data[index] = row[index_row_two]
			data[index+1] = row[index_row_two+1]
			data[index+2] = row_height[index_row]
			data[index+3] = 0

			index_row <- index_row + 1
			index_row_two <- index_row_two + 2
			#delta <- r_height_delta
			index <- index + 4
		}
		else
		{
			data[index] = col[index_col_two]
			data[index+1] = col[index_col_two+1]
			data[index+2] = col_height[index_col]
			data[index+3] = 1

			index_col <- index_col + 1
			index_col_two <- index_col_two + 2
			index <- index + 4
		}
	}

	merge_matrix = matrix(data,
	   					          nrow = merge_n_row,
	   					          ncol = 4,
	   					          byrow = TRUE) # fill matrix by rows 

	return(merge_matrix)
}

#---------------------------------------------------------------------------------------
# Remove all the .2, .3, .4 elements.
data(gaelle)

a <- gaelle

# print(a)

b = 1:55
c = seq(4, 55, 4)
d = c(1)
b <- b[-c]
b <- b[-d]
a <- a[-b,]

# Matrix dimension.
size = c(14, 43)

row = c( -6,  -7,	
         -2,  -5,
          2,  -3,
         -9, -10,
          3,  -4,
        -11, -12,
          6, -13,
          7, -14,
          8,   4,
          9,  -8,
         10,  -1,
         11,   5,
         12,   1 )

row_ord = c(11, 12, 13, 14, 9, 10, 8, 1,  2,  5,  3,  4, 6, 7)

row_pos =c( -1931.594, 
	          -1903.779,
	          -1896.990,
	          -1884.700,
            -1880.054,
            -1854.682, 
            -1851.869, 
            -1849.247, 
            -1847.492, 
            -1825.632, 
            # PROBLEM WITH THE LAST ONES (3).
            -1825.632 + 2.331, #-1827.963
            -1825.632 + 50.084, #-1875.716, 
            -1825.632 + 118.908)#-1943.540) 

col = c(-23, -25,
          1,  -4,
          2, -18,
         -3,  -6,
          4,  -9,
         -2, -13,
          5, -31,
          7, -10,
          8, -14,
          9,  -5,
         10, -38,
         11, -28,
         12, -20,
        -15, -34,
         14, -33,
         15, -29,
         16, -22,
         17, -27,
         18, -43,
         19, -11,
         20, -17,
         21, -26,
         22, -37,
         23, -41,
         -7, -19,
         25, -24,
         13, -12,
         27,  -8,
        -30, -42,
         29, -40,
         30, -36,
         31, -39,
         32, -21,
         33, -32,
         34, -35,
         35, -16,
         36,  26,
         37,   6,
         38,  24,
         39,  28,
         40,  -1,
         41,   3)

 col_ord= c(30, 42, 40, 36, 39, 21, 32, 35, 16,  
 			      7, 19, 24,  2, 13, 15, 34, 33, 29, 
 			      22, 27, 43, 11, 17, 26, 37, 41,  3, 
 			      6,  9, 31, 10, 14,  5, 38, 28, 20, 
 			      12,  8,  1, 23, 25,  4, 18)
 
 col_pos= c( -1923.791, 
 	           -1912.095,
 	           -1890.653,
 	           -1874.904,
 	           -1869.877,
 	           -1866.058, 
 	           -1862.769,
 	           -1860.382, 
 	           -1858.169, 
 	           -1856.289, 
 	           -1846.465, 
 	           -1845.380, 
 	           -1844.230, 
 	           -1843.217, 
 	           -1840.901, 
 	           -1838.208, 
 	           -1835.315, 
 	           -1831.820,
 	           -1829.413, 
 	           -1827.457, 
 	           -1824.860, 
 	           -1824.129, 
 	           -1823.456, 
 	           -1823.140, 
 	           -1822.956, 
 	           -1822.683, 
 	           -1822.513, 
 	           -1822.335, 
 	           -1822.228, 
 	           -1822.119, 
 	           -1822.009, 
 	           -1821.898, 
 	           -1821.787, 
 	           -1821.676, 
 	           -1821.564, 
 	           -1821.455, 
             # PROBLEM WITH THE LAST ONES (6).
 	           -1821.455 + 0.195,#-1821.650,
 	           -1821.455 + 13.023,#-1834.478, 
 	           -1821.455 + 25.885,#-1847.340, 
 	           -1821.455 + 58.556,#-1880.011, 
 	           -1821.455 + 114.837,#-1936.292, 
 	           -1821.455 + 186.689)#-2008.144 )
  
info_matrix <- CombineRowAndColMergeAndHeight(size, row, col, row_pos, col_pos)

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
              a, 
              row_ord, 
              col_ord,
              cut_height = 48,
              draw_cut = TRUE, 
              draw_side_tree = TRUE, 
              draw3D = TRUE,
              draw2D_grid = TRUE,
              line_width = 4,
              line_width_2D = 1) 
               