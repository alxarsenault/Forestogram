#include "BiDendrogram.h"
#include <utility>

Dendrogram::Dendrogram(R::Matrix2D<double> merge,
                       R::Vector<double> height,
                       R::Vector<int> order,
                       R::Matrix2D<double>& line_points, // Return value.
                       R::Vector<double>& answer_limits):
_merge(merge),
_order(order),
_height(height),
_line_points(line_points),
_answer_limits(answer_limits),
_normHeight(_height.size()),
_size(_height.size() + 1)
{
    
}

void Dendrogram::init()
{
    // Set all limits to zero.
    for(auto& n : _answer_limits)
    {
        n = 0.0;
    }
    
    // Create normalize height vector.
    double hight_sum = _height[_height.size() - 1];
    
    for(int i = 0; i < _normHeight.size(); i++)
    {
        _normHeight[i] = (_height[i] / hight_sum);
    }
    
    double half_pos = (1.0 / double(_size)) * 0.5;
    
    for(int i = 0; i < _size; i++)
    {
        int index = -_order[i];
        
//        _clusters[index].point = R::Point((i / double(_size)) + half_pos, 0.0);
        double pos_delta = i / double(_size) + half_pos;
        _clusters[index].point = GetInitalClusterPosition(pos_delta);
        
        _clusters[index].color = R::Color(0.0, 0.0, 0.0, 1.0);
        _clusters[index].small_limit = i;
        _clusters[index].big_limit = i;
    }
}

void Dendrogram::process(const double& cut_hight)
{
    int merge_index = 1;
    
    bool as_reach_cutting_hight = false;
    bool is_first_time_cut = false;
    
    double norm_cut_hight = cut_hight / _height[_height.size() - 1];
    
    for(int i = 0; i < _merge.size().row; i++)
    {
        int index1 = _merge(i, 0);
        int index2 = _merge(i, 1);
        
        // Find highest center.
        R::Point low(_clusters[index1].point);
        R::Point high(_clusters[index2].point);
        
        //------------------------------------------------------------------------
//        if(low.y > high.y)
        if(!IsLowestPoint(low, high))
        //------------------------------------------------------------------------
        {
            std::swap(low, high);
        }
        
        
        
        
        
        //------------------------------------------------------------------------
//        double y_final = _normHeight[i];
//        
//        R::Line low_line(low, R::Point(low.x, y_final));
//        R::Line high_line(high, R::Point(high.x, y_final));
//        R::Line cross_line(low_line.pt2, high_line.pt2);
        
        std::vector<R::Line> lines = GetMergeLines(_normHeight[i], low, high);
        //std::vector<R::Line> GetMergeLines(const double& height, const R::Point& low, const R::Point& high);
        //------------------------------------------------------------------------
        
        
        
        
        R::Color color(0.0, 0.0, 0.0, 1.0);
        
//        if(high_line.pt2.y > norm_cut_hight)
        if(IsPointAboveHeight(norm_cut_hight, lines[2].pt2))
        {
            color = R::Color(0.0, 0.0, 0.0, 1.0);
            
            if(as_reach_cutting_hight == false)
            {
                is_first_time_cut = true;
                as_reach_cutting_hight = true;
            }
            else
            {
                is_first_time_cut = false;
            }
        }
        
        
        
        AddLinesToMatrix(merge_index, _line_points,
                         lines[0], lines[1], lines[2], color);
        
        
        
        
        
        
        // Change all cluster color.
        if(is_first_time_cut)
        {
            std::size_t n_cluster = _clusters.size();
            
            R::ColorVector colors = R::GetRainbowColors(n_cluster);
            
            int i = 0;
            for(auto& clust : _clusters)
            {
                R::Color c = colors[i++];
                
                for(auto& i : clust.second.index_list)
                {
                    _line_points(i, 12) = c.r;
                    _line_points(i, 13) = c.g;
                    _line_points(i, 14) = c.b;
                    _line_points(i, 15) = 1.0;
                }
                
                // Set limits.
                for(int i = 0; i < _size; i++)
                {
                    if(i == clust.second.small_limit)
                    {
                        _answer_limits[i] = 1.0;
                    }
                }
            }
        }
        
        
        
        //------------------------------------------------------------------------
        // Add new cluster.
//        _clusters[merge_index].point = R::Point((low.x + high.x) * 0.5, y_final);
        
        _clusters[merge_index].point = GetNewClusterCenter(_normHeight[i], low, high);
        //R::Point GetNewClusterCenter(const double& height, const R::Point& low, const R::Point& high);
        
        _clusters[merge_index].color = color;
        _clusters[merge_index].n_merge = _clusters[index1].n_merge + _clusters[index2].n_merge + 1;
        
        std::vector<int> index_list1 = _clusters[index1].index_list;
        std::vector<int> index_list2 = _clusters[index2].index_list;
        index_list1.insert(index_list1.end(), index_list2.begin(), index_list2.end());
        
        _clusters[merge_index].index_list = index_list1;
        _clusters[merge_index].index_list.push_back(merge_index - 1);
        
        _clusters[merge_index].small_limit = std::min(_clusters[index1].small_limit, _clusters[index2].small_limit);
        _clusters[merge_index].big_limit = std::max(_clusters[index1].big_limit, _clusters[index2].big_limit);
        //------------------------------------------------------------------------
        
        // if(as_reach_cutting_hight)
        // {
        // 	// as_reach_cutting_hight = false;
        // }
        
        // Remove old cluster.
        _clusters.erase(index1);
        _clusters.erase(index2);
        
        merge_index++;
    }
}







void Dendrogram::AddLinesToMatrix(const int& merge_index,
                                  R::Matrix2D<double>& lines,
                                  const R::Line& low,
                                  const R::Line& high,
                                  const R::Line& cross,
                                  const R::Color& color)
{
    int index = merge_index - 1;
    
    // Low line.
    lines(index, 0) = low.pt1.x;
    lines(index, 1) = low.pt1.y;
    
    lines(index, 2) = low.pt2.x;
    lines(index, 3) = low.pt2.y;
    
    // High line.
    lines(index, 4) = high.pt1.x;
    lines(index, 5) = high.pt1.y;
    
    lines(index, 6) = high.pt2.x;
    lines(index, 7) = high.pt2.y;
    
    // Cross line.
    lines(index, 8) = cross.pt1.x;
    lines(index, 9) = cross.pt1.y;
    
    lines(index, 10) = cross.pt2.x;
    lines(index, 11) = cross.pt2.y;
    
    lines(index, 12) = color.r;
    lines(index, 13) = color.g;
    lines(index, 14) = color.b;
    lines(index, 15) = 1.0;//color.a;
}




















ColumnDendrogram::ColumnDendrogram(R::Matrix2D<double> merge,
                                   R::Vector<double> height,
                                   R::Vector<int> order,
                                   R::Matrix2D<double>& line_points,
                                   R::Vector<double>& answer_limits):
Dendrogram(merge, height, order, line_points, answer_limits)
{
    
}

R::Point ColumnDendrogram::GetInitalClusterPosition(const double& pos_delta)
{
    return R::Point(pos_delta, 0.0);
}

bool ColumnDendrogram::IsLowestPoint(const R::Point& low, const R::Point& high)
{
    return low.y < high.y;
}

std::vector<R::Line> ColumnDendrogram::GetMergeLines(const double& height,
                                                     const R::Point& low,
                                                     const R::Point& high)
{
    R::Line low_line(low, R::Point(low.x, height));
    R::Line high_line(high, R::Point(high.x, height));
    R::Line cross_line(low_line.pt2, high_line.pt2);
    
    return std::vector<R::Line>{low_line, high_line, cross_line};
}

bool ColumnDendrogram::IsPointAboveHeight(const double& height,
                                         const R::Point& point)
{
    return point.y > height;
}

R::Point ColumnDendrogram::GetNewClusterCenter(const double& height,
                                               const R::Point& low,
                                               const R::Point& high)
{
    return R::Point((low.x + high.x) * 0.5, height);
}









RowDendrogram::RowDendrogram(R::Matrix2D<double> merge,
                             R::Vector<double> height,
                             R::Vector<int> order,
                             R::Matrix2D<double>& line_points,
                             R::Vector<double>& answer_limits):
Dendrogram(merge, height, order, line_points, answer_limits)
{
    
}

R::Point RowDendrogram::GetInitalClusterPosition(const double& pos_delta)
{
    return R::Point(0.0, pos_delta);
}

bool RowDendrogram::IsLowestPoint(const R::Point& low, const R::Point& high)
{
    return low.x < high.x;
}

std::vector<R::Line> RowDendrogram::GetMergeLines(const double& height,
                                                  const R::Point& low,
                                                  const R::Point& high)
{
    R::Line low_line(low, R::Point(height, low.y));
    R::Line high_line(high, R::Point(height, high.y));
    R::Line cross_line(low_line.pt2, high_line.pt2);
    
    return std::vector<R::Line>{low_line, high_line, cross_line};
}

bool RowDendrogram::IsPointAboveHeight(const double& height, const R::Point& point)
{
    return point.x > height;
}

R::Point RowDendrogram::GetNewClusterCenter(const double& height,
                                            const R::Point& low,
                                            const R::Point& high)
{
    return R::Point(height, (low.y + high.y) * 0.5);
}



