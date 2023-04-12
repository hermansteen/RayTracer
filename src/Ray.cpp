#include "Ray.hpp"

Ray::Ray(vec3 startingPoint, Direction direction) {
	startPoint = startingPoint;
	this->direction = direction;
	color = colorDBL(0.0f, 0.0f, 0.0f);
}
void Ray::removeLastRay() {
	if (nextRay != nullptr) {
		Ray* temp = nextRay;		
		while(temp->nextRay != nullptr) {
			temp = temp->nextRay;
		}
		nextRay = temp->nextRay;
		temp->previousRay = nullptr;
		delete temp;
	}
	
}


void Ray::setNextRay(Ray* _nextRay) {
	nextRay = _nextRay;
	_nextRay->setPreviousRay(this);

}

/*Ray Ray::bounce(const vec3& position, const vec3& normal, bool reflect, const float& refractionIndex) {
	//bounces the ray and adds a new ray to the rayList as well as writes the new ray to the Ray* next variable
	nextRay = new Ray();
	nextRay->setStartPoint(position);
	nextRay->setPreviousRay(this);
	if (reflect) {
		Direction newDirection = glm::reflect(direction, normal);
		nextRay->setDirection(newDirection);
	}

	return *nextRay;
}*/

/*
vec3 Ray::getClosestIntersectionPoint(Ray _ray) {	
	if (_ray.intersections.size() == 1) {
		return _ray.intersections[0];
	}
	else {

		for (int i = 0; i < _ray.intersections.size() - 1; i++) {
			{
				if (glm::distance(_ray.intersections[i], _ray.getStartPoint()) < glm::distance(_ray.intersections[i + 1], _ray.getStartPoint())) {
					return _ray.intersections[i];
				}
				else {
					return _ray.intersections[i + 1];
				}
			}
		}
	}
}*/