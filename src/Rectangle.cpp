#include "Rectangle.hpp"

Rectangle::Rectangle(vec3 point1, vec3 point2, vec3 point3, vec3 point4, colorDBL _color)
{
	//instantiate points vector
	points = new vec3[4];
	points[0] = point1;
	points[1] = point2;
	points[2] = point3;
	points[3] = point4;
	color = _color;
	calculateNormal();
}

vec3 Rectangle::calculateIntersectionPoint(vec3 startingPoint, Direction direction)
{
	vec3 intersection;
	float t = glm::dot(normal, (points[0] - startingPoint)) / glm::dot(normal, direction);
	intersection = startingPoint + t * direction;
	return intersection;
}

//calculate if ray intersects quad using moller trumbore algorithm
bool Rectangle::intersects(const Ray& _ray) {
	Triangle triangle1 = Triangle(points[0], points[1], points[2], color);
	Triangle triangle2 = Triangle(points[0], points[2], points[3], color);
	if (triangle1.intersects(_ray) || triangle2.intersects(_ray)) {
		return true;
	}
	else {
		return false;
	} 
}