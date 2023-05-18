#include "Rectangle.hpp"

/**
 * @brief Constructs a Rectangle object with the given points, color, and surface type.
 *
 * @param point1 The first point of the rectangle.
 * @param point2 The second point of the rectangle.
 * @param point3 The third point of the rectangle.
 * @param point4 The fourth point of the rectangle.
 * @param _color The color of the rectangle.
 * @param _surface The surface type of the rectangle.
 */
Rectangle::Rectangle(vec3 point1, vec3 point2, vec3 point3, vec3 point4, colorDBL _color, std::string _surface)
{
	//instantiate points vector
	points = new vec3[4];
	points[0] = point1;
	points[1] = point2;
	points[2] = point3;
	points[3] = point4;
	color = _color;
	calculateNormal();
	surfaceType = _surface;
	isSphere = false;
		
}

/**
 * @brief Calculates the intersection point between the rectangle and a ray.
 *
 * @param startingPoint The starting point of the ray.
 * @param direction The direction of the ray.
 * @return The intersection point between the rectangle and the ray.
 */
vec3 Rectangle::calculateIntersectionPoint(vec3 startingPoint, Direction direction)
{
	vec3 intersection;
	float t = glm::dot(normal, (points[0] - startingPoint)) / glm::dot(normal, direction);
	intersection = startingPoint + t * direction;
	return intersection;
}

//calculate if ray intersects quad using moller trumbore algorithm
/**
 * @brief Checks if the rectangle intersects with a given ray.
 *
 * @param _ray The ray to check for intersection.
 * @return True if the rectangle intersects with the ray, false otherwise.
 */
bool Rectangle::intersects(const Ray& _ray) {
	Triangle triangle1 = Triangle(points[0], points[1], points[2], color, surfaceType);
	Triangle triangle2 = Triangle(points[0], points[2], points[3], color, surfaceType);
	
	if (triangle1.intersects(_ray) || triangle2.intersects(_ray)) {
		return true;
	}
	else {
		return false;
	}
}