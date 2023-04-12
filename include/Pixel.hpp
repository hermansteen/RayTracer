#pragma once
#include <iostream>
#include <list>
#include "Ray.hpp"


class Pixel {
public: 
	Pixel();

	//void addRay(Ray&); //<- Might be a problem

	vec3 getPointFromPixel(int y, int z, int k, int l);

	void setColor(const colorDBL& color) { this->color = color; }
private:
	colorDBL color;
	Ray rayFromEye;
	//std::list<Ray> rayList; // <- Might be a problem
	//ostream operator
	friend std::ostream& operator<<(std::ostream& os, const Pixel& p);
};