#pragma once
#include "Polygon.hpp"


class Ray {
public:
	Ray() = default;
	Ray(vec3 startingPoint, Direction direction);
	//~Ray();
	void setDirection(Direction _direction) { direction = _direction; };
	Direction getDirection() const { return direction; };
	colorDBL getColor() const { return color; };
	vec3 getStartPoint() const { return startPoint; };
	void setStartPoint(vec3 _startPoint) { startPoint = _startPoint; };
	void setNextRay(Ray* _nextRay);
	Ray* getNextRay() const { return nextRay; };
	void setPreviousRay(Ray* _previousRay) { previousRay = _previousRay; };
	Ray* getPreviousRay() const { return previousRay; };
	void removeLastRay();
	//void setEnd(const vec3& end) { endPoint = end; };
	//vec3 getEndPoint() const { return endPoint; };
	//double getLength();
	//vec3 getClosestIntersectionPoint(Ray _ray);
	//void Ray::savePoint(Ray& _ray, vec3 point) const;

	void setColor(colorDBL _color) { color = _color; };
	void addColor(colorDBL _color) { color += _color; };

	//Ray bounce(const vec3&, const vec3&, bool, const float&);
	
	
private:
	vec3 startPoint;
	Direction direction;
	//vec3 endPoint;
	colorDBL color;
	Polygon* startingSurface;
	Ray* nextRay = nullptr;
	Ray* previousRay = nullptr;
	//std::vector <vec3> intersections;	
};