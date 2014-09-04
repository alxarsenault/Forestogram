#include "Distances.h"

Distances::Distances()
{
}

Distances::Distances(const int& N)
{
	CreateDistancesArray(N);
	//ProcessDistances(points);
}

Distances::Distances(const Distances& dist)
{
	distances = dist.distances;
	size = dist.size;
}

int Distances::GetSize() const
{
	return size;
}

void Distances::ProcessDistances(const deque<RPoint>& points, const int& N)
{
	CreateDistancesArray(N);

	for(int j = 0; j < distances.size(); j++)
	{
		for(int i = 0; i < distances[j].size(); i++)
		{
			distances[j][i] = points[j+1].Dist(points[i]);
		}
	}
}

void Distances::CreateDistancesArray(const int& N)
{
	distances.resize(N-1);
	size = N;

	// Init size loop.
	for(int i = 0; i < N-1; i++)
	{
		distances[i].resize(i+1);
	}
}

// MinInfo Distances::FindMin()
// {
// 	double min = 100000000;

// 	MinInfo min_info;

// 	for(int j = 0; j < distances.size(); j++)
// 	{
// 		for(int i = 0; i < distances[j].size(); i++)
// 		{
// 			if(distances[j][i] < min)
// 			{
// 				min_info.i = i+1;
// 				min_info.j = j+2;
// 				min_info.dist = min = distances[j][i];
// 			}
// 		}
// 	}

// 	// double total_merge = n_merge_vector[min_info.j].n_merge + n_merge_vector[min_info.i].n_merge;

// 	// min_info.value = (n_merge_vector[min_info.j] * 
// 	// 				  n_merge_vector[min_info.j].value + 
// 	// 				  n_merge_vector[min_info.i] * 
// 	// 				  n_merge_vector[min_info.i].value) / total_merge;

// 	// min_info.n_merge = total_merge;
// 	// return min_info;
// }

void Distances::Print()
{
	for(int i = 0; i < distances.size(); i++)
	{
		std::cout.width(9);
		cout << right << i+1;
	}
	cout << endl;

	for(int j = 0; j < distances.size(); j++)
	{
		std::cout.width(3);
		cout << left << j+2 << " : ";

		for(int i = 0; i < distances[j].size(); i++)
		{
			std::cout.width(8);
			cout << left << fixed << distances[j][i] << " ";
		}

		cout << endl;
	}
}
