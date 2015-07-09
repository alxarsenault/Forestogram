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
        // Merging clusters index.
        int index1 = _merge(i, 0);
        int index2 = _merge(i, 1);
        
        // Find highest cluster center.
        R::Point low(_clusters[index1].point);
        R::Point high(_clusters[index2].point);
        
        if(!IsLowestPoint(low, high))
        {
            std::swap(low, high);
        }

        // Get merged clusters drawing lines position.
        std::vector<R::Line> lines = GetMergeLines(_normHeight[i], low, high);

        // Determine if new cluster is above cutting height.
        if(IsPointAboveHeight(norm_cut_hight, lines[2].pt2))
        {
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
        
        // Add merging cluster lines points to matrix.
        AddLinesToMatrix(merge_index, lines, R::Color(0.0, 0.0, 0.0, 1.0));
        
        // Change all cluster color and add limits to each cluster.
        if(is_first_time_cut)
        {
            AssignColorToMergedClusters();
            ActivateMergedClustersLimit();
        }
        
        // Merge both cluster in the cluster map.
        MergeTwoClusters(merge_index, index1, index2, _normHeight[i], low, high);
        merge_index++;
    }
}


void Dendrogram::AddLinesToMatrix(const int& merge_index,
                                  const std::vector<R::Line>& lines,
                                  const R::Color& color)
{
    int index = merge_index - 1;
    
    // Low line.
    _line_points(index, 0) = lines[0].pt1.x;
    _line_points(index, 1) = lines[0].pt1.y;
    
    _line_points(index, 2) = lines[0].pt2.x;
    _line_points(index, 3) = lines[0].pt2.y;
    
    // High line.
    _line_points(index, 4) = lines[1].pt1.x;
    _line_points(index, 5) = lines[1].pt1.y;
    
    _line_points(index, 6) = lines[1].pt2.x;
    _line_points(index, 7) = lines[1].pt2.y;
    
    // Cross line.
    _line_points(index, 8) = lines[2].pt1.x;
    _line_points(index, 9) = lines[2].pt1.y;
    
    _line_points(index, 10) = lines[2].pt2.x;
    _line_points(index, 11) = lines[2].pt2.y;
    
    
    // Color.
    _line_points(index, 12) = color.r;
    _line_points(index, 13) = color.g;
    _line_points(index, 14) = color.b;
    _line_points(index, 15) = 1.0;//color.a;
}

void Dendrogram::AssignColorToMergedClusters()
{
    R::ColorVector colors = R::GetRainbowColors(_clusters.size());
    
    int i = 0;
    for(auto& clust : _clusters)
    {
        R::Color c = colors[i++];
        
        for(auto& k : clust.second.index_list)
        {
            _line_points(k, 12) = c.r;
            _line_points(k, 13) = c.g;
            _line_points(k, 14) = c.b;
            _line_points(k, 15) = 1.0;
        }
    }
}

void Dendrogram::ActivateMergedClustersLimit()
{
    for(auto& clust : _clusters)
    {
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

void Dendrogram::MergeTwoClusters(const int& merge_index,
                                  const int& index1,
                                  const int& index2,
                                  const double& height,
                                  const R::Point& low,
                                  const R::Point& high)
{
    Cluster& clust1(_clusters[index1]);
    Cluster& clust2(_clusters[index2]);
    
    // New cluster created.
    Cluster& m_clust(_clusters[merge_index]);
    
    // Update new cluster info.
    m_clust.point = GetNewClusterCenter(height, low, high);
    m_clust.color = R::Color(0.0, 0.0, 0.0, 1.0);
    m_clust.n_merge = clust1.n_merge + clust2.n_merge + 1;
    
    // Merge both cluster index list.
    std::vector<int> index_list1 = clust1.index_list;
    std::vector<int> index_list2 = clust2.index_list;
    index_list1.insert(index_list1.end(), index_list2.begin(), index_list2.end());
    
    m_clust.index_list = index_list1;
    m_clust.index_list.push_back(merge_index - 1);
    
    // Find new limits.
    m_clust.small_limit = std::min(clust1.small_limit, clust2.small_limit);
    m_clust.big_limit = std::max(clust1.big_limit, clust2.big_limit);

    // Remove old cluster.
    _clusters.erase(index1);
    _clusters.erase(index2);
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



