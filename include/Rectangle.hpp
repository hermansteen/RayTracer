#pragma once
#include "Polygon.hpp"
#include "Ray.hpp"
#include "Triangle.hpp"

class Rectangle : public Polygon {
public:

	Rectangle(vec3 point1, vec3 point2, vec3 point3, vec3 point4, colorDBL color, std::string surface);
	vec3 calculateIntersectionPoint(vec3 startingPoint, Direction direction) override;


	bool intersects(const Ray&) override;
};