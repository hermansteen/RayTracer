#pragma once
#include "definitions.hpp"
#include <string>

class Polygon {
public:
	virtual vec3 calculateIntersection(vec3 startingPoint, Direction direction) = 0;

	void calculateNormal();

	colorDBL getColor() { return color; };

	vec3 getNormal() { return normal; };
protected:
	//array of points which span the polygon
	vec3* points;
	colorDBL color;
	std::string surfaceType;
	vec3 normal;
};