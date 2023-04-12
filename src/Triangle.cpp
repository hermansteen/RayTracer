#include "Triangle.hpp"

Triangle::Triangle(vec3 point1, vec3 point2, vec3 point3, colorDBL _color, std::string _surface)
{
	points = new vec3[3];
	points[0] = point1;
	points[1] = point2;
	points[2] = point3;
	color = _color;
	calculateNormal();
	surfaceType = _surface;
	isSphere = false;
}

//might be wrong, debug this if weird
vec3 Triangle::calculateIntersectionPoint(vec3 startingPoint, Direction direction)
{
	vec3 intersection;
	float t = glm::dot(normal, (points[0] - startingPoint)) / glm::dot(normal, direction);
	intersection = startingPoint + t * direction;
	return intersection;
}

//calculate if ray intersects triangle using moller trumbore algorithm
bool Triangle::intersects(const Ray& _ray) {
	vec3 edge1, edge2, h, s, q;
	float a, f, u, v;
	const float EPSILON = 0.0000001f;
	edge1 = points[1] - points[0];
	edge2 = points[2] - points[0];
	h = glm::cross(_ray.getDirection(), edge2);
	a = glm::dot(edge1, h);
	if (a > -EPSILON && a < EPSILON)
		return false;    // This ray is parallel to this triangle.
	f = 1.0 / a;
	s = _ray.getStartPoint() - points[0];
	u = f * glm::dot(s, h);
	if (u < 0.0 || u > 1.0)
		return false;
	q = glm::cross(s, edge1);
	v = f * glm::dot(_ray.getDirection(), q);
	if (v < 0.0 || u + v > 1.0)
		return false;
	// At this stage we can compute t to find out where the intersection point is on the line.
	float t = f * glm::dot(edge2, q);
	if (t > EPSILON) // ray intersection
	{
		return true;
	}
	else // This means that there is a line intersection but not a ray intersection.
		return false;
}

vec3 Triangle::randomPointOnSurface() {
	float r1 = (float)rand() / (float)RAND_MAX;
	float r2 = (float)rand() / (float)RAND_MAX;
	vec3 point = (1 - sqrt(r1)) * points[0] + (sqrt(r1) * (1 - r2)) * points[1] + (sqrt(r1) * r2) * points[2];
	return point;
}

double Triangle::getArea() {
	vec3 edge1 = points[1] - points[0];
	vec3 edge2 = points[2] - points[0];
	vec3 cross = glm::cross(edge1, edge2);
	return 0.5 * glm::length(cross);
}