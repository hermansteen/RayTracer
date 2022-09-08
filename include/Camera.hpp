#include "definitions.hpp"

class Camera {
public:
	Camera(int size = 800);
	
private:
	//2d array of pixels
	
	colorDBL** pixels;
};