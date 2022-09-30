#pragma once
#include "definitions.hpp"
#include "Polygon.hpp"

class Ray {
public:
	Ray() = default;
	Ray(vec3 startingPoint, Direction direction);
	~Ray();
	void setDirection(Direction _direction) { direction = _direction; };
	Direction getDirection() const { return direction; };
	colorDBL getColor() const { return color; };
	vec3 getStartPoint() const { return startPoint; };
	void setStartPoint(vec3 _startPoint) { startPoint = _startPoint; };
	void setPreviousRay(Ray* _previousRay) { previousRay = _previousRay; };
	void setEnd(const vec3& end) { endPoint = end; };

	void addColor(colorDBL _color) { color += _color; };

	Ray bounce(const vec3&, const vec3&, bool, const float&);
private:
	vec3 startPoint;
	Direction direction;
	vec3 endPoint;
	colorDBL color;
	Polygon* startingSurface;
	Ray* nextRay;
	Ray* previousRay;
};