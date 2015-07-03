#ifndef __R_UTILS__
#define __R_UTILS__

#include <iostream>

namespace R
{
	// Since variadic templates are recursive, must have a base case.
    void Print();
    
    template <typename T, typename ...P>
    void Print(T t, P ...p)
    {
        std::cout << t << ' ';
        {
            Print(p...);
        }
    }

	template<typename T>
	struct Size2D_T
	{
		Size2D_T(const T& nrow = 0, const T& ncol = 0):
		row(nrow), col(ncol)
		{

		}

		T row, col;
	};

	typedef Size2D_T<unsigned int> Size2D;
}

#endif // __R_UTILS__
