// Deyan Yosifov
// Computational Geometry Exam FMI 06.11.2014

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

void DrawResultSketchps(std::vector<vec2d<>>& points, vec2d<>& first, vec2d<>& second)
{
	cout<<"unit 10"<<endl;

	DrawCircle(first, 1, "red");
	DrawCircle(second, 1, "green");
	
	SetColor("black");
	DrawPoints(points);
	SetColor("blue");
	SetWidth(1);
	//DrawPolygone(points);	
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

void OuputResult(IndexedPoint& first, IndexedPoint& second)
{
	cout<<(first.Index + 1)<<endl;
	cout<<(second.Index + 1)<<endl;
}

std::vector<IndexedPoint> FindDiametralPoints(std::vector<IndexedPoint>& indexedPoints, IndexedPoint& firstSidePoint, IndexedPoint& secondSidePoint)
{
	double maxFace = 0;
	std::vector<IndexedPoint>& diametralPoints = *(new std::vector<IndexedPoint>());

	int size = indexedPoints.size();
	vec2d<> sideVector = firstSidePoint.Point - secondSidePoint.Point;

	for(int i = 0; i < size; i++)
	{
		IndexedPoint point = indexedPoints[i];
		
		if(point.Index == firstSidePoint.Index || point.Index == secondSidePoint.Index)
		{
			continue;
		}

		vec2d<> diametralVector = point.Point - secondSidePoint.Point;
		double face = abs(sideVector ^ diametralVector);

		if(face > maxFace)
		{
			diametralPoints.clear();
			diametralPoints.push_back(point);
			maxFace = face;
		}
		else if(face == maxFace)
		{
			diametralPoints.push_back(point);
		}
	}

	return diametralPoints;
}

void AddToMaxDiametralPoints(IndexedPoint sidePoint, IndexedPoint currentDiametral, std::vector<IndexedPoint>& diametralPoints)
{
	diametralPoints.push_back(sidePoint);
	diametralPoints.push_back(currentDiametral);
}

void UpdateMaxDiameterAndDiametralPoints(IndexedPoint sidePoint, IndexedPoint currentDiametral, std::vector<IndexedPoint>& diametralPoints, double& maxDiameterNorm, double& newMaxDiameterNorm)
{
	maxDiameterNorm = newMaxDiameterNorm;
	diametralPoints.clear();
	AddToMaxDiametralPoints(sidePoint, currentDiametral, diametralPoints);
}

void UpdateMaxDiameterAndDiametralPoints(std::vector<IndexedPoint>& sidePoints, std::vector<IndexedPoint>& currentDiametrals, std::vector<IndexedPoint>& diametralPoints, double& maxDiameterNorm)
{
	int diametralsCount = currentDiametrals.size();	

	for(int i = 0; i < diametralsCount; i++)
	{
		IndexedPoint point = currentDiametrals[i];

		double first = norm(point.Point - sidePoints[0].Point);		
		if(first > maxDiameterNorm)
		{
			UpdateMaxDiameterAndDiametralPoints(sidePoints[0], point, diametralPoints, maxDiameterNorm, first);
		}
		else if(first == maxDiameterNorm)
		{
			AddToMaxDiametralPoints(sidePoints[0], point, diametralPoints);
		}

		double second = norm(point.Point - sidePoints[0].Point);		
		if(second > maxDiameterNorm)
		{
			UpdateMaxDiameterAndDiametralPoints(sidePoints[0], point, diametralPoints, maxDiameterNorm, second);
		}
		else if(second == maxDiameterNorm)
		{
			AddToMaxDiametralPoints(sidePoints[0], point, diametralPoints);
		}
	}	
}



std::vector<IndexedPoint> CalculateDiametralPoints(std::vector<vec2d<>>& points)
{
	int count = points.size();
	std::vector<IndexedPoint> indexedPoints;

	for(int i = 0; i < count; i++)
	{
		indexedPoints.push_back(IndexedPoint(i, points[i]));
	}

	double maxDiameterNorm = 0;
	std::vector<IndexedPoint>& diametralPoints = *(new std::vector<IndexedPoint>());
	std::vector<IndexedPoint>& sidePoints = *(new std::vector<IndexedPoint>());

	sidePoints.push_back(indexedPoints[0]);
	sidePoints.push_back(indexedPoints[1]);	
	double angle = 0;

	while (angle <= PI)
	{
		std::vector<IndexedPoint> currentDiametrals = FindDiametralPoints(indexedPoints, sidePoints[0], sidePoints[1]);
		UpdateMaxDiameterAndDiametralPoints(sidePoints, currentDiametrals, diametralPoints, maxDiameterNorm);

		vec2d<> sideVector = sidePoints[1].Point - sidePoints[0].Point;

	}


	return diametralPoints;
}

int main()  {
	vector<vec2d<>> points = GetSampleInputSimple();
	//vector<vec2d<>> points = GetSampleInputComplex();
	//vector<vec2d<>> points = GetInput();

	vector<IndexedPoint> diametralPoints = CalculateDiametralPoints(points);

	OuputResult(diametralPoints[0], diametralPoints[1]);
	DrawResultSketchps(points, diametralPoints[0].Point, diametralPoints[1].Point);

	return 0;
}