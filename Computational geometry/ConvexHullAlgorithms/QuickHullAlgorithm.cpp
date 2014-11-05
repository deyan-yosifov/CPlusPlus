#pragma once
#include <iostream>
#include "QuickHullAlgorithm.h"

QuickHullAlgorithm::QuickHullAlgorithm()
{
}

QuickHullAlgorithm::~QuickHullAlgorithm()
{
}

void QuickHullAlgorithm::SortByX(std::vector<vec2d<>>* points)
{
	std::sort(points->begin(), points->end(),
		// Lambda expression begins
		[](vec2d<> a, vec2d<> b)
	{
		return (a.x < b.x);
	} // end of lambda expression
	);
}

std::vector<vec2d<>>* QuickHullAlgorithm::ExecuteQuickHullAlgorithm(std::vector<vec2d<>>* points)
{
	QuickHullAlgorithm::SortByX(points);

	return points;
}

std::vector<vec2d<>>* QuickHullAlgorithm::CalculateConvexHull(std::vector<vec2d<>>* points)
{
	QuickHullAlgorithm::SortByX(points);

	std::vector<vec2d<>>* hullPoints = QuickHullAlgorithm::ExecuteQuickHullAlgorithm(points);
	return hullPoints;
}