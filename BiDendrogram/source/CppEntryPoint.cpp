#include <iostream>
#include <vector>
#include "RUtils.h"

#include <map>
#include <utility>
// #include <functionnal>

struct Point
{
	Point()
	{

	}

	Point(const double& X, const double& Y):
	x(X), y(Y)
	{

	}

	double x, y;
};

struct Line
{	
	Line(const Point& p1, const Point& p2):
	pt1(p1), pt2(p2)
	{

	}

	Point pt1, pt2;
};

// struct Cluster
// {
// 	Cluster() 
// 	{

// 	}

// 	Cluster(const Point& center_position):
// 	n_merge(n), center(center_position) 
// 	{

// 	}

// 	int n_merge;
// 	Point center;
// };

 void AddLinesToMatrix(const int& merge_index,
 					  R::Matrix2D<double>& lines, 
 					  const Line& low, 
 					  const Line& high, 
 					  const Line& cross)
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
 }

 extern "C"
 {


// 	void GenericDendrogram(int* n_merge, 
// 						   double* merge, 
// 						   double* height, 
// 						   int* order,
// 						   double* line_points
// 						   const std::function<bool(Point& low, Point& high)>& findLowHigh)
// 	{
// 		R::Matrix2D<double> matrix(merge, R::Size2D(*n_merge, 2));

// 		R::Matrix2D<double> lines_output(line_points, R::Size2D(*n_merge, 12));

// 		std::vector<double> norm_hight(*n_merge);

// 		double hight_sum = height[*n_merge - 1];

// 		for(int i = 0; i < *n_merge; i++)
// 		{
// 			norm_hight[i] = (height[i] / hight_sum);
// 		}

// 		std::map<int, Point> clusters;

// 		double half_pos = (1.0 / double(*n_merge + 1.0)) * 0.5;

// 		// Init cluster info.
// 		for(int i = 0; i < *n_merge + 1; i++)
// 		{
// 			// int index = -(i + 1);
// 			int index = -order[i];

// 			//------------------------------------------------------------------------
// 			clusters[index] = Point((i / double(*n_merge + 1.0)) + half_pos, 0.0);
// 			//------------------------------------------------------------------------
// 		}

// 		int merge_index = 1;

// 		for(int i = 0; i < *n_merge; i++)
// 		{
// 			int index1 = matrix(i, 0);
// 			int index2 = matrix(i, 1);

// 			// Find highest center.
// 			Point low(clusters[index1]);
// 			Point high(clusters[index2]);

// 			//------------------------------------------------------------------------
// 			// if(low.y > high.y)
// 			if(findLowHigh(low.y, high.y)
// 			//------------------------------------------------------------------------
// 			{
// 				std::swap(low, high);
// 			}

// 			//------------------------------------------------------------------------
// 			// double y_final = high.y + norm_hight[i];
// 			double y_final = norm_hight[i];

// 			Line low_line(low, Point(low.x, y_final));
// 			Line high_line(high, Point(high.x, y_final));
// 			Line cross_line(low_line.pt2, high_line.pt2);
// 			//------------------------------------------------------------------------

// 			AddLinesToMatrix(merge_index, lines_output, low_line, high_line, cross_line);

// 			//------------------------------------------------------------------------
// 			// Add new cluster.
// 			clusters[merge_index] = Point((low.x + high.x) * 0.5, y_final);
// 			//------------------------------------------------------------------------

// 			// Remove old cluster.
// 			clusters.erase(index1);
// 			clusters.erase(index2);

// 			merge_index++;
// 		}
// 	}
	

	void ProcessRightSideDendrogram(int* n_merge, 
						   			double* merge, 
						   			double* height, 
						   			int* order,
						   			double* line_points)
	{
		R::Matrix2D<double> matrix(merge, R::Size2D(*n_merge, 2));

		R::Matrix2D<double> lines_output(line_points, R::Size2D(*n_merge, 12));

		std::vector<double> norm_hight(*n_merge);

		double hight_sum = height[*n_merge - 1];

		for(int i = 0; i < *n_merge; i++)
		{
			norm_hight[i] = (height[i] / hight_sum);
		}

		std::map<int, Point> clusters;

		double half_pos = (1.0 / double(*n_merge + 1.0)) * 0.5;

		// Init cluster info.
		for(int i = 0; i < *n_merge + 1; i++)
		{
			int index = -order[i];
			clusters[index] = Point(0.0, (i / double(*n_merge + 1.0)) + half_pos);
		}

		// std::vector<Point> lines;

		int merge_index = 1;

		for(int i = 0; i < *n_merge; i++)
		{
			int index1 = matrix(i, 0);
			int index2 = matrix(i, 1);

			// Find highest center.
			Point low(clusters[index1]);
			Point high(clusters[index2]);

			if(low.x > high.x)
			{
				std::swap(low, high);
			}

			// double x_final = high.x + norm_hight[i];
			double x_final = norm_hight[i];

			Line low_line(low, Point(x_final, low.y));
			Line high_line(high, Point(x_final, high.y));
			Line cross_line(low_line.pt2, high_line.pt2);

			AddLinesToMatrix(merge_index, lines_output, low_line, high_line, cross_line);

			// Add new cluster.
			clusters[merge_index] = Point(x_final, (low.y + high.y) * 0.5);

			// Remove old cluster.
			clusters.erase(index1);
			clusters.erase(index2);

			merge_index++;
		}
	}



		void ProcessColDendrogram(int* n_merge, 
						   double* merge, 
						   double* height, 
						   int* order,
						   double* line_points)
	{
		// R::Print("TEST");

		R::Matrix2D<double> matrix(merge, R::Size2D(*n_merge, 2));

		R::Matrix2D<double> lines_output(line_points, R::Size2D(*n_merge, 12));

		std::vector<double> norm_hight(*n_merge);
		// 

		double hight_sum = height[*n_merge - 1];


		for(int i = 0; i < *n_merge; i++)
		{
			norm_hight[i] = (height[i] / hight_sum);
		}


		std::map<int, Point> clusters;

		double half_pos = (1.0 / double(*n_merge + 1.0)) * 0.5;

		// Init cluster info.
		for(int i = 0; i < *n_merge + 1; i++)
		{
			// int index = -(i + 1);
			int index = -order[i];

			//------------------------------------------------------------------------
			clusters[index] = Point((i / double(*n_merge + 1.0)) + half_pos, 0.0);
			//------------------------------------------------------------------------
		}

		int merge_index = 1;

		for(int i = 0; i < *n_merge; i++)
		{
			int index1 = matrix(i, 0);
			int index2 = matrix(i, 1);

			// Find highest center.
			Point low(clusters[index1]);
			Point high(clusters[index2]);

			//------------------------------------------------------------------------
			if(low.y > high.y)
			//------------------------------------------------------------------------
			{
				std::swap(low, high);
			}

			//------------------------------------------------------------------------
			// double y_final = high.y + norm_hight[i];
			double y_final = norm_hight[i];

			Line low_line(low, Point(low.x, y_final));
			Line high_line(high, Point(high.x, y_final));
			Line cross_line(low_line.pt2, high_line.pt2);
			//------------------------------------------------------------------------

			AddLinesToMatrix(merge_index, lines_output, low_line, high_line, cross_line);

			//------------------------------------------------------------------------
			// Add new cluster.
			clusters[merge_index] = Point((low.x + high.x) * 0.5, y_final);
			//------------------------------------------------------------------------

			// Remove old cluster.
			clusters.erase(index1);
			clusters.erase(index2);

			merge_index++;
		}
	}
}
