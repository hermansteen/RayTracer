#include "Pixel.hpp"

Pixel::Pixel() {
	color = colorDBL(0.0, 0.0, 0.0);
	Ray rayFromEye(vec3(0.0f), vec3(0.0f));
	rayList.push_back(rayFromEye);
}

void Pixel::addRay(Ray& _ray) {
	color = _ray.getColor();
	*rayList.begin() = _ray;
}

vec3 Pixel::getPointFromPixel(int y, int z, int k, int l) {
	float displacement = (float)rand() / RAND_MAX;

	float tminy = 0.0f + 0.00125 * l;
	float tmaxy = 0.00125f + 0.00125 * l;
	float tminz = 0.0f + 0.00125 * k;
	float tmaxz = 0.00125f + 0.00125 * k;

	float displacementY = displacement * (tmaxy - tminy) + tminy;
	float displacementZ = displacement * (tmaxz - tminz) + tminz;

	vec3 intersectionPointCameraPlane = vec3(0.0f, 1.0f - y * 0.0025f - displacementY, 1.0 - z * 0.0025f - displacementZ); // tar fram mitten av pixel för respektive y och z

	return intersectionPointCameraPlane;
}

std::ostream& operator<<(std::ostream& os, const Pixel& p)
{
	os << floor(p.color.r * 255) << " " << floor(p.color.g * 255) << " " << floor(p.color.b * 255) << " ";
	return os;
}
