#include "Ray.hpp"

Ray::Ray(vec3 startingPoint, Direction direction) {
	startPoint = startingPoint;
	this->direction = direction;
	color = colorDBL(0.0f, 0.0f, 0.0f);
}

Ray::~Ray() {
	Ray* temp = this;
	while(temp->nextRay != nullptr) {
		temp = temp->nextRay;
	}
}

Ray Ray::bounce(const vec3& position, const vec3& normal, bool reflect, const float& refractionIndex) {
	//bounces the ray and adds a new ray to the rayList as well as writes the new ray to the Ray* next variable
	nextRay = new Ray();
	nextRay->setStartPoint(position);
	nextRay->setPreviousRay(this);
	if (reflect) {
		Direction newDirection = glm::reflect(direction, normal);
		nextRay->setDirection(newDirection);
	}
	else {
		Direction newDirection = glm::refract(direction, normal, refractionIndex);
		nextRay->setDirection(newDirection);
	}
	return *nextRay;
}