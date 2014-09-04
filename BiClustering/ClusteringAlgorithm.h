#ifndef __CLUSTERING_ALGORITHM__
#define __CLUSTERING_ALGORITHM__

#include "Utils.h"
#include "Distances.h"

//-----------------------------------------------------------------------------
// ClusteringAlogorithm
//-----------------------------------------------------------------------------
class ClusteringAlogorithm
{
public:
	ClusteringAlogorithm();

	virtual void Process(const vector<RPoint>& points) = 0;

	double* GetMerges(int& size)
	{
		double* m = new double[merges.size() * 2];

		int k = 0;

		size = merges.size() * 2;

		for(int i = 0; i < merges.size(); i++)
		{
			m[k] = merges[i].i;
			m[k+1] = merges[i].j;
			k += 2;
		}

		return m;
	}

	double* GetHeights(int& size)
	{
		size = heights.size();
		return heights.data();
	}

	void PrintMerges() const
	{
		for(int i = 0; i < merges.size(); i++)
		{
			merges[i].Print();
		}
	}

	void PrintHeights() const
	{
		for(int i = 0; i < heights.size(); i++)
		{
			cout << heights[i] << endl;
		}
	}
protected:
	Distances distances;

	deque<int> data_index;
	vector<Merge> merges;
	vector<double> heights;

	void InitDataIndex(const int& size);
};

#endif // __CLUSTERING_ALGORITHM__
