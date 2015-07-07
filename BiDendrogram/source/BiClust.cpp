#include "BiClust.h"

#include <cmath>
#include <algorithm>
#include <string>
#include <vector>






BiClust::BiClust()
{
    
}

ClusterData BiClust::initClusterData(const R::Matrix2D<double>& data)
{
    ClusterData clusters(data.size().row);
    
    int ncol = data.size().col;
    
    for(int j = 0; j < clusters.size(); j++)
    {
        clusters[j].n_row_clust = 1;
        clusters[j].name = std::to_string(-(j+1));
        clusters[j].index_list = std::vector<int>(j);
        
        auto& v = clusters[j].center.getStdVector();
        v.resize(ncol);
        
        for(int i = 0; i < ncol; i++)
        {
            v[i] = data(j, i);
        }
    }
    
    return clusters;
}

Matrix BiClust::initDistanceMatrix(const R::Matrix2D<double>& data)
{
    int nrow = data.size().row;
    
    Matrix distMatrix(nrow);
    
    for(auto& n : distMatrix)
    {
        n.resize(nrow);
        std::fill_n(n.begin(), nrow, 0.0);
    }
    
    return distMatrix;
}

void BiClust::calculateDistances(const ClusterData& clusters, Matrix& distMatrix)
{
    for(int i = 0; i < clusters.size(); i++)
    {
        for(int k = i + 1; k < clusters.size(); k++)
        {
            distMatrix[i][k] = clusters[i].center.Dist(clusters[k].center);
        }
    }
}

std::pair<int, int> BiClust::getNextMergeVectorsIndex(const ClusterData& clusters,
                                                      const Matrix& distMatrix)
{
    double min = 10000000.0;
    std::pair<int, int> min_index(-1, -1);
    
    for(int i = 0; i < clusters.size(); i++)
    {
        for(int k = i + 1; k < clusters.size(); k++)
        {
           if(distMatrix[i][k] < min)
           {
               min = distMatrix[i][k];
               min_index = std::pair<int, int>(i, k);
           }
        }
    }
    
    return min_index;
}

void BiClust::mergeTwoCluster(ClusterData& clusters,
                              const std::pair<int, int>& merge,
                              const int& merge_index)
{
    ax::Cluster& c1 = clusters[merge.first];
    ax::Cluster& c2 = clusters[merge.second];
    
    double n_merge = c1.n_row_clust + c2.n_row_clust;
    c1.center = ((c1.center * c1.n_row_clust) + (c2.center * c2.n_row_clust)) / n_merge;
    
    c1.n_row_clust = n_merge;
    c1.name = std::to_string(merge_index);
    
    c1.index_list.insert(c1.index_list.end(),
                         c1.index_list.begin(),
                         c1.index_list.end());
    
    clusters.erase(clusters.begin() + merge.second);
}

//std::pair<int, int> DistVectorIndexToVectorIndex(const int& index,
//                                                 const int& nVector)
//{
//    for(int i = 0, vec_index = 0; i < nVector; i++)
//    {
//        for(int k = i + 1; k < nVector; k++)
//        {
//            if(vec_index++ == index)
//            {
//                return std::pair<int, int>(i, k);
//            }
//        }
//    }
//    
//    return std::pair<int, int>(-1, -1);
//}

//std::vector<double> CalculateDistances(const int& nDist,
//                                       const std::vector<ax::Cluster>& clusters)
//{
//    std::vector<double> dist_vector(nDist);
//    
//    for(int i = 0, vec_index = 0; i < clusters.size(); i++)
//    {
//        for(int k = i + 1; k < clusters.size(); k++)
//        {
//            dist_vector[vec_index++] = clusters[i].center.Dist(clusters[k].center);
//        }
//    }
//    
//    return dist_vector;
//}

//std::pair<int, int> GetClosestVectorIndex(std::vector<double> dist_vector,
//                                          const int& nVector,
//                                          double& distance)
//{
////    std::vector<double>::iterator result = std::min_element(dist_vector.begin(),
////                                                            dist_vector.end());
////    
////    distance = *result;
////    
////    int index = std::distance(dist_vector.begin(), result);
//    
//    double min = 10000000.0;
//    int index = -1 ;
//    for(int i = 0; i < dist_vector.size(); i++)
//    {
//        if(dist_vector[i] < min)
//        {
//            min = dist_vector[i];
//            index = i;
//        }
//    }
//    
//    distance = min;
//    return DistVectorIndexToVectorIndex(index, nVector);
////
////    return DistVectorIndexToVectorIndex(index, nVector);
//
//}

//void MergeTwoCluster(std::vector<ax::Cluster>& clusters,
//                     const std::pair<int, int>& index,
//                     const int& merge_index,
//                     std::vector<std::pair<std::string, std::string>>& merge_matrix)
//{
//    ax::Cluster& c1 = clusters[index.first];
//    ax::Cluster& c2 = clusters[index.second];
//
//    
//    merge_matrix.emplace_back(std::pair<std::string, std::string>(c1.name, c2.name));
//    
//    double n_merge = c1.n_row_clust + c2.n_row_clust;
//    c1.center = ((c1.center * c1.n_row_clust) + (c2.center * c2.n_row_clust)) / n_merge;
//    
//    c1.n_row_clust = n_merge;
//    c1.name = std::to_string(merge_index);
//    
//    c1.index_list.insert(c1.index_list.end(), c1.index_list.begin(), c1.index_list.end());
//    
//    clusters.erase(clusters.begin() + index.second);
//}

//double DistValue(const int& i1, const int& i2,
//                 const std::vector<double>& global_dist,
//                 const int& nVector)
//{
//    
////    return global_dist[i1 * ];
//    
//    for(int i = 0, vec_index = 0; i < nVector; i++)
//    {
//        for(int k = i + 1; k < nVector; k++)
//        {
//                if((i1 == i && i2 == k) || (i1 == k && i2 == i))
//                {
//                    return global_dist[vec_index];
//                }
//            
//            vec_index++;
//        }
//    }
//
//    
//    
//    return -10000.0;
//}

//double DistBetwwenTwoClust(const std::vector<double>& global_dist,
//                           const ax::Cluster& c1, const ax::Cluster& c2,
//                           const int& nVector)
//{
//    double sum_dist = 0.0;
//    
//    
////    for(int i = 0; i < c1.index_list.size(); i++)
//    for(auto& n : c1.index_list)
//    {
////        for(int k = 0; k < c2.index_list.size(); k++)
//        for(auto& k : c2.index_list)
//        {
//            sum_dist += DistValue(n, k, global_dist, nVector);
//        }
//    }
//    
//    return sum_dist / (c1.n_row_clust * c2.n_row_clust);
//}
//
//std::pair<int, int> FindNextMerge(const std::vector<double>& global_dist,
//                                  std::vector<ax::Cluster>& clusters)
//{
//    for(int i = 0; i < clusters.size(); i++)
//    {
//        
//    }
//}

void BiClust::process(const R::Matrix2D<double>& data)
{
    ClusterData clusters = initClusterData(data);
    Matrix distMatrix = initDistanceMatrix(data);
    
    calculateDistances(clusters, distMatrix);
    
    
    int merge_index = 1;
    
    std::pair<int, int> merge = getNextMergeVectorsIndex(clusters, distMatrix);
    
    R::Print("MERGE :", merge.first, merge.second);
    
    mergeTwoCluster(clusters, merge, merge_index);
    
//    R::Print("BiClust::process");
    
//    int nVector = data.size().row;
    
//    std::vector<ax::Cluster> clusters(nVector);
//    InitClusterData(clusters, data);

    
    
//    int nDist = nVector * (nVector - 1) * 0.5;
    
//    R::Print("Size  :", data.size().row, data.size().col);
//    R::Print("NDist :", nDist);
    
    
    //--------------------------------------------------------------------------
    // Init cluster data.
    
//    int merge_index = 1;
//    std::vector<std::pair<std::string, std::string>> merge_matrix;
//    std::vector<double> heights;
//    
    
    
//    R::Print("DISTANCEEEE  :", clusters[50 - 1].center.Dist(clusters[51 - 1].center));
//    
//    
//    ax::Math::Vector<double> bb = clusters[45 - 1].center + clusters[46 - 1].center;
//    bb = bb * 0.5;
//    R::Print("DISTANCEEEE  :", bb.Dist(clusters[44 - 1].center));
//    
//    
//    double dd = clusters[45 - 1].center.Dist(clusters[44 - 1].center);
//    dd += clusters[46 - 1].center.Dist(clusters[44 - 1].center);
//    
//    dd *= 0.5;
//    
//    R::Print("AVEAGGART  :", dd);

//    int nDist = clusters.size() * (clusters.size() - 1) / 2;
//    std::vector<double> global_dist(CalculateDistances(nDist, clusters));
    
//    std::vector<std::vector<double>> global_dist(CalculateDistances(nDist, clusters));
//    std::vector<std::vector<double>> global_distances(data.size().row * data.size().col);
    
    
    
//    while(clusters.size() > 1)
//    {
////        int nDist = clusters.size() * (clusters.size() - 1) / 2;
////        std::vector<double> dist_vector(CalculateDistances(nDist, clusters));
//        
//        double dist_min = 100000000.0;
//        std::pair<int, int> merge_pair;
//        
//        for(int j = 0; j < clusters.size(); j++)
//        {
//            for(int i = j + 1; i < clusters.size(); i++)
//            {
//                double d = DistBetwwenTwoClust(global_dist,
//                                               clusters[i], clusters[j],
//                                               nVector);
//                if(d < dist_min)
//                {
//                    dist_min = d;
//                    merge_pair = std::pair<int, int>(i, j);
//                }
//            }
//        }
//        
//        double DistBetwwenTwoClust(const std::vector<double>& global_dist,
//                                   const ax::Cluster& c1, const ax::Cluster& c2)
//        std::pair<int, int> min_dist = GetClosestVectorIndex(dist_vector,
//                                                             clusters.size(),
//                                                             dist);
        
//        if(min_dist.first == min_dist.second)
//        {
//            R::Print("CLOSEST ERROR");
//        }
        
//         MergeTwoCluster(clusters, merge_pair, merge_index, merge_matrix);
//        MergeTwoCluster(clusters, min_dist, merge_index, merge_matrix);
        
//        R::Print(dist);
        
        
//        if(heights.size())
//        {
//            double l_height = heights[heights.size() - 1];
//            heights.push_back(l_height + dist - l_height);
//        }
//        else
//        {
//            heights.push_back(dist_min);
////        }
//        
//        merge_index++;
//    }
    
    
    
    
    // Merge two cluster.
//    int i = 1;
//    for(auto& n : merge_matrix)
//    {
//        R::Print(i++, " : ", n.first, n.second);
//    }
//    
//    
//    for(auto& n : heights)
//    {
//        R::Print(n);
//    }
    
    
    
    
    // Find all distance values.
//    std::vector<double> dist_vector(nDist);
//    
//    for(int i = 0, vec_index = 0; i < nVector; i++)
//    {
//        for(int k = i + 1; k < nVector; k++)
//        {
//            dist_vector[vec_index++] = clusters[i].center.Dist(clusters[k].center);
//        }
//    }
    
//    std::vector<double>::iterator result = std::min_element(dist_vector.begin(),
//                                                            dist_vector.end());
//    
//    int index = std::distance(dist_vector.begin(), result);
//    
//    std::pair<int, int> min_dist = DistVectorIndexToVectorIndex(index, nVector);
    
//    R::Print("MERGE :", min_dist.first, min_dist.second);
//    
//    R::Print("DIST -> ", clusters[min_dist.first].center.Dist(clusters[min_dist.second].center));
//    
    
//    int ncol = data.size().col;
//    
//    for(int j = 0; j < nVector; j++)
//    {
//        clusters_data[j].n_vector = 1;
//        auto& v = clusters_data[j].center.getStdVector();
//        v.resize(ncol);
//        
//        for(int i = 0; i < v.size(); i++)
//        {
//            v[i] = data(j, i);
//        }
//    }
    
    
    
//    std::vector<axMathVec> data_vectors(nVector);
//
//    for(int j = 0; j < data.size().row; j++)
//    {
//        axMathVec vec(data.size().col);
//        
//        for(int i = 0; i < vec.size(); i++)
//        {
//            vec[i] = data(j, i);
//        }
//        
//        data_vectors[j] = vec;
//    }
    //--------------------------------------------------------------------------
    
    
//    // Find all distance values.
//    std::vector<double> dist_vector(nDist);
//    
//    int vec_index = 0;
//    
//    for(int i = 0; i < nVector; i++)
//    {
//        for(int k = i + 1; k < nVector; k++)
//        {
//            dist_vector[vec_index++] = data_vectors[i].Dist(data_vectors[k]);
//        }
//    }
    //--------------------------------------------------------------------------
    
//    for(int i = 0; i < dist_vector.size(); i++)
//    {
//        R::Print(i, " : ", dist_vector[i]);
//    }
    
    // Find min value.
    
    
    // Merge data.
    
    
    // Find new distance values.
    

//    std::vector<double> dist_vector(nDist);
//    
//    for(int i = 0, vec_index = 0; i < nVector; i++)
//    {
//        for(int k = i + 1; k < nVector; k++)
//        {
//            double dist = 0.0;
//            
//            for(int d = 0; d < data.size().col; d++)
//            {
//                double v1 = data(i, d);
//                double v2 = data(k, d);
//                
//                dist += pow(v1 - v2, 2);
//            }
//
//            dist_vector[vec_index++] = sqrt(dist);
//        }
//    }
//    
//    R::Print("VEC DIST :", dist_vector.size());
//    
//    for(int i = 0; i < dist_vector.size(); i++)
//    {
//        R::Print(i , " : ", dist_vector[i]);
//    }
//    
//    

}