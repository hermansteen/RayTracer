#pragma once
#include "Polygon.hpp"
#include "Ray.hpp"
#include "Triangle.hpp"

class Rectangle : public Polygon {
public:

	Rectangle(vec3 point1, vec3 point2, vec3 point3, vec3 point4, colorDBL color);
	vec3 calculateIntersectionPoint(vec3 startingPoint, Direction direction) override;

	colorDBL getColor() override { return color; };

	bool intersects(const Ray&);
};