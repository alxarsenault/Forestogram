source('Function.R')

n_row = 4
n_col = 3

open3d(windowRect = c(0, 0, 600, 600) )  

DrawPlaneAndGrid(n_row, n_col)

# Example tree drawing.
merge_matrix = CreateMergeMatrix(n_row, n_col, 
								 c(-1, -2, 
   								   -1, -2, 
   								    1, -3, 
   								    2, -4, 
   								    1, -3))

height_vector = c(1, 2, 3, 4, 5)
rowcol_vector = c(0, 1, 1, 1, 0)

if(merge_matrix[1, 1] < 0)
{
	v1 = -merge_matrix[1, 1]
}

if(merge_matrix[1, 2] < 0)
{
	v2 = -merge_matrix[1, 2]
}

index_col = v1
index_row = v2
height = 0.1

for(i in 1:n_row)
{
	point = MiddleSquarePoint(v1, i, n_row, n_col)
	lines3d(point[1], point[2],  seq(0, height, by=0.0001), col="black", lwd=4)
}

for(i in 1:n_row)
{
	point = MiddleSquarePoint(v2, i, n_row, n_col)
	lines3d(point[1], point[2], seq(0, height, by=0.0001), col="black", lwd=4)
}


for(i in 1:n_row)
{
	x1 = -1.0 + 1.0 / n_col * (2 * v1 - 1.0)
	x2 = -1.0 + 1.0 / n_col * (2 * v2 - 1.0)
	y = 1.0 - 1.0 / n_row * (2 * i - 1.0)
	lines3d(seq(x1, x2, by=0.001), y, seq(height, height, by=0.0001), col="black", lwd=4)
}
