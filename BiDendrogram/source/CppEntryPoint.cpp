#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <random>

#include "BiDendrogram.h"
#include "BiClust.h"


inline R::Point indexToPoint(int* size,
				   double* size_ratio, 
				   double* margin, 
				   const int& row, 
				   const int& col)
{
	double x = margin[1] + (col / double(size[1])) * size_ratio[1];
	double y = margin[0] + (row / double(size[0])) * size_ratio[0];

	return R::Point(x, y);
}


 extern "C"
 {

	void ProcessRightSideDendrogram(int* n_merge, 
						   			double* merge, 
						   			double* height, 
						   			int* order,
						   			double* cut_hight,
						   			double* line_points,
						   			double* answer_limits)
	{
        R::Matrix2D<double> merge_matrix(merge, R::Size2D(*n_merge, 2));
        R::Vector<double> height_vec(height, *n_merge);
        R::Vector<int> order_vec(order, *n_merge);
        R::Matrix2D<double> points_matrix(line_points, R::Size2D(*n_merge, 15));
        R::Vector<double> limits_vec(answer_limits, *n_merge + 1);
        
        RowDendrogram dendrogram(merge_matrix,
                                 height_vec,
                                 order_vec,
                                 points_matrix,
                                 limits_vec);
        
        dendrogram.init();
        dendrogram.process(*cut_hight);
	}

     void ProcessColDendrogram(int* n_merge,
                               double* merge,
                               double* height,
                               int* order,
                               double* cut_hight,
                               double* line_points,
                               double* answer_limits)
     {
         R::Matrix2D<double> merge_matrix(merge, R::Size2D(*n_merge, 2));
         R::Vector<double> height_vec(height, *n_merge);
         R::Vector<int> order_vec(order, *n_merge);
         R::Matrix2D<double> points_matrix(line_points, R::Size2D(*n_merge, 15));
         R::Vector<double> limits_vec(answer_limits, *n_merge + 1);
         
         ColumnDendrogram dendrogram(merge_matrix,
                                     height_vec,
                                     order_vec,
                                     points_matrix,
                                     limits_vec);
         
         dendrogram.init();
         dendrogram.process(*cut_hight);
     }


	void ProcessClusterOnRect(int* size, 
							  double* size_ratio, 
							  double* margin,
							  double* row_limits,
							  double* col_limits,
							  double* rect_points)
	{
		std::vector<int> row_index;
		std::vector<int> col_index;

		// For all rows.
		for(int k = 0; k < size[0]; k++)
		{
			if(row_limits[k] == 1.0)
			{
				row_index.push_back(k);
			}
		}
		row_index.push_back(size[0]);

		// For all cols.
		for(int k = 0; k < size[1]; k++)
		{
			if(col_limits[k] == 1.0)
			{
				col_index.push_back(k);
			}
		}
		col_index.push_back(size[1]);

		int n_cluster = (col_index.size() - 1) * (row_index.size() - 1);

		R::Matrix2D<double> rect_points_matrix(rect_points, R::Size2D(n_cluster, 7));
	
		int clust_incr = 0;

		R::ColorVector colors = R::GetRainbowColors(n_cluster);
//        R::ColorVector colors = GetHeatColors(n_cluster);

        
//		for(int j = 0; j < row_index.size() - 1; j++)
        for(int i = 0; i < col_index.size() - 1; i++)
		{
//			for(int i = 0; i < col_index.size() - 1; i++)
            for(int j = 0; j < row_index.size() - 1; j++)
			{
				R::Color c = colors[clust_incr];

				R::Point bl(indexToPoint(size, size_ratio, margin, row_index[j], col_index[i]));
				R::Point tr(indexToPoint(size, size_ratio, margin, row_index[j+1], col_index[i+1]));
				// rectangles.emplace_back(Rect(bl, tr));

				rect_points_matrix(clust_incr, 0) = bl.x;
				rect_points_matrix(clust_incr, 1) = bl.y;
				rect_points_matrix(clust_incr, 2) = tr.x;
				rect_points_matrix(clust_incr, 3) = tr.y;

				rect_points_matrix(clust_incr, 4) = c.r;
				rect_points_matrix(clust_incr, 5) = c.g;
				rect_points_matrix(clust_incr, 6) = c.b;

				clust_incr++;
			}
		}

		// R::Print("NUMBER OF CLUSTER = ", n_cluster);
		// R::Print("Number of rect = ", rectangles.size());
	}
     
     void ProcessBiClustering(int* size, double* data, double* answer)
     {
         R::Matrix2D<double> data_matrix(data, R::Size2D(size[0], size[1]));
         
         BiClust clusters;
         
         clusters.process(data_matrix);
     }


}
