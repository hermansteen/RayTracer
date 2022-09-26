#pragma once
#include "Rectangle.hpp"
#include "Triangle.hpp"
#include "Polygon.hpp"

class Scene {
public:
	Scene();

	void createScene();

	std::vector<Triangle> sceneTriangles;
	std::vector<Rectangle> sceneRectangles;
};