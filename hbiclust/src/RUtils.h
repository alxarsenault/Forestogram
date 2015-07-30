#ifndef __R_UTILS__
#define __R_UTILS__

#include <iostream>
#include <vector>

namespace R
{
	// Since variadic templates are recursive, must have a base case.
//    void Print();
//    
//    template <typename T, typename ...P>
//    void Print(T t, P ...p)
//    {
//        std::cout << t << ' ';
//        {
//            Print(p...);
//        }
//    }

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
    
    template<typename T>
    struct Point2D_T
    {
        Point2D_T()
        {
            
        }
        
        Point2D_T(const T& X, const T& Y):
        x(X), y(Y)
        {
            
        }
        
        T x, y;
    };
    
    typedef Point2D_T<double> Point;
    
    template<typename T>
    struct Line_T
    {
        Line_T(const Point2D_T<T>& p1, const Point2D_T<T>& p2):
        pt1(p1), pt2(p2)
        {
            
        }
        
        Point2D_T<T> pt1, pt2;
    };
    
    typedef Line_T<double> Line;
    
    template<typename T>
    struct Color_T
    {
        Color_T()
        {
            
        }
        
        Color_T(const T& R,
                const T& G,
                const T& B,
                const T& A):
        r(R), g(G), b(B), a(A)
        {
            
        }
        
        T r, g, b, a;
    };
    
    typedef Color_T<double> Color;
    typedef std::vector<Color> ColorVector;
    
    R::ColorVector GetHeatColors(const int& n);
    R::ColorVector GetRainbowColors(const int& n);

}

#endif // __R_UTILS__
