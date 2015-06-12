#include <iostream>
#include <vector>
#include "RUtils.h"
#include "kmeans.h"

extern "C"
{
	void CudaKMean(double* data, int* dim, int* nrow, int* ncol, int* nCluster, double* answer)
	{
		R::Print("CudaKMean");

		R::Size2D size(*nrow, *ncol);
		R::Matrix2D<double> matrix(data, size);

		double** data_cpy = new double*[size.row];

		for(int i = 0; i < size.row; i++)
		{
			data_cpy[i] = new double[size.col];

			for(int n = 0; n < size.col; n++)
			{
				data_cpy[i][n] = double(matrix(i, n));
			}
		}

		int nData = size.row;
		int numCoords = size.col;
		int K = *nCluster;
		// int membership = 0;
		int* membership = new int[size.row];
		int loop_iterations = 0;
		double** kmeans_answer = cuda_kmeans(data_cpy, numCoords, nData, K, 0.0, membership, &loop_iterations);

		// R::Print("NIter =", loop_iterations);
		
		R::Matrix2D<double> answer_matrix(answer, R::Size2D(K, numCoords));

		for(int j = 0; j < K; j++)
		{
			// std::cout << std::fixed;

			for(int i = 0; i < numCoords; i++)
			{
				// std::cout << kmeans_answer[j][i] << " ";
				// answer_matrix(j, i) = kmeans_answer[j][i];
				answer_matrix.AssignValue(j, i, kmeans_answer[j][i]);
			}
			
			// std::cout << std::endl;
		}

		// std::cout << std::fixed << kmeans_answer[i][0] << " " << kmeans_answer[i][1] << std::endl;
	}
}
