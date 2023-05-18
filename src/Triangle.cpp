#include "Triangle.hpp"

/**
 * @brief Constructs a Triangle object with three points, color, and surface type.
 *
 * This constructor initializes a Triangle object with three points defining its vertices, a color, and a surface type.
 * The points are stored in the `points` array, and the normal vector is calculated using the `calculateNormal` method.
 * The `isSphere` flag is set to false to indicate that this object is not a sphere.
 *
 * @param point1 The first vertex of the triangle.
 * @param point2 The second vertex of the triangle.
 * @param point3 The third vertex of the triangle.
 * @param _color The color of the triangle.
 * @param _surface The surface type of the triangle.
 */
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
/**
 * @brief Calculates the intersection point between a ray and the triangle.
 *
 * This method calculates the intersection point between a ray and the triangle. It uses the Moller-Trumbore algorithm
 * to determine if the ray intersects the triangle. If an intersection occurs, it returns the intersection point.
 *
 * @param startingPoint The starting point of the ray.
 * @param direction The direction of the ray.
 * @return The intersection point between the ray and the triangle. If no intersection occurs, returns a zero vector.
 */
vec3 Triangle::calculateIntersectionPoint(vec3 startingPoint, Direction direction)
{
	vec3 intersection;
	float t = glm::dot(normal, (points[0] - startingPoint)) / glm::dot(normal, direction);
	intersection = startingPoint + t * direction;
	return intersection;
}

//calculate if ray intersects triangle using moller trumbore algorithm
/**
 * @brief Checks if a ray intersects with the triangle.
 *
 * This method checks if a given ray intersects with the triangle. It uses the Moller-Trumbore algorithm to perform
 * the intersection test. If an intersection occurs, it returns true; otherwise, it returns false.
 *
 * @param _ray The ray to check for intersection.
 * @return True if the ray intersects with the triangle, false otherwise.
 */
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

/**
 * @brief Generates a random point on the surface of the triangle.
 *
 * This method generates a random point on the surface of the triangle using barycentric coordinates.
 * It first generates two random numbers `r1` and `r2` between 0 and 1.
 * The random point is calculated using the formula: 
 * `point = (1 - sqrt(r1)) * points[0] + (sqrt(r1) * (1 - r2)) * points[1] + (sqrt(r1) * r2) * points[2]`.
 *
 * @return A randomly generated point on the surface of the triangle.
 */
vec3 Triangle::randomPointOnSurface() {
	float r1 = (float)rand() / (float)RAND_MAX;
	float r2 = (float)rand() / (float)RAND_MAX;
	vec3 point = (1 - sqrt(r1)) * points[0] + (sqrt(r1) * (1 - r2)) * points[1] + (sqrt(r1) * r2) * points[2];
	return point;
}

/**
 * @brief Calculates the area of the triangle.
 *
 * This method calculates the area of the triangle using the cross product of its two edges.
 * The area is computed as half the length of the cross product vector.
 *
 * @return The area of the triangle.
 */
double Triangle::getArea() {
	vec3 edge1 = points[1] - points[0];
	vec3 edge2 = points[2] - points[0];
	vec3 cross = glm::cross(edge1, edge2);
	return 0.5 * glm::length(cross);
}