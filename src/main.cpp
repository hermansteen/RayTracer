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
	
	auto end = std::chrono::high_resolution_clock::now();
	//print time elapsed in seconds
	std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << "s" << std::endl;
	return 0;
}