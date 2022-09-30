#include "Polygon.hpp"
#include "Ray.hpp"

class Sphere : public Polygon {
public:
	Sphere(vec3 center, float radius, colorDBL color);
	vec3 calculateIntersectionPoint(vec3 startingPoint, Direction direction) override;
	bool intersects(const Ray&) override;
	vec3 getCenter() { return points[0]; };
	vec3 getSphereNormal(const vec3&);
	
private:
	float radius;

};