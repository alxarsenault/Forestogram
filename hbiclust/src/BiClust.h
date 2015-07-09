#ifndef __B_CLUST__
#define __B_CLUST__

#include "RMatrix.h"
#include <map>


typedef ax::Math::Vector<double> axMathVec;
typedef std::pair<int, int> IntPair;

//typedef std::vector<std::vector<double>> Matrix;
typedef std::map<IntPair, double> DistMatrix;

namespace ax
{
    struct Cluster
    {
        Cluster()
        {
            
        }
        
        ax::Math::Vector<double> center;
        int n_row_clust, n_col_clust;
        std::vector<int> index_list;
        int name;
        //std::string name;
    };
}

//typedef std::vector<ax::Cluster> ClusterData;
typedef std::map<int, ax::Cluster> ClusterData;

class BiClust
{
public:
    BiClust();
    
    void process(const R::Matrix2D<double>& data);
    
    
private:
    ClusterData initClusterData(const R::Matrix2D<double>& data);
    
    DistMatrix initDistanceMatrix(ClusterData& clusters);
    
    void calculateDistances(const ClusterData& clusters,
                            DistMatrix& distMatrix,
                            const IntPair& merge,
                            const int& merge_index);
    
    IntPair getNextMergeVectorsIndex(const ClusterData& clusters,
                                     const DistMatrix& distMatrix);
    
    void mergeTwoCluster(ClusterData& clusters,
                         const std::pair<int, int>& merge,
                         const int& merge_index);

};


#endif // __B_CLUST__
