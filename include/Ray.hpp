#pragma once
#include "definitions.hpp"
#include <Polygon.hpp>

class Ray {
public:
	Ray() = default;
	Ray(vec3 startingPoint, Direction direction);

	void raySurfaceIntersection();
	void setDirection(Direction);
	Direction getDirection();
	colorDBL getColor();

private:
	vec3 startPoint;
	Direction direction;
	vec3 endPoint;
	colorDBL color;
	Polygon* startingSurface;
	Ray* nextRay;
	Ray* previousRay;
};