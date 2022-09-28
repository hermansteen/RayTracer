#include "Ray.hpp"

Ray::Ray(vec3 startingPoint, Direction direction) {
	startPoint = startingPoint;
	this->direction = direction;
	color = colorDBL(0.0f, 0.0f, 0.0f);
}