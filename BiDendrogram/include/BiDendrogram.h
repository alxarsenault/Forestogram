#ifndef __BI_DENDROGRAM__
#define __BI_DENDROGRAM__

#include "RUtils.h"
#include "RMatrix.h"
#include <map>

struct Cluster
{
    Cluster():
    n_merge(0)
    {
        
    }
    
    Cluster(const R::Point& point_, const R::Color& color_):
    point(point_), color(color_),
    n_merge(0)
    {
        
    }
    
    R::Point point;
    R::Color color;
    int n_merge;
    std::vector<int> index_list;
    int small_limit, big_limit;
};

class Dendrogram
{
public:
    Dendrogram(R::Matrix2D<double> merge,
               R::Vector<double> height,
               R::Vector<int> order,
               
               R::Matrix2D<double>& line_points, // Return value.
               R::Vector<double>& answer_limits); // Return value.
    
    void init();
    void process(const double& cut_hight);
    
protected:
    virtual R::Point GetInitalClusterPosition(const double& pos_delta) = 0;
    virtual bool IsLowestPoint(const R::Point& low, const R::Point& high) = 0;
    virtual std::vector<R::Line> GetMergeLines(const double& height,
                                               const R::Point& low,
                                               const R::Point& high) = 0;
    
    virtual bool IsPointAboveHeight(const double& height, const R::Point& point) = 0;
    
    virtual R::Point GetNewClusterCenter(const double& height,
                                         const R::Point& low,
                                         const R::Point& high) = 0;
    
private:
    void AddLinesToMatrix(const int& merge_index,
                          const std::vector<R::Line>& lines,
                          const R::Color& color);
    
    void AssignColorToMergedClusters();
    void ActivateMergedClustersLimit();
    
    void MergeTwoClusters(const int& merge_index,
                          const int& index1,
                          const int& index2,
                          const double& height,
                          const R::Point& low,
                          const R::Point& high);
    
protected:
    R::Matrix2D<double> _merge, _line_points;
    R::Vector<int> _order;
    R::Vector<double> _height, _answer_limits;
    
    std::vector<double> _normHeight;
    std::map<int, Cluster> _clusters;
    int _size;
};

class ColumnDendrogram : public Dendrogram
{
public:
    
    ColumnDendrogram(R::Matrix2D<double> merge,
                     R::Vector<double> height,
                     R::Vector<int> order,
                     
                     R::Matrix2D<double>& line_points, // Return value.
                     R::Vector<double>& answer_limits);
    
protected:
    virtual R::Point GetInitalClusterPosition(const double& pos_delta);
    
    virtual bool IsLowestPoint(const R::Point& low, const R::Point& high);
    
    virtual std::vector<R::Line> GetMergeLines(const double& height,
                                               const R::Point& low,
                                               const R::Point& high);
    
    virtual bool IsPointAboveHeight(const double& height, const R::Point& line);
    
    virtual R::Point GetNewClusterCenter(const double& height,
                                         const R::Point& low,
                                         const R::Point& high);
    
};


class RowDendrogram : public Dendrogram
{
public:
    
    RowDendrogram(R::Matrix2D<double> merge,
                  R::Vector<double> height,
                  R::Vector<int> order,
                  
                  R::Matrix2D<double>& line_points, // Return value.
                  R::Vector<double>& answer_limits);
    
protected:
    virtual R::Point GetInitalClusterPosition(const double& pos_delta);
    virtual bool IsLowestPoint(const R::Point& low, const R::Point& high);
    virtual std::vector<R::Line> GetMergeLines(const double& height,
                                               const R::Point& low,
                                               const R::Point& high);
    virtual bool IsPointAboveHeight(const double& height, const R::Point& line);
    
    virtual R::Point GetNewClusterCenter(const double& height,
                                         const R::Point& low,
                                         const R::Point& high);
};



#endif // __BI_DENDROGRAM__
