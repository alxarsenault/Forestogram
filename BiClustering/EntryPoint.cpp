#include "NCube.h"

extern "C"
{
	void BiClustering(double* x, int *nrow, int* ncol, double* merge, double* height)
	{
		vector<RPoint> points(*nrow);
		int k = 0;

		for(int i = 0; i < *nrow; ++i)
		{
			points[i] = RPoint(x[k], x[k+1]);
			k += 2;
		}

		//Distances distances;
		ClusteringAlogorithm* algo = new NCube();

		algo->Process(points);
		// cout << "MERGES : " << endl;
		// algo->PrintMerges();
		// cout << "HEIGHTS : " << endl;
		// algo->PrintHeights();
		int size = 0;
		double* m = algo->GetMerges(size);

		for(int i = 0; i < size; i++)
		{
			merge[i] = m[i];
		}

		delete m;


		double* h = algo->GetHeights(size);

		for(int i = 0; i < size; i++)
		{
			height[i] = h[i];
		}
	}
}
// int main()
// {
// 	// vector<RPoint> points(11);

// 	// points[0]  = RPoint(1, 1);
// 	// points[1]  = RPoint(1, 2);
// 	// points[2]  = RPoint(2, 1);
// 	// points[3]  = RPoint(2, 2);
// 	// points[4]  = RPoint(3, 1);
// 	// points[5]  = RPoint(6, 6);
// 	// points[6]  = RPoint(6, 7);
// 	// points[7]  = RPoint(7, 7);
// 	// points[8]  = RPoint(7, 8);
// 	// points[9]  = RPoint(8, 7);
// 	// points[10] = RPoint(8, 8);

// 	// Example 2.
// 	vector<RPoint> points(14);

// 	points[0] = RPoint(0.5, 1.0);
// 	points[1] = RPoint(1.0, 0.5);
// 	points[2] = RPoint(1.0, 1.0);
// 	points[3] = RPoint(1.0, 1.5);
// 	points[4] = RPoint(1.5, 1.0);
// 	points[5] = RPoint(2.0, 2.5);
// 	points[6] = RPoint(2.5, 2.5);
// 	points[7] = RPoint(2.5, 3.0);
// 	points[8] = RPoint(2.5, 3.5);
// 	points[9] = RPoint(4.0, 1.0);
// 	points[10] = RPoint(4.5, 0.5);
// 	points[11] = RPoint(4.5, 1.0);
// 	points[12] = RPoint(4.5, 1.5);
// 	points[13] = RPoint(4.5, 2.0);

// 	//Distances distances;
// 	ClusteringAlogorithm* algo = new NCube();

// 	algo->Process(points);
// 	cout << "MERGES : " << endl;
// 	algo->PrintMerges();
// 	cout << "HEIGHTS : " << endl;
// 	algo->PrintHeights();

// 	return 0;
// }