#include "Triangle.hpp"

Triangle::Triangle(vec3 point1, vec3 point2, vec3 point3, colorDBL _color)
{
	points = new vec3[3];
	points[0] = point1;
	points[1] = point2;
	points[2] = point3;
	color = _color;
	calculateNormal();
}

//might be wrong, debug this if weird
vec3 Triangle::calculateIntersection(vec3 startingPoint, Direction direction)
{
	vec3 intersection;
	float t = glm::dot(normal, (points[0] - startingPoint)) / glm::dot(normal, direction);
	intersection = startingPoint + t * direction;
	return intersection;
}

