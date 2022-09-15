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
}
