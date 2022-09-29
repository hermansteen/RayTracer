#pragma once
#include <iostream>
#include <list>
#include "Ray.hpp"


class Pixel {
public: 
	Pixel();

	void addRay(Ray&);

	vec3 getPointFromPixel(int y, int z, int k, int l);

	void setColor(const colorDBL& color) { this->color = color; }
private:
	colorDBL color;
	Ray rayFromEye;
	std::list<Ray> rayList;
	//ostream operator
	friend std::ostream& operator<<(std::ostream& os, const Pixel& p);
};