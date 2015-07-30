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
    ClusterData clusters;//(data.size().row);
    
    const int nrow = data.size().row;
    const int ncol = data.size().col;
    
    for(int j = 0; j < nrow; j++)
    {
        int index = -(j+1);
        
        ax::Cluster clust;
        clust.n_row_clust = 1;
        clust.name = index;
        clust.index_list = std::vector<int>(j);
        
        auto& v = clust.center.getStdVector();
        v.resize(ncol);
        
        for(int i = 0; i < ncol; i++)
        {
            v[i] = data(j, i);
        }
        
        clusters[index] = clust;
    }
    
    return clusters;
}

//DistMatrix BiClust::initDistanceMatrix(const R::Matrix2D<double>& data)
//{
//    int nrow = data.size().row;
//    
//    DistMatrix distMatrix;//(nrow - 1);
//    
//    for(auto& n : distMatrix)
//    {
//        // Number of column.
//        n.resize(nrow - 1);
//        std::fill_n(n.begin(), nrow, 0.0);
//    }
//    
//    return distMatrix;
//}

IntPair getFormatedPair(const int& i1, const int& i2)
{
    if(i1 > i2)
    {
        return IntPair(i2, i1);
    }
    
    return IntPair(i1, i2);
}

DistMatrix BiClust::initDistanceMatrix(ClusterData& clusters)
{
    DistMatrix distMatrix;//(nrow - 1);
    
    // For all clusters.
    for(int i = 0; i < clusters.size() - 1; i++)
    {
        for(int k = i + 1; k < clusters.size(); k++)
        {
            int i1 = -(i+1);
            int i2 = -(k+1);
            IntPair index(getFormatedPair(i1, i2));
            distMatrix[index] = clusters[i1].center.Dist(clusters[i2].center);
            
//            R::Print(i1, i2, " : ", clusters[i1].center.Dist(clusters[i2].center));
        }
    }
    
    return distMatrix;
}

void BiClust::calculateDistances(const ClusterData& clusters,
                                 DistMatrix& distMatrix,
                                 const IntPair& namedMerge,
                                 const int& merge_index)
{
//    IntPair getFormatedPair(const int& i1, const index& i2);
    
    
    // Find ratio.
    int n1 = clusters.find(namedMerge.first)->second.n_row_clust;
    int n2 = clusters.find(namedMerge.second)->second.n_row_clust;
    
    for(auto& n : clusters)
    {
        int clust_name = n.second.name;
        
        if(clust_name != namedMerge.first && clust_name != namedMerge.second)
        {
            IntPair v1Index(namedMerge.first, clust_name);
            IntPair v2Index(namedMerge.second, clust_name);
            
            double v1 = distMatrix[v1Index];
            double v2 = distMatrix[v2Index];
            
            IntPair index(getFormatedPair(merge_index, clust_name));
            
            distMatrix[index] = (v1 * n1 + v2 * n2)/ (n1 + n2);
        }
    }
    
    
    std::vector<IntPair> toDelete;
    
    for(auto& n : distMatrix)
    {
        if(n.first.first == namedMerge.first || n.first.first == namedMerge.second ||
           n.first.second == namedMerge.first || n.first.second == namedMerge.second)
        {
            toDelete.push_back(n.first);
        }
    }
    
    for(auto& n : toDelete)
    {
        distMatrix.erase(n);
    }
    
//    // For all clusters.
//    for(int i = 0; i < clusters.size() - 1; i++)
//    {
//        for(int k = i + 1; k < clusters.size(); k++)
//        {
//            distMatrix[i][k] = clusters[i].center.Dist(clusters[k].center);
//        }
//    }
}

IntPair BiClust::getNextMergeVectorsIndex(const ClusterData& clusters,
                                          const DistMatrix& distMatrix)
{
//    double min = 10000000.0;
//    IntPair min_index(-1, -1);
    
//    for(int i = 0; i < clusters.size(); i++)
//    {
//        for(int k = i + 1; k < clusters.size(); k++)
//        {
//           if(distMatrix[i][k] < min)
//           {
//               min = distMatrix[i][k];
//               min_index = IntPair(i, k);
//           }
//        }
//    }
    
//    auto n = std::min_element(distMatrix.begin(), distMatrix.end());
    auto n = min_element(distMatrix.begin(), distMatrix.end(),
                         [](const std::pair<IntPair, double>& v1,
                            const std::pair<IntPair, double>& v2) -> bool
    {
        return v1.second < v2.second;
    });
    
    return n->first;
}

void BiClust::mergeTwoCluster(ClusterData& clusters,
                              const IntPair& merge,
                              const int& merge_index)
{
    auto n1 = clusters.find(merge.first);
    auto n2 = clusters.find(merge.second);
    
//    if(n1 == clusters.end())
//    {
//        R::Print("Error");
//        exit(0);
//    }
//    if(n2 == clusters.end())
//    {
//        R::Print("Error");
//        exit(0);
//    }

    
    ax::Cluster& c1 = n1->second;
    ax::Cluster& c2 = n2->second;

    double n_merge = c1.n_row_clust + c2.n_row_clust;
    c1.center = ((c1.center * c1.n_row_clust) + (c2.center * c2.n_row_clust)) / n_merge;

    c1.n_row_clust = n_merge;
    c1.name = merge_index;

//    // Merge list of index.
    c1.index_list.insert(c1.index_list.end(),
                         c1.index_list.begin(),
                         c1.index_list.end());

    
    // Add new cluster.
    clusters[merge_index] = c1;

    clusters.erase(n1);
    clusters.erase(n2);

}

void recalculateDistance(ClusterData& clusters,
                         DistMatrix& distMatrix,
                         const IntPair& merge)
{

//    std::vector<double> new_clust(clusters.size() - 1);
//    
//    for(int i = 0; i < clusters.size(); i++)
//    {
//        
//    }
//    
//    distMatrix
}

void BiClust::process(const R::Matrix2D<double>& data)
{
    ClusterData clusters = initClusterData(data);
    DistMatrix distMatrix = initDistanceMatrix(clusters);
    std::vector<IntPair> mergeMatrix;
    
    
    int merge_index = 1;
    int i = 0;
    
    
//    R::Print("SIZE : ", clusters.size());
    //--------------------------------------------------------------------------
    while(clusters.size() > 1)
    {
        IntPair namedMerge = getNextMergeVectorsIndex(clusters, distMatrix);
        
        mergeMatrix.push_back(namedMerge);
        
        // Recalculate new distances before merging.
        calculateDistances(clusters, distMatrix, namedMerge, merge_index);

        // Merge cluster in ClusterData matrix.
        mergeTwoCluster(clusters, namedMerge, merge_index);
        
        merge_index++;
        
//        R::Print("SIZE : ", clusters.size());
    }
    
    
    //--------------------------------------------------------------------------

//    for(auto& n : mergeMatrix)
//    {
//        R::Print(n.first, n.second);
//    }
    
    
    
}