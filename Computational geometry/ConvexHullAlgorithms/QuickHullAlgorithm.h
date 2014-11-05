#pragma once
#include "ConvexHullAlgorithmBase.h"
#include <algorithm>
#include <cmath>

class QuickHullAlgorithm : public ConvexHullAlgorithmBase
{
public:
	QuickHullAlgorithm();
	~QuickHullAlgorithm();

	static void SortByX(std::vector<vec2d<>>* points);
	static std::vector<vec2d<>>* ExecuteQuickHullAlgorithm(std::vector<vec2d<>>* points);
	
	std::vector<vec2d<>>* CalculateConvexHull(std::vector<vec2d<>>* points) override;
};

