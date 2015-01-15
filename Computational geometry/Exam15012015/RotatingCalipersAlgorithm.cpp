// Deyan Yosifov
// Computational Geometry Exam FMI 15.01.2015

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

void DrawResultSketchps(std::vector<vec2d<>>& points,vector<IndexedPoint> diametralPoints)
{	
	cout<<"unit 10"<<endl;
	int size = diametralPoints.size();

	for(int i = 1; i < size; i+=2)
	{
		IndexedPoint& first = diametralPoints[i-1];
		IndexedPoint& second = diametralPoints[i];
		DrawCircle(first.Point, 1, "red");
		DrawCircle(second.Point, 1, "green");
	}  
	
	SetColor("black");
	DrawPoints(points);
	SetColor("blue");
	SetWidth(1);
	DrawLines(diametralPoints);
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

void OuputResult(vector<IndexedPoint> diametralPoints)
{
	int size = diametralPoints.size();

	for(int i = 1; i < size; i+=2)
	{
		IndexedPoint& first = diametralPoints[i-1];
		IndexedPoint& second = diametralPoints[i];
		cout<<(first.Index + 1)<<" "<<(second.Index + 1)<<endl;
	}
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

void ReplaceMaxDiameterAndDiametralPoints(IndexedPoint sidePoint, IndexedPoint currentDiametral, std::vector<IndexedPoint>& diametralPoints, double& maxDiameterNorm, double& newMaxDiameterNorm)
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
		IndexedPoint firstSidePoint = sidePoints[0];
		double firstNorm = norm(point.Point - firstSidePoint.Point);		
		if(firstNorm > maxDiameterNorm)
		{
			ReplaceMaxDiameterAndDiametralPoints(firstSidePoint, point, diametralPoints, maxDiameterNorm, firstNorm);
		}
		else if(firstNorm == maxDiameterNorm)
		{
			AddToMaxDiametralPoints(firstSidePoint, point, diametralPoints);
		}
		
		IndexedPoint secondSidePoint = sidePoints[1];
		double secondNorm = norm(point.Point - secondSidePoint.Point);		
		if(secondNorm > maxDiameterNorm)
		{
			ReplaceMaxDiameterAndDiametralPoints(secondSidePoint, point, diametralPoints, maxDiameterNorm, secondNorm);
		}
		else if(secondNorm == maxDiameterNorm)
		{
			AddToMaxDiametralPoints(secondSidePoint, point, diametralPoints);
		}
	}	
}

IndexedPoint& GetNextPoint(std::vector<IndexedPoint>& indexedPoints, IndexedPoint& point)
{
	int size = indexedPoints.size();
	if(point.Index < size - 1)
	{
		return indexedPoints[point.Index + 1];
	}
	else
	{
		return indexedPoints[0];
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
		vec2d<> nextSideVector = GetNextPoint(indexedPoints, sidePoints[1]).Point - sidePoints[1].Point;
		double sideAngle = abs(vecta::angle(sideVector, nextSideVector));

		vec2d<> diametralVector = vec2d<>(-sideVector.x, -sideVector.y);
		int currentDiametralsCount = currentDiametrals.size();
		vec2d<> nextDiametralVector = GetNextPoint(indexedPoints, currentDiametrals[currentDiametralsCount - 1]).Point - currentDiametrals[currentDiametralsCount - 1].Point;
		double diametralAngle = abs(vecta::angle(sideVector, nextSideVector));


		if(sideAngle <= diametralAngle)
		{
			angle += sideAngle;
			IndexedPoint first = sidePoints[1];
			IndexedPoint second = GetNextPoint(indexedPoints, first);
			sidePoints.clear();
			sidePoints.push_back(first);
			sidePoints.push_back(second);
		}
		else
		{			
			angle += diametralAngle;
			IndexedPoint first = currentDiametrals[currentDiametralsCount - 1];
			IndexedPoint second = GetNextPoint(indexedPoints, first);
			sidePoints.clear();
			sidePoints.push_back(first);
			sidePoints.push_back(second);
		}
	}

	return diametralPoints;
}

int main()  {
	//vector<vec2d<>> points = GetSampleInputSimple();
	//vector<vec2d<>> points = GetSampleInputComplex();
	vector<vec2d<>> points = GetInput();

	vector<IndexedPoint> diametralPoints = CalculateDiametralPoints(points);
		
	OuputResult(diametralPoints);
	//DrawResultSketchps(points, diametralPoints);

	return 0;
}