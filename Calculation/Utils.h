#ifndef __UTILS_H__
#define __UTILS_H__

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <deque>

using namespace std;

//-----------------------------------------------------------------------------
// Point
//-----------------------------------------------------------------------------
template<typename T>
class Point
{
public:
	Point(const vector<T>& pt)
	{
		point = pt;
	}

	Point(const Point<T>& pt)
	{
		point = pt.point;
	}

	Point()
	{
	}

	Point(const T& x, const T& y)
	{
		point.push_back(x);
		point.push_back(y);
	}

	// Could be a bit faster with pointer arithmetic using vector data array.
	T Dist(const Point<T>& pt) const
	{
		T dist = pow(point[0] - pt.point[0], 2.0);

		for(int i = 1; i < point.size(); i++)
		{
			dist += pow(point[i] - pt.point[i], 2.0);
		}

		return sqrt(dist);
	}

	vector<T> GetPointVector() const
	{
		return point;
	}

	void Print() const
	{
		cout << "(";
		for(int i = 0; i < point.size() - 1; i++)
		{
			cout << point[i] << ", ";
		}
		cout << point[point.size()-1] << ")" << endl;
	}


private:
	vector<T> point;
};

typedef Point<double> RPoint;
typedef vector<double> RVector;

//-----------------------------------------------------------------------------
// Merge
//-----------------------------------------------------------------------------
struct Merge
{
	Merge(int jj, int ii)
	{
		i = ii;
		j = jj;
	}
	int i, j;

	void Print() const
	{
		cout << i << " " << j << endl;
	}
};

//-----------------------------------------------------------------------------
// MinInfo
//-----------------------------------------------------------------------------
class MinInfo
{
public:
	MinInfo(){}

	MinInfo(const int& jj, 
			const int& ii, 
			const double& distance):
			i(ii),
			j(jj),
			dist(distance)
	{

	}

	void Print()
	{
		cout << "[" << j << ", " << i << "] : " << endl; 
	}

	int j, i;
	double dist;//, value;
	// int n_merge;
};

#endif // __UTILS_H__