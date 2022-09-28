#pragma once
#include "definitions.hpp"
#include <Polygon.hpp>

class Ray {
public:
	Ray() = default;
	Ray(vec3 startingPoint, Direction direction);

	void raySurfaceIntersection();
	void setDirection(Direction);
	Direction getDirection() const { return direction; }
	colorDBL getColor() const { return color; }
	vec3 getStartPoint() const { return startPoint; }
	void setEnd(const vec3& end) { endPoint = end; }

	void addColor(colorDBL _color) { color += _color; }

private:
	vec3 startPoint;
	Direction direction;
	vec3 endPoint;
	colorDBL color;
	Polygon* startingSurface;
	Ray* nextRay;
	Ray* previousRay;
};