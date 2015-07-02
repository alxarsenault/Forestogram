#include <iostream>
#include <vector>
#include "RUtils.h"

#include <map>
#include <utility>
// #include <Rmath.h>
#include <random>
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

struct Color
{
	Color()
	{

	}

	Color(const double& R, const double& G, const double& B, const double& A):
	r(R), g(G), b(B), a(A)
	{

	}

	double r, g, b, a;
};

struct Cluster
{

	Cluster():
	n_merge(0)
	{

	}

	Cluster(const Point& point_, const Color& color_):
	point(point_), color(color_),
	n_merge(0)
	{

	}

	Point point;
	Color color;
	int n_merge;
	std::vector<int> index_list; 
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
 					  const Line& cross,
 					  const Color& color)
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

// std::vector<Color> GetRainbowColors(const int& n)
// {
// 	std::default_random_engine generator;
//   	std::uniform_real_distribution<double> distribution(0.0, 1.0);
// 	std::vector<Color> colors;

// 	double r = 0.0;
// 	double g = 0.0;
// 	double b = 0.0;
// 	double dist = 0.0;

// 	for(int i = 0; i < n; i++)
// 	{
// 		do
// 		{
// 			r = distribution(generator);
// 			g = distribution(generator);
// 			b = distribution(generator);

// 			dist = sqrt(r*r + g*g + b*b);

// 		} while(dist < 1.0);

// 		colors.emplace_back(Color(r, g, b, 1.0));
// 	}

// 	return colors;
// }

std::vector<Color> GetRainbowColors(const int& n)
{
	std::vector<Color> colors;

	double separation = 1.0 / 6.0;
	double incr = 1.0 / double(n);
	double v = 0.0;

	R::Print("NCLUST ", n);
	R::Print("Separation : ", separation);
	// double pos = 0.0;

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
		
		colors.emplace_back(Color(r, g, b, 1.0));
	}

	return colors;
}

 extern "C"
 {

	void ProcessRightSideDendrogram(int* n_merge, 
						   			double* merge, 
						   			double* height, 
						   			int* order,
						   			double* cut_hight,
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

		// std::map<int, Point> clusters;

		double norm_cut_hight = *cut_hight / hight_sum;
		std::map<int, Cluster> clusters;

		double half_pos = (1.0 / double(*n_merge + 1.0)) * 0.5;

		// Init cluster info.
		for(int i = 0; i < *n_merge + 1; i++)
		{
			int index = -order[i];
			clusters[index].point = Point(0.0, (i / double(*n_merge + 1.0)) + half_pos);
			clusters[index].color = Color(1.0, 0.0, 0.0, 1.0);
		}

		// std::vector<Point> lines;

		int merge_index = 1;
		bool as_reach_cutting_hight = false;
		bool is_first_time_cut = false;

		for(int i = 0; i < *n_merge; i++)
		{
			int index1 = matrix(i, 0);
			int index2 = matrix(i, 1);

			// Find highest center.
			Point low(clusters[index1].point);
			Point high(clusters[index2].point);

			if(low.x > high.x)
			{
				std::swap(low, high);
			}

			// double x_final = high.x + norm_hight[i];
			double x_final = norm_hight[i];

			Line low_line(low, Point(x_final, low.y));
			Line high_line(high, Point(x_final, high.y));
			Line cross_line(low_line.pt2, high_line.pt2);

			Color color(0.0, 0.0, 0.0, 1.0);

			if(high_line.pt2.x > norm_cut_hight)
			{
				color = Color(0.0, 0.0, 0.0, 1.0);

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

			AddLinesToMatrix(merge_index, lines_output, low_line, high_line, cross_line, color);

			// Change all cluster color.
			if(is_first_time_cut)
			{
				std::size_t n_cluster = clusters.size();
				// R::Print("N CLUSTER = ", n_cluster);
				std::vector<Color> colors = GetRainbowColors(n_cluster);

				R::Print(n_cluster);

				int i = 0;
				for(auto& clust : clusters)
				{

					// R::Print("N ROW :", clust.second.index_list.size());
					Color c = colors[i++];

					for(auto& i : clust.second.index_list)
					{
						lines_output(i, 12) = c.r;
						lines_output(i, 13) = c.g;
						lines_output(i, 14) = c.b;
						lines_output(i, 15) = 1.0;
					}
				}
			}




			// Add new cluster.
			clusters[merge_index].point = Point(x_final, (low.y + high.y) * 0.5);
			clusters[merge_index].color = color;
			clusters[merge_index].n_merge = clusters[index1].n_merge + clusters[index2].n_merge + 1;

			std::vector<int> index_list1 = clusters[index1].index_list;
			std::vector<int> index_list2 = clusters[index2].index_list;
			index_list1.insert(index_list1.end(), index_list2.begin(), index_list2.end());

			clusters[merge_index].index_list = index_list1;
			clusters[merge_index].index_list.push_back(merge_index - 1);
			//------------------------------------------------------------------------------------
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
						      double* cut_hight,
						      double* line_points)
	{
		R::Matrix2D<double> matrix(merge, R::Size2D(*n_merge, 2));

		R::Matrix2D<double> lines_output(line_points, R::Size2D(*n_merge, 15));

		std::vector<double> norm_hight(*n_merge);

		double hight_sum = height[*n_merge - 1];

		for(int i = 0; i < *n_merge; i++)
		{
			norm_hight[i] = (height[i] / hight_sum);
		}

		double norm_cut_hight = *cut_hight / hight_sum;

		// std::map<int, Point> clusters;
		std::map<int, Cluster> clusters;

		double half_pos = (1.0 / double(*n_merge + 1.0)) * 0.5;

		// std::default_random_engine generator;
  // 		std::uniform_real_distribution<double> distribution(0.0, 1.0);

  		
		// Init cluster info.
		for(int i = 0; i < *n_merge + 1; i++)
		{
			int index = -order[i];

			// double r = distribution(generator);
			// double g = distribution(generator);
			// double b = distribution(generator);


			//------------------------------------------------------------------------
			clusters[index].point = Point((i / double(*n_merge + 1.0)) + half_pos, 0.0);
			clusters[index].color = Color(0.0, 0.0, 0.0, 1.0);
			//------------------------------------------------------------------------
		}

		int merge_index = 1;


		bool as_reach_cutting_hight = false;
		bool is_first_time_cut = false;

		for(int i = 0; i < *n_merge; i++)
		{
			int index1 = matrix(i, 0);
			int index2 = matrix(i, 1);

			// Find highest center.
			Point low(clusters[index1].point);
			Point high(clusters[index2].point);

			//------------------------------------------------------------------------
			if(low.y > high.y)
			//------------------------------------------------------------------------
			{
				std::swap(low, high);
			}

			//------------------------------------------------------------------------
			double y_final = norm_hight[i];

			Line low_line(low, Point(low.x, y_final));
			Line high_line(high, Point(high.x, y_final));
			Line cross_line(low_line.pt2, high_line.pt2);
			//------------------------------------------------------------------------

			// Color color(clusters[index1].color);
			Color color(0.0, 0.0, 0.0, 1.0);

			// if(clusters[index2].n_merge > clusters[index1].n_merge)
			// {
			// 	color = Color(clusters[index2].color);
			// }

			if(high_line.pt2.y > norm_cut_hight)
			{
				color = Color(0.0, 0.0, 0.0, 1.0);

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

			AddLinesToMatrix(merge_index, lines_output, low_line, high_line, cross_line, color);

			// Change all cluster color.
			if(is_first_time_cut)
			{
				std::size_t n_cluster = clusters.size();
				// R::Print("N CLUSTER = ", n_cluster);
				std::vector<Color> colors = GetRainbowColors(n_cluster);

				R::Print(n_cluster);

				int i = 0;
				for(auto& clust : clusters)
				{

					// R::Print("N ROW :", clust.second.index_list.size());
					Color c = colors[i++];

					for(auto& i : clust.second.index_list)
					{
						lines_output(i, 12) = c.r;
						lines_output(i, 13) = c.g;
						lines_output(i, 14) = c.b;
						lines_output(i, 15) = 1.0;
					}
				}
			}
			


			//------------------------------------------------------------------------
			// Add new cluster.
			clusters[merge_index].point = Point((low.x + high.x) * 0.5, y_final);
			clusters[merge_index].color = color;
			clusters[merge_index].n_merge = clusters[index1].n_merge + clusters[index2].n_merge + 1;

			std::vector<int> index_list1 = clusters[index1].index_list;
			std::vector<int> index_list2 = clusters[index2].index_list;
			index_list1.insert(index_list1.end(), index_list2.begin(), index_list2.end());

			clusters[merge_index].index_list = index_list1;
			clusters[merge_index].index_list.push_back(merge_index - 1);
			//------------------------------------------------------------------------

			// if(as_reach_cutting_hight)
			// {
			// 	// as_reach_cutting_hight = false;
			// }

			// Remove old cluster.
			clusters.erase(index1);
			clusters.erase(index2);

			merge_index++;
		}
	}
}
