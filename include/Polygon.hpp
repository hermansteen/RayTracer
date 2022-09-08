#include "definitions.hpp"

class Polygon {
	virtual vec3 calculateIntersection(vec3 startingPoint, Direction direction) = 0;
};