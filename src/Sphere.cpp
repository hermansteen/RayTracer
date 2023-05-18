#include "Sphere.hpp"


/**
 * @brief Construct a Sphere object with the specified center, radius, color, and surface type.
 * 
 * This constructor initializes a Sphere object with the given center coordinates, radius, color, and surface type.
 * The center of the sphere is specified by the _center parameter.
 * The radius of the sphere is specified by the _radius parameter.
 * The color of the sphere is specified by the _color parameter.
 * The surface type of the sphere is specified by the _surface parameter.
 * The isSphere flag is set to true to indicate that this object is a sphere.
 * 
 * @param _center The center coordinates of the sphere.
 * @param _radius The radius of the sphere.
 * @param _color The color of the sphere.
 * @param _surface The surface type of the sphere.
 */
Sphere::Sphere(vec3 _center, float _radius, colorDBL _color, std::string _surface)
{
	points = new vec3[1];
	points[0] = _center;
	radius = _radius;
	color = _color;
	surfaceType = _surface;
	isSphere = true;
		
}

/**
 * @brief Calculates the intersection point between a ray and the sphere.
 * 
 * This method calculates and returns the intersection point between a ray defined by a start point and direction
 * and the sphere. The intersection point is determined by solving the quadratic equation derived from the ray-sphere intersection formula.
 * If there is no intersection, the method returns the zero vector (0, 0, 0).
 * 
 * @param _startPoint The start point of the ray.
 * @param _direction The direction of the ray.
 * @return The intersection point between the ray and the sphere, or the zero vector if there is no intersection.
 */
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

/**
 * @brief Checks if a ray intersects with the sphere.
 *
 * This method determines whether a given ray intersects with the sphere or not. It calculates the intersection using
 * the ray-sphere intersection formula and checks if the discriminant is greater than or equal to zero.
 * If the discriminant is less than zero, there is no intersection and the method returns false. Otherwise, it returns true.
 *
 * @param _ray The ray to check for intersection.
 * @return True if the ray intersects with the sphere, false otherwise.
 */
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

/**
 * @brief Calculates the normal vector of the sphere at a given point.
 *
 * This method calculates the normal vector of the sphere at the specified point. It subtracts the point's coordinates
 * from the sphere's center coordinates and normalizes the resulting vector to obtain the unit normal vector.
 * Note: If the normals appear to be facing the wrong direction, you can switch the subtraction order to _point - points[0].
 *
 * @param _point The point at which to calculate the normal vector.
 * @return The normalized normal vector of the sphere at the given point.
 */
vec3 Sphere::getSphereNormal(const vec3& _point)
{
	return glm::normalize(points[0] - _point); //Switch to _point - points[0] if the normals are backwards	
}
