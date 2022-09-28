#pragma once
#include <vector>
#include "Rectangle.hpp"
#include "Triangle.hpp"
#include "Ray.hpp"

class Scene {
public:
	Scene();

	void createScene();

	std::vector<Triangle> sceneTriangles;
	std::vector<Rectangle> sceneRectangles;

	Polygon* getHitGeometry(const Ray& _ray, vec3& intersection);
private:
};