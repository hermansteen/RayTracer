#pragma once
#include "definitions.hpp"
#include <string>

class Polygon {
public:
	virtual vec3 calculateIntersectionPoint(vec3 startingPoint, Direction direction) = 0;

	void calculateNormal();

	virtual colorDBL getColor() = 0;

	vec3 getNormal() { return normal; };
protected:
	//array of points which span the polygon
	vec3* points;
	colorDBL color;
	std::string surfaceType = "DIFFUSE";
	vec3 normal;
};