#pragma once
#include "Polygon.hpp"
#include "Ray.hpp"

class Triangle : public Polygon {
public:
	Triangle(vec3 point1, vec3 point2, vec3 point3, colorDBL _color);

	vec3 calculateIntersectionPoint(vec3 startingPoint, Direction direction) override;

	colorDBL getColor() override { return color; };

	bool intersects(const Ray&);
private:
};