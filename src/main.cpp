#pragma once
#include "Camera.hpp"
#include <vector>
#include <chrono>

//main function body
int main() {
	auto start = std::chrono::high_resolution_clock::now();
	
	Scene scene;
	Camera camera;
	camera.render(scene);
	camera.saveImage(scene);
	
	return 0;
}