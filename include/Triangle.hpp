#pragma once
#include "Polygon.hpp"

class Triangle : public Polygon {
public:
	Triangle(vec3 point1, vec3 point2, vec3 point3, colorDBL _color);

	vec3 calculateIntersection(vec3 startingPoint, Direction direction) override;
private:
};