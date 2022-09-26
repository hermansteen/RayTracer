#pragma once
#include "definitions.hpp"
#include <string>

class Polygon {
	virtual vec3 calculateIntersection(vec3 startingPoint, Direction direction) = 0;
protected:
	//array of points which span the polygon
	vec3* points;
	colorDBL color;
	std::string surfaceType;
};