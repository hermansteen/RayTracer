#pragma once
#include "definitions.hpp"
#include <string>

class Ray;
class Polygon {
public:
	virtual vec3 calculateIntersectionPoint(vec3 startingPoint, Direction direction) = 0;

	virtual bool intersects(const Ray&) = 0;

	virtual void calculateNormal();

	colorDBL getColor() const { return color; };

	std::string getSurfaceType() const { return surfaceType; };

	vec3 getNormal() const{ return normal; };
protected:
	//array of points which span the polygon
	vec3* points;
	colorDBL color;
	std::string surfaceType = "DIFFUSE";
	vec3 normal;
};