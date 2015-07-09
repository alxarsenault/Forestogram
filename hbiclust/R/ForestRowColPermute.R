#source('ForestUtils.R')

##### SHOULD BE MADE IN C++ 
DoRowPermutation <- function(size, row_permutation)
{
	row_names = 0
	if(length(row_permutation) == size[1])
	{
		v = vector(mode="numeric", length=0)

		for(i in 1:length(row_permutation))
		{
			val = -row_permutation[i]
			index = toString(val)
			v[index] = i
		}

		row_names <- v
	}
	else
	{
		cat("No row permuation.")

		# Name rows and columns.
		row_names <- CreateRowNames(size[1])
	}

	return (row_names)
}

##### SHOULD BE MADE IN C++ 
DoColPermutation <- function(size, col_permutation)
{
	col_names = 0

	if(length(col_permutation) == size[2])
	{
		v = vector(mode="numeric", length=0)

		for(i in 1:length(col_permutation))
		{
			val = -col_permutation[i]
			index = toString(val)
			v[index] = size[2] - (i - 1)
		}

		col_names <- v
		plane_col_names <- v
	}
	else
	{
		cat("No col permuation.\n")
		
		# Name rows and columns.
		col_names <- CreateColNames(size[2])
		plane_col_names <- col_names
		
	}
	return (col_names)
}