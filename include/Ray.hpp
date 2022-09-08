#include "definitions.hpp"
#include <Polygon.hpp>

class Ray {
public:

private:
	vec3 startPoint;
	Direction direction;
	vec3 endPoint;
	colorDBL color;
	Polygon* startingSurface;
	Ray* nextRay;
	Ray* previousRay;
};