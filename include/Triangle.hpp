#pragma once
#include "Polygon.hpp"
#include "Ray.hpp"

class Triangle : public Polygon {
public:
	Triangle(vec3 point1, vec3 point2, vec3 point3, colorDBL _color);

	vec3 calculateIntersectionPoint(vec3 startingPoint, Direction direction) override;

	bool intersects(const Ray&) override;
private:
	
};