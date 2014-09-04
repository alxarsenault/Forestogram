#include "ClusteringAlgorithm.h"

ClusteringAlogorithm::ClusteringAlogorithm()
{
	//distances = dist;
	//InitDataIndex(dist.GetSize());
}


void ClusteringAlogorithm::InitDataIndex(const int& size)
{
	data_index.resize(size);

	for(int i = 0; i < size; i++)
	{
		data_index[i] = -(i+1);
	}
}