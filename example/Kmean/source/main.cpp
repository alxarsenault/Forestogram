#include <iostream>
#include "kmeans.h"

// int main()
// {
// 	std::cout << "Main" << std::endl;

// 	// float** cuda_kmeans(float **objects,      /* in: [numObjs][numCoords] */
//  //                   int     numCoords,    /* no. features */
//  //                   int     numObjs,      /* no. objects */
//  //                   int     numClusters,  /* no. clusters */
//  //                   float   threshold,    /* % objects change membership */
//  //                   int    *membership,   /* out: [numObjs] */
//  //                   int    *loop_iterations)
// 	// float** cuda_kmeans(float**, int, int, int, float, int*, int*);

// 	// return an array of cluster centers of size [numClusters][numCoords]

// 	float** data = new float*[4];

// 	for(int i = 0; i < 4; i++)
// 	{
// 		data[i] = new float[2];
// 		data[i][0] = float(i);
// 		data[i][1] = float(i);
// 	}

// 	int numCoords = 2;
// 	int nCluster = 2;
// 	int membership = 0;
// 	int loop_iterations = 0;
// 	float** kmeans_answer = cuda_kmeans(data, numCoords, 4, nCluster, 0.0, &membership, &loop_iterations);

// 	for(int i = 0; i < nCluster; i++)
// 	{
// 		std::cout << kmeans_answer[i][0] << " " << kmeans_answer[i][1] << std::endl;
// 	}

// 	return 0;
// }