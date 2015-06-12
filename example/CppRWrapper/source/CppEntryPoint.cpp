#include <iostream>
#include <vector>
#include "RUtils.h"

extern "C"
{
	void PrintMatrix(double* data, int* dim, int* nrow, int* ncol)
	{
		std::cout << "PrintMatrix" << std::endl;

		R::Matrix2D<double> matrix(data, R::Size2D(*nrow, *ncol));

		for(int j = 0; j < *nrow; j++)
		{
			for(int i = 0; i < *ncol; i++)
			{
				R::Print(matrix(j, i));
			}
		}
	}

	void SimpleExample(double* x)
	{
        std::cout << "X value : " << *x << std::endl;
	}
}
