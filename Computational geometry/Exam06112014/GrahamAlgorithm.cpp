#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include "vecta.h"

using namespace std;
using namespace vecta;

class IndexedPoint
{
public:
	int Index;
	vec2d<> Point;

	IndexedPoint(int& index, vec2d<>& point)
	{
		Index = index;
		Point = point;
	}
};

ostream& operator << (ostream& os, vec2d<> p)  {
	return  os << p.x << ' ' << p.y;
}

void DrawLines(std::vector<IndexedPoint>& points)
{
	cout<<"lines"<<endl;
	int count = points.size();

	for(int i = 1; i < count; i+=2)
	{
		cout<< points[i-1].Point <<' '<< points[i].Point <<endl;
	}
}

void DrawPolygone(std::vector<IndexedPoint>& points)
{
	cout<<"polygon"<<endl;
	int count = points.size();

	for(int i = 0; i < count; i++)
	{
		cout<< points[i].Point <<endl;
	}
}

void DrawPoints(std::vector<vec2d<>>& points)
{
	cout<<"points"<<endl;
	int count = points.size();

	for(int i = 0; i < count; i++)
	{
		cout<< points[i] <<endl;
	}
}

void SetColor(char* color)
{
	cout<<"colour "<<color<<endl;
}

void SetWidth(double width)
{
	cout<<"width "<<width<<endl;
}

void DrawCircle(vec2d<>& point, double radius, char* color)
{
	SetColor(color);
	cout<<"circles*"<<endl<<point<<' '<<radius<<endl;
}

void DrawResultSketchps(std::vector<vec2d<>>& points, std::vector<IndexedPoint>& grahamConvexHull)
{
	cout<<"unit 10"<<endl;

	DrawCircle(grahamConvexHull[0].Point, 1, "red");
	DrawCircle(grahamConvexHull[1].Point, 1, "green");
	DrawCircle(grahamConvexHull[2].Point, 1, "blue");

	SetColor("black");
	DrawPoints(points);
	SetColor("blue");
	SetWidth(1);
	DrawLines(grahamConvexHull);
	SetWidth(0.3);
	SetColor("red");
	DrawPolygone(grahamConvexHull);	
}

void SortByX(std::vector<IndexedPoint>& points)
{
	std::sort(points.begin(), points.end(),
		// Lambda expression begins
		[](IndexedPoint a, IndexedPoint b)
	{
		if(a.Point.x == b.Point.x)
		{
			if(a.Point.y == b.Point.y)
			{
				return a.Index < b.Index;
			}

			return a.Point.y < b.Point.y;
		}

		return (a.Point.x < b.Point.x);
	} // end of lambda expression
	);
}

vec2d<> start;

void SortByPrecedence(std::vector<IndexedPoint>& points)
{
	if(points.size() <= 1)
	{
		return;
	}
		
	start = points[0].Point;

	std::sort(points.begin()+1, points.end(),
		// Lambda expression begins
		[](IndexedPoint a, IndexedPoint b)
	{
		vec2d<> first = a.Point-start;
		vec2d<> second = b.Point-start;

		return (first < second);
	} // end of lambda expression
	);
}

std::vector<IndexedPoint>& CalculateGrahamConvexHullBySortedPoints(std::vector<IndexedPoint>& sortedPoints)
{
	std::vector<IndexedPoint>& grahamPoints = *(new std::vector<IndexedPoint>());
	int count = sortedPoints.size();

	for(int i = 0; i < count; i++)
	{
		grahamPoints.push_back(sortedPoints[i]);		
		
		while(grahamPoints.size() > 2)
		{
			int index = grahamPoints.size() - 1;

			IndexedPoint& first = grahamPoints[index - 2];
			IndexedPoint& second = grahamPoints[index - 1];
			IndexedPoint& third = grahamPoints[index];

			vec2d<> firstVector = second.Point - first.Point;
			vec2d<> secondVector = third.Point - first.Point;
			double orientation = firstVector ^ secondVector;

			if(orientation <= 0)
			{
				grahamPoints.pop_back();
				grahamPoints.pop_back();
				IndexedPoint pointToAdd = ((orientation < 0 || vecta::norm(firstVector) < vecta::norm(secondVector)) ? third : second);
				grahamPoints.push_back(pointToAdd);
			}
			else
			{
				break;
			}
		}
	}

	return grahamPoints;
}

int FindSmallestIndexPosition(std::vector<IndexedPoint>& grahamPoints)
{
	int position = -1;
	int minIndex = std::numeric_limits<int>::max();

	int count = grahamPoints.size();

	for(int i = 0; i < count; i++)
	{
		int currentIndex = grahamPoints[i].Index;
		if(currentIndex < minIndex)
		{
			minIndex = currentIndex;
			position = i;
		}
	}

	return position;
}

std::vector<IndexedPoint> CalculateGrahamConvexHull(std::vector<vec2d<>>& points)
{
	int count = points.size();
	std::vector<IndexedPoint> indexedPoints;

	for(int i = 0; i < count; i++)
	{
		indexedPoints.push_back(IndexedPoint(i, points[i]));
	}

	SortByX(indexedPoints);
	SortByPrecedence(indexedPoints);

	std::vector<IndexedPoint> grahamPoints = CalculateGrahamConvexHullBySortedPoints(indexedPoints);
	int currentIndex = FindSmallestIndexPosition(grahamPoints);
	std::vector<IndexedPoint> orderedGrahamPoints;

	int hullPointsCount = grahamPoints.size();

	for(int i = 0; i < hullPointsCount; i++)
	{
		orderedGrahamPoints.push_back(grahamPoints[currentIndex++]);

		if(currentIndex >= hullPointsCount)
		{
			currentIndex = 0;
		}
	}

	return orderedGrahamPoints;
}

std::vector<vec2d<>>& GetSampleInputSimple()
{
	vector<vec2d<>>& points = *(new std::vector<vec2d<>>());
	points.push_back(vec2d<>(5, 5)); 
	points.push_back(vec2d<>(3, 2)); 
	points.push_back(vec2d<>(10, 1));
	points.push_back(vec2d<>(2, 7));
	points.push_back(vec2d<>(0, 0));
	points.push_back(vec2d<>(6, 3));

	return points;
}

std::vector<vec2d<>>& GetSampleInputComplex()
{
	vector<vec2d<>>& points = *(new std::vector<vec2d<>>());
	points.push_back(vec2d<>(2, 3));
	points.push_back(vec2d<>(4, 5));
	points.push_back(vec2d<>(1, 2));
	points.push_back(vec2d<>(2, 2));
	points.push_back(vec2d<>(1, 1));
	points.push_back(vec2d<>(0, 6));
	points.push_back(vec2d<>(8, 3));
	points.push_back(vec2d<>(0, 0));
	points.push_back(vec2d<>(6, 3));
	points.push_back(vec2d<>(2, 6));

	return points;
}

std::vector<vec2d<>>& GetInput()
{
	vector<vec2d<>>& points = *(new std::vector<vec2d<>>());
	double x,y;

	while(cin >> x >> y)
	{
		points.push_back(vec2d<>(x, y));
	}

	return points;
}

void OuputResult(vector<IndexedPoint>& grahamHull)
{
	int count = grahamHull.size();

	for(int i = 0; i < count; i++)
	{
		cout<<"#"<<grahamHull[i].Index<<endl;
	}
}

int main()  {
	//vector<vec2d<>> points = GetSampleInputSimple();
	//vector<vec2d<>> points = GetSampleInputComplex();
	vector<vec2d<>> points = GetInput();

	vector<IndexedPoint> grahamHull = CalculateGrahamConvexHull(points);

	OuputResult(grahamHull);
	//DrawResultSketchps(points, grahamHull);

	return 0;
}
