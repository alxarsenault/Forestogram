#ifndef __B_CLUST__
#define __B_CLUST__

#include "RMatrix.h"

typedef std::vector<std::vector<double>> Matrix;
typedef ax::Math::Vector<double> axMathVec;

namespace ax
{
    struct Cluster
    {
        Cluster()
        {
            
        }
        
        ax::Math::Vector<double> center;
        int n_row_clust, n_col_clust;
        std::string name;
        std::vector<int> index_list;
    };
}

typedef std::vector<ax::Cluster> ClusterData;

class BiClust
{
public:
    BiClust();
    
    void process(const R::Matrix2D<double>& data);
    
    
private:
    std::vector<ax::Cluster> initClusterData(const R::Matrix2D<double>& data);
    Matrix initDistanceMatrix(const R::Matrix2D<double>& data);
    
    void calculateDistances(const ClusterData& clusters, Matrix& distMatrix);
    std::pair<int, int> getNextMergeVectorsIndex(const ClusterData& clusters,
                                                 const Matrix& distMatrix);
    
    void mergeTwoCluster(ClusterData& clusters,
                         const std::pair<int, int>& merge,
                         const int& merge_index);

};


#endif // __B_CLUST__
