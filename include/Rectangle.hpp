#include "Polygon.hpp"

class Rectangle : public Polygon {
public:
	Rectangle(vec3 point1, vec3 point2, vec3 point3, vec3 point4, colorDBL color);
	vec3 calculateIntersection(vec3 startingPoint, Direction direction) override;
};