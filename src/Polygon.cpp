#include "Polygon.hpp"

/**
 * @brief Calculate the normal vector of the Polygon.
 *
 * This function calculates the normal vector of the Polygon by taking the cross product
 * of two edge vectors formed by the first three vertices of the Polygon. The result is
 * then normalized to ensure a unit length.
 */
void Polygon::calculateNormal() {
	// Calculate the normal of the polygon
	// The normal is the cross product of two vectors of the polygon
	// We use the first three vertices to calculate two edge vectors and take the cross product of those
	// We then normalize the result
	vec3 v1 = points[1] - points[0];
	vec3 v2 = points[2] - points[0];
	normal = glm::normalize(glm::cross(v1, v2));
}