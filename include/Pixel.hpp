#pragma once
#include "definitions.hpp"
#include <iostream>


class Pixel {
public: 
	Pixel();
	colorDBL color;
private:
	//ostream operator
	friend std::ostream& operator<<(std::ostream& os, const Pixel& p);
};