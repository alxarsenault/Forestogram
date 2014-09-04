#include "main.h"

template <typename T>
void PrintVector(const deque<T>& vec)
{
	for(int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] <<  " ";
	}

	cout << endl;
}

void NCube::Process(const vector<RPoint>& points)
{
	// Vector to deque conversion.
	deque<RPoint> data(points.size());

	for(int i = 0; i < points.size(); i++)
	{
		data[i] = points[i];
	}

	deque<int> n_merge_vector(points.size(), 1);
	InitDataIndex(data.size());

	int nMerge = 1;

	do
	{
		distances.ProcessDistances(data, data.size());
		vector<RVector>& distMatrix(distances.GetDistancesMatrix());
		
		// Find minimum.
		//----------------------------------------------------------
		double min = 100000000;
		MinInfo min_info;

		for(int j = 0; j < distMatrix.size(); j++)
		{
			for(int i = 0; i < distMatrix[j].size(); i++)
			{
				if(distMatrix[j][i] < min)
				{
					min_info.i = i+0;
					min_info.j = j+1;
					min_info.dist = min = distMatrix[j][i];
				}
			}
		}

		//----------------------------------------------------------

		double total_merge = n_merge_vector[min_info.j] + n_merge_vector[min_info.i];

		// Create new point.
		vector<double> pt(data[0].GetPointVector().size());

		for(int i = 0; i < pt.size(); i++)
		{
			pt[i] = (data[min_info.i].GetPointVector()[i] * 
					 n_merge_vector[min_info.i] + 
				 
				     data[min_info.j].GetPointVector()[i] * 
				     n_merge_vector[min_info.j]) / total_merge;
		}

		//cout << "MERGES :: " << endl;
		cout << "Merge #" << nMerge << endl;
		for(int n = 0; n < data.size(); n++)
		{
			cout << "Index : " << data_index[n];
			data[n].Print();
		}
		cout << "Merge : " << data_index[min_info.i] << " and "<< data_index[min_info.j] << " with distances of : " << min_info.dist << endl << endl;


		// Add to merge vectors.
		heights.push_back(min_info.dist);
		merges.push_back(Merge(data_index[min_info.i], data_index[min_info.j]));

		// Reformat data vector.
		data.erase(data.begin() + min_info.i);
		data.erase(data.begin() + min_info.j-1);
		data.push_front(pt);

		// Reformat n_merge_vector.
		n_merge_vector.erase(n_merge_vector.begin() + min_info.i);
		n_merge_vector.erase(n_merge_vector.begin() + min_info.j-1);
		n_merge_vector.push_front((int)total_merge);

		// Reformat data_index vector.
		data_index.erase(data_index.begin() + min_info.i);
		data_index.erase(data_index.begin() + min_info.j-1);
		data_index.push_front(nMerge);

		nMerge++;

	} while(data.size() > 1);
}


int main()
{
	// vector<RPoint> points(11);

	// points[0]  = RPoint(1, 1);
	// points[1]  = RPoint(1, 2);
	// points[2]  = RPoint(2, 1);
	// points[3]  = RPoint(2, 2);
	// points[4]  = RPoint(3, 1);
	// points[5]  = RPoint(6, 6);
	// points[6]  = RPoint(6, 7);
	// points[7]  = RPoint(7, 7);
	// points[8]  = RPoint(7, 8);
	// points[9]  = RPoint(8, 7);
	// points[10] = RPoint(8, 8);

	// Example 2.
	vector<RPoint> points(14);

	points[0] = RPoint(0.5, 1.0);
	points[1] = RPoint(1.0, 0.5);
	points[2] = RPoint(1.0, 1.0);
	points[3] = RPoint(1.0, 1.5);
	points[4] = RPoint(1.5, 1.0);
	points[5] = RPoint(2.0, 2.5);
	points[6] = RPoint(2.5, 2.5);
	points[7] = RPoint(2.5, 3.0);
	points[8] = RPoint(2.5, 3.5);
	points[9] = RPoint(4.0, 1.0);
	points[10] = RPoint(4.5, 0.5);
	points[11] = RPoint(4.5, 1.0);
	points[12] = RPoint(4.5, 1.5);
	points[13] = RPoint(4.5, 2.0);

	//Distances distances;
	ClusteringAlogorithm* algo = new NCube();

	algo->Process(points);
	cout << "MERGES : " << endl;
	algo->PrintMerges();
	cout << "HEIGHTS : " << endl;
	algo->PrintHeights();

	return 0;
}