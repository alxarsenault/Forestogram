#include "ClusteringAlgorithm.h"

using namespace std;

//-----------------------------------------------------------------------------
// NCube
//-----------------------------------------------------------------------------
class NCube : public ClusteringAlogorithm
{
public:
	NCube(): ClusteringAlogorithm()
	{
	}

	virtual void Process(const vector<RPoint>& points);

private:
	deque<int> n_merges_vector;
};

