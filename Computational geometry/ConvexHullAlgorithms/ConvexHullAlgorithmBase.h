#pragma once
#include "vecta.h"
#include <vector>
#include <iostream>

using namespace vecta;

class ConvexHullAlgorithmBase
{
public:	
	virtual std::vector<vec2d<>>& CalculateConvexHull(std::vector<vec2d<>>& points) = 0;
};
