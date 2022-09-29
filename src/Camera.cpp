#include "Camera.hpp"
#include <fstream>

Camera::Camera() {
	cameraPlaneVertex[0][0] = vec3(0.0f, -1.0f, -1.0f);
	cameraPlaneVertex[1][0] = vec3(0.0f, 1.0f, -1.0f);
	cameraPlaneVertex[0][0] = vec3(0.0f, -1.0f, 1.0f);
	cameraPlaneVertex[1][1] = vec3(0.0f, 1.0f, 1.0f);
	for (int i = 0; i < WIDTH; i++) {
		pixels[i] = new Pixel[WIDTH];
	}
}

void Camera::render(Scene& _scene) {
	
	for(int i = 0; i < WIDTH; i++) {
		for(int j = 0; j < HEIGHT;j++) {
			Pixel screenPixel;
			Ray finalRay = Ray(vec3(0.0f), vec3(0.0f));
			for(int k = 0; k < RAYSPERPIXEL; k++) {
				for(int l = 0; l < RAYSPERPIXEL; l++ ) {
					vec3 rayEnd = screenPixel.getPointFromPixel(i, j, l, k);
		
					Ray shotRay = Ray(eye, glm::normalize((rayEnd - eye)));
					screenPixel.addRay(shotRay);
					colorDBL shotColor = shootRay(_scene, shotRay);
					finalRay.addColor(shotColor);
				}
			}
			screenPixel.setColor(finalRay.getColor().operator/=(RAYSPERPIXEL));
			//@TODO, debug assignment operator
			pixels[i][j] = screenPixel;
		}
	}
}
//Save as .ppm-file
void Camera::saveImage(Scene& _scene)
{
	const int width = 800, height = 800;

	std::ofstream img("render.ppm");
	img << "P3" << std::endl;
	img << width << " " << height << std::endl;
	img << "255" << std::endl;
	render(_scene);

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			img << pixels[j][i];
		}
	}
}

bool Camera::russianRoulette(const colorDBL& areaCol) {
	float random = (float)rand() / (float)RAND_MAX;
	float threshold = 0.5f * ((float)length(areaCol) / (float)length(colorDBL(1.0f)));
	if (random < threshold) {
		return true;
	}
	else {
		return false;
	}
}

colorDBL Camera::shootRay(Scene& _scene, Ray& _ray) {
	vec3 intersectionPoint;
	float distanceToIntersection = 100.f;
	vec3 rayEnd = vec3(0.0f);

	Polygon* hitPolygon = _scene.getHitGeometry(_ray, intersectionPoint);

	if ((length(_ray.getStartPoint() - rayEnd) < distanceToIntersection) && (hitPolygon != nullptr)) {
		intersectionPoint = rayEnd;
		distanceToIntersection = length(_ray.getStartPoint() - rayEnd);
		_ray.addColor(hitPolygon->getColor());
	}
	return _ray.getColor();
}
