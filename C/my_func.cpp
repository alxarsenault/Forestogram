#include <iostream>
#include <vector>

using namespace std;

double test_cube(double x)
{
	return x * x * x;
}

extern "C" 
{
	void power(double *x)
	{
		*x *= *x;
	}

	void cube(double *x)
	{
		// *x *= (*x * *x);

		*x = test_cube(*x);
	}

	void mytest(double* x, int *n)
	{
		// vector<double> v(std::begin(x), std::end(x));

		// cout << v.size() << endl;
		for(int i = 0; i < *n; ++i)
		{
			cout << x[i] << " ";
		}
		cout << "TEST" << endl;
	}
}
