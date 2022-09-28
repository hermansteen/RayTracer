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
			Pixel p;
			Ray rays = Ray(vec3(0.0f), vec3(0.0f));

			for(int k = 0; k < 1; k++) {
				for(int l = 0; l < 1; l++ ) {
					vec3 rayEnd = p.getPointFromPixel(i, j, l, k, RAYSPERPIXEL);
					Ray shotRay = Ray(eye, (rayEnd - eye));
					p.addRay(shotRay);
					colorDBL shotColor = shootRay(_scene, shotRay);
					rays.addColor(shotColor);
				}
			}
			p.setColor(rays.getColor().operator/=(RAYSPERPIXEL));
			pixels[i][j] = p;
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

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			img << pixels[i][j];
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

	if (length(_ray.getStartPoint() - rayEnd) < distanceToIntersection) {
		intersectionPoint = rayEnd;
		distanceToIntersection = length(_ray.getStartPoint() - rayEnd);
		_ray.addColor(hitPolygon->getColor());
	}
	return _ray.getColor();
}
