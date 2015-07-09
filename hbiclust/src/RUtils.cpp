#include "RUtils.h"

namespace R
{
	void Print()
	{
		std::cout << std::endl;
	}
    
    R::ColorVector GetHeatColors(const int& n)
    {
        R::ColorVector colors;
        double incr = 1.0 / double(n);
        double v = 0.0;
        
        double r = 1.0;
        double g = 0.0;
        double b = 0.0;
        
        for(int i = 0; i < n; i++)
        {
            g = v;
            v += incr;
            
            if(v > 1.0) v = 1.0;
            if(g > 1.0) g = 1.0;
            
            colors.emplace_back(R::Color(r, g, b, 1.0));
        }
        
        return colors;
    }
    
    R::ColorVector GetRainbowColors(const int& n)
    {
        R::ColorVector colors;
        
        double separation = 1.0 / 6.0;
        double incr = 1.0 / double(n);
        double v = 0.0;
                
        for(int i = 0; i < n; i++)
        {
            double r = 0.0;
            double g = 0.0;
            double b = 0.0;
            
            double ratio = 0.0;
            
            double t = v;
            
            if(t > 5 * separation)
            {
                ratio = (t  - (5.0 * separation)) / (separation);
                
                r = 1.0;
                g = 0.0;
                b = 1.0 - ratio;
            }
            else if(t > 4 * separation)
            {
                ratio = (t  - (4.0 * separation)) / (separation);
                
                r = ratio;
                g = 0.0;
                b = 1.0;
            }
            else if(t  > 3 * separation)
            {
                ratio = (t  - (3.0 * separation)) / (separation);
                r = 0.0;
                g = 1.0 - ratio;
                b = 1.0; 
            }
            else if(t  > 2 * separation)
            {
                ratio = (t  - (2.0 * separation)) / (separation);
                r = 0.0;
                g = 1.0; 
                b = ratio;
            }
            else if(t  > separation)
            {
                ratio = (t  - separation) / (separation);
                r = 1.0 - ratio;
                g = 1.0; 
                b = 0.0;
            }
            else
            {
                ratio = t / (separation);
                r = 1.0;
                g = ratio;
                b = 0.0;
            }
            
            v += incr;
            
            if(v > 1.0) v = 1.0;
            if(r > 1.0) r = 1.0;
            if(g > 1.0) g = 1.0;
            if(b > 1.0) b = 1.0;
            
            colors.emplace_back(R::Color(r, g, b, 1.0));
        }
        
        return colors;
    }

}