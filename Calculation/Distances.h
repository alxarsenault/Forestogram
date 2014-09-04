#ifndef __DISTANCES__
#define __DISTANCES__
#include "Utils.h"

//-----------------------------------------------------------------------------
// Distances
//-----------------------------------------------------------------------------
class Distances
{
public: 
	Distances(const int& N);
	Distances(const Distances& dist);
	Distances();

	void CreateDistancesArray(const int& N);
	void ProcessDistances(const deque<RPoint>& points, const int& N);
	
	//MinInfo FindMin();
	int GetSize() const;
	void Print();

	vector<RVector>& GetDistancesMatrix()
	{
		return distances;
	}

private:
	vector<RVector> distances;
	int size;
};

#endif // __DISTANCES__
