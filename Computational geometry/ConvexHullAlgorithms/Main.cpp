#include<iostream>
#include<vector>
#include "vecta.h"
#include "QuickHullAlgorithm.h"

using namespace std;
using namespace vecta;

template <typename N>
ostream& operator << (ostream& os, vec2d<N> p)  {
	return  os << p.x << ' ' << p.y;
}

int main()
{
	vector<vec2d<>> points; 
	points.push_back(vec2d<>(2, 3)); 
	points.push_back(vec2d<>(3, 4)); 
	points.push_back(vec2d<>(4, 5));
	points.push_back(vec2d<>(0, 5));
	points.push_back(vec2d<>(-1, 5));
	points.push_back(vec2d<>(4, 5));

	ConvexHullAlgorithmBase* convexHullAlgorithm = new QuickHullAlgorithm();

	vector<vec2d<>>& convexHull = convexHullAlgorithm->CalculateConvexHull(points);

	for (int i = 0; i < convexHull.size(); i++)
	{
		std::cout << "Point[" << i << "] = " << convexHull.at(i) << endl;
	}
	
	std::cout << "points adress" << &points << endl;
	std::cout << "graham adress" << &convexHull << endl;

	return 0;
}