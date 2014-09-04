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
