#pragma once
#include "Polygon.hpp"
#include "Ray.hpp"

class Triangle : public Polygon {
public:
	Triangle(vec3 point1, vec3 point2, vec3 point3, colorDBL _color, std::string _surface);

	vec3 calculateIntersectionPoint(vec3 startingPoint, Direction direction) override;
	
	vec3 randomPointOnSurface();
	double getArea();

	bool intersects(const Ray&) override;
private:
	
};