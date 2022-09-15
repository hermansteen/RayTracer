#include "Camera.hpp"
#include <fstream>

Camera::Camera() {

}

void Camera::render(Scene& _scene) {

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
			int r = (int)(255 * pixels[i][j].color.r);
			int g = (int)(255 * pixels[i][j].color.g);
			int b = (int)(255 * pixels[i][j].color.b);

			img << r << " " << g << " " << b << std::endl;
		}
	}
}
