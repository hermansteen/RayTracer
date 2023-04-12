#pragma once
#include "definitions.hpp"
#include <math.h>
#include "Pixel.hpp"
#include "Scene.hpp"
#include "Ray.hpp"
#include "Rectangle.hpp"
#include "Triangle.hpp"
#include "Polygon.hpp"

class Camera {
public:
	Camera();

	void render(Scene& _scene);
	
	void saveImage(Scene& _scene);
private:
	//2d array of pixels
	Pixel** pixels = new Pixel*[WIDTH];
	//cameraPlaneVertex
	vec3 cameraPlaneVertex[2][2];
	//eye pos
	vec3 eye = vec3(-1.0f, 0.0f, 0.0f); //vec3(-1.0f, 0.0f, 0.0f);

	const float pixelLength = 0.0025f;

	//shootRay
	colorDBL shootRay(Scene&, Ray&, int);

	bool russianRoulette(const colorDBL&);
	bool inShade(Scene&, Direction, vec3);

	double lightCalculation(vec3, Scene&, vec3, double);
};