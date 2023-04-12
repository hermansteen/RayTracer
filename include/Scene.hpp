#pragma once
//#include <vector>
#include "Rectangle.hpp"
#include "Triangle.hpp"
#include "Sphere.hpp"
#include "Ray.hpp"

class Scene {
public:
	Scene();

	void createScene();

	//might be possible to refactor to std::vector<Polygon*> scenePolygons
	std::vector<Polygon*> sceneObjects;
	std::vector<Polygon*> sceneLights;

	Polygon* getHitGeometry(Ray& _ray, vec3& intersection, bool _isShadowRay);
private:
	float closestDistance = 100.0f;
};