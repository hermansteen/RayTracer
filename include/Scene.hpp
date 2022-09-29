#pragma once
#include <vector>
#include "Rectangle.hpp"
#include "Triangle.hpp"
#include "Sphere.hpp"
#include "Ray.hpp"

class Scene {
public:
	Scene();

	void createScene();

	//might be possible to refactor to std::vector<Polygon*> scenePolygons
	/*std::vector<Triangle> sceneTriangles;
	std::vector<Rectangle> sceneRectangles;
	std::vector<Sphere> sceneSpheres;*/
	std::vector<Polygon*> sceneObjects;

	Polygon* getHitGeometry(const Ray& _ray, vec3& intersection);
private:
};