#include "Sphere.hpp"

Sphere::Sphere(vec3 _center, float _radius, colorDBL _color, std::string _surface)
{
	points = new vec3[1];
	points[0] = _center;
	radius = _radius;
	color = _color;
	surfaceType = _surface;
	isSphere = true;
		
}

vec3 Sphere::calculateIntersectionPoint(vec3 _startPoint, Direction _direction)
{
	vec3 center = points[0];
	vec3 startPoint = _startPoint;
	Direction direction = _direction;
	
	float a = 1;
	float b = 2 * dot(direction, startPoint - center);
	float c = dot(startPoint - center, startPoint - center) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		return vec3(0, 0, 0);
	}
	else
	{
		float t1 = (-b + sqrt(discriminant)) / (2 * a);
		float t2 = (-b - sqrt(discriminant)) / (2 * a);
		if (t1 < 0 && t2 < 0)
		{
			return vec3(0, 0, 0);
		}
		else if (t1 < 0)
		{
			return startPoint + t2 * direction;
		}
		else if (t2 < 0)
		{
			return startPoint + t1 * direction;
		}
		else
		{
			return startPoint + std::min(t1, t2) * direction;
		}
	}
}

bool Sphere::intersects(const Ray& _ray)
{
	vec3 center = points[0];
	vec3 startingPoint = _ray.getStartPoint();
	Direction direction = _ray.getDirection();
	float a = 1;
	float b = 2 * dot(direction, startingPoint - center);
	float c = dot(startingPoint - center, startingPoint - center) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	
	if (discriminant < 0)
	{
		return false;
	}
	else
	{
		float t1 = (-b + sqrt(discriminant)) / (2 * a);
		float t2 = (-b - sqrt(discriminant)) / (2 * a);
		if (t1 < 0 && t2 < 0)
		{
			return false;
		}
		else if (t1 < 0)
		{
			return true;
		}
		else if (t2 < 0)
		{
			return true;
		}
		else
		{
			return true;
		}
	}
}

vec3 Sphere::getSphereNormal(const vec3& _point)
{
	return glm::normalize(points[0] - _point); //Switch to _point - points[0] if the normals are backwards

	
}
