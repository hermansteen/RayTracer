#include "Polygon.hpp"

void Polygon::calculateNormal() {
	// Calculate the normal of the polygon
	// The normal is the cross product of two vectors on the polygon
	// We use the first three vertices to calculate two edge vectors and take the cross product of those
	// We then normalize the result
	vec3 v1 = points[1] - points[0];
	vec3 v2 = points[2] - points[0];
	normal = glm::normalize(glm::cross(v1, v2));
}