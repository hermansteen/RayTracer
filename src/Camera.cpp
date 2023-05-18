#include "Camera.hpp"
#include <fstream>

/**
 * @brief Default constructor for the Camera class.
 *
 * This constructor initializes a Camera object by setting up the camera plane vertices
 * and allocating memory for the pixel grid. The camera plane vertices define the boundaries
 * of the camera's field of view. The pixel grid is a 2D array of Pixel objects used to store
 * the color information for each pixel in the rendered image.
 */
Camera::Camera() {
	cameraPlaneVertex[0][0] = vec3(0.0f, -1.0f, -1.0f);
	cameraPlaneVertex[1][0] = vec3(0.0f, 1.0f, -1.0f);
	cameraPlaneVertex[0][0] = vec3(0.0f, -1.0f, 1.0f);
	cameraPlaneVertex[1][1] = vec3(0.0f, 1.0f, 1.0f);
	for (int i = 0; i < WIDTH; i++) {
		pixels[i] = new Pixel[WIDTH];
	}
}

/**
 * @brief Renders the scene by calculating the color of each pixel.
 *
 * This function captures the scene by calculating the color of each pixel in the image.
 * It performs subsampling to improve the quality of the rendered image. For each pixel,
 * multiple rays are shot from different positions within the pixel, and their colors are
 * averaged to determine the final color for the pixel. The process is repeated for all
 * pixels in the image. Progress updates are provided during the rendering process, indicating
 * the number of pixels calculated and the percentage of the rendering progress.
 *
 * @param _scene The scene to be rendered.
 */
void Camera::render(Scene& _scene) {
	std::cout << "Capturing scene..." << "\n";
	std::cout << "Number of pixels to calculate: " << WIDTH * HEIGHT << "\n";
	int pixelCount = 0;
	double percentDone = 0.0;
	
	Pixel screenPixel;
	Ray finalRay = Ray(vec3(0.0f), vec3(0.0f));
	
	
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			
			//Subsampling
			for (int k = 0; k < RAYSPERPIXEL; k++) {
				for (int l = 0; l < RAYSPERPIXEL; l++) {
					vec3 rayEnd = screenPixel.getPointFromPixel(i, j, l, k);
					Ray shotRay = Ray(eye, vec3(0.0f));
					shotRay.setDirection(glm::normalize((rayEnd - eye)));
					//screenPixel.addRay(shotRay);
					colorDBL shotColor = shootRay(_scene, shotRay, BOUNCES);
					finalRay.addColor(shotColor);					
				}
			}
			screenPixel.setColor(finalRay.getColor().operator/=((double)(RAYSPERPIXEL*RAYSPERPIXEL)));
			pixels[i][j] = screenPixel;
			finalRay.setColor(vec3(0.0f));
			pixelCount++;
			
			if (pixelCount % 10000 == 0) {
				std::cout <<  pixelCount << " / " << WIDTH * HEIGHT << " pixels calculated" << std::endl;
				percentDone = (double)pixelCount / (double)(WIDTH * HEIGHT) * 100.0;
				std::cout << percentDone << "% done." << std::endl;
			}
			
		}
	}
}
/**
 * @brief Saves the rendered image to a PPM file.
 *
 * This function saves the rendered image to a PPM file format. It iterates over the pixels
 * in the image and writes their color values to the file. Additionally, it provides progress
 * updates during the saving process, displaying the number of pixels saved and the percentage
 * of the image saved.
 *
 * @param _scene The scene containing the rendered image.
 */
void Camera::saveImage(Scene& _scene)
{	
	std::cout << "Saving image..." << "\n";
	int pixelCount = 0;
	double percentDone = 0.0;
	
	std::ofstream img("render.ppm");
	img << "P3" << std::endl;
	img << WIDTH << " " << HEIGHT << std::endl;
	img << "255" << std::endl;

	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			img << pixels[j][i];
			pixelCount++;
			if (pixelCount % 10000 == 0) {
				std::cout << pixelCount << " / " << WIDTH * HEIGHT << " pixels saved" << std::endl;
				percentDone = (double)pixelCount / (double)(WIDTH * HEIGHT) * 100.0;
				std::cout << percentDone << "% done." << std::endl;
			}				
		}
	}
	std::cout << "Image saved!" << "\n";
}

/**
 * @brief Determines whether a ray should be terminated or continued based on a probabilistic criterion.
 *
 * This function implements a simplified version of the Russian roulette algorithm
 * to make a decision about terminating or continuing a ray in a rendering process.
 * The decision is based on a randomized probability calculation and the color of the
 * polygon that the ray last intersected with.
 *
 * @param areaCol The color of the polygon the ray last intersected with.
 * @return `true` if the ray should be terminated, `false` if it should be continued.
 */
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

/**
 * @brief Shoots a ray into the scene and calculates the color of the intersection point.
 *
 * This function shoots a ray into the scene and calculates the color of the intersection point.
 * It performs various calculations depending on the properties of the hit polygon, such as diffuse
 * reflection, mirror reflection, and light emission. The function also handles ray splitting and
 * recursive ray tracing for global illumination effects. The resulting color is clamped to ensure
 * it does not exceed the maximum value of 1.0 before being returned.
 *
 * @param _scene The scene containing the geometry and light sources.
 * @param _ray The ray to be shot into the scene.
 * @param _bounces The maximum number of ray bounces allowed for recursive ray tracing.
 * @return The color of the intersection point.
 */
colorDBL Camera::shootRay(Scene& _scene, Ray& _ray, int _bounces) {
	
	if (_bounces >= 0) {
		vec3 intersectionPoint;
		float distanceToIntersection = 100.f;
		vec3 rayEnd = vec3(0.0f);
		colorDBL finalColor = colorDBL(0.0f);
		colorDBL splittedColor = colorDBL(0.0f);
	
		Polygon* hitPolygon = _scene.getHitGeometry(_ray, intersectionPoint, false);
		rayEnd = intersectionPoint;
	
		if ((length(_ray.getStartPoint() - rayEnd) < distanceToIntersection) && (hitPolygon != nullptr)) {
			
			distanceToIntersection = length(_ray.getStartPoint() - intersectionPoint);
			vec3 normal = vec3(0.0f);

			//If the hitPolygon is a sphere we need to cast it to a sphere to get the normal
			if (hitPolygon->isSphere) {
				normal = ((Sphere*)hitPolygon)->getSphereNormal(intersectionPoint);
			}
			else {
				normal = hitPolygon->getNormal();
			}

			//Is the polygon a diffuse?
			if (hitPolygon->getSurfaceType() == DIFFUSE) {
				
				double brdf = 0.00000033f;
				double radiance = lightCalculation(intersectionPoint, _scene, normal, brdf);
				
				_ray.addColor(hitPolygon->getColor() * radiance);
				
				//See if the ray should be splitted
				if (russianRoulette(hitPolygon->getColor())) { //Russian roulette
					int splits = rand() % 5;
					
					for (int n = 0; n < splits; n++) {
						
						Direction randomDirection;
	
						//Check that the new direction is acutally inside the scene
						do {
							randomDirection = glm::normalize(normal + vec3((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX));
						} while ((glm::dot(randomDirection, normal)) < 0 || glm::dot(randomDirection, normal) > PI/2);
						
						//Ray newRay = Ray(intersectionPoint + randomDirection * 0.05f, randomDirection);
						_ray.setNextRay(new Ray(intersectionPoint + randomDirection * 0.05f, randomDirection));
						
						//_ray.addColor(shootRay(_scene, newRay, _bounces - 1) / (double)(splits + 1));
						_ray.addColor(shootRay(_scene, *_ray.getNextRay(), _bounces - 1) / (double)(splits + 1));
						
						//delete _ray.getNextRay();
						_ray.removeLastRay();
						
						
						
					}				
				}
			}
			
			//Is the polygon a mirror?
			else if (hitPolygon->getSurfaceType() == MIRROR) {

				vec3 direction = _ray.getDirection();

				vec3 reflectedDirection = glm::normalize(direction - 2.0f * glm::dot(direction, normal) * normal);
				
				//Move the startpoint a little bit away from the intersection point to avoid self intersection.
				//Ray reflectedRay = Ray(intersectionPoint + reflectedDirection * 0.01f, reflectedDirection);
				_ray.setNextRay(new Ray(intersectionPoint + reflectedDirection * 0.01f, reflectedDirection));

				//_ray.addColor(shootRay(_scene, reflectedRay, _bounces - 1));
				_ray.addColor(shootRay(_scene, *_ray.getNextRay(), _bounces - 1));
				_ray.removeLastRay();
			}
			
			else if (hitPolygon->getSurfaceType() == LIGHTSOURCE) {
				_ray.addColor(hitPolygon->getColor());
			}	
		}
	}	

	_ray.removeLastRay();
	
	//Clamp	color, just make sure that the color is not above 1.0
	if (_ray.getColor().r > 1.0f) {
		colorDBL color = _ray.getColor();
		color.r = 1.0f;
		_ray.setColor(color);
	}
	if (_ray.getColor().g > 1.0f) {
		colorDBL color = _ray.getColor();
		color.g = 1.0f;
		_ray.setColor(color);
	}
	if (_ray.getColor().b > 1.0f) {
		colorDBL color = _ray.getColor();
		color.b = 1.0f;
		_ray.setColor(color);
	}
	
	return _ray.getColor();
}


//Check if the ray between the intersection point and the light source is blocked by another polygon
/**
 * @brief Checks if a point is in shade from a light source.
 *
 * This function checks if a given point is in shade from a light source in the scene.
 * It creates a ray from the point towards the light source and checks if any geometry
 * intersects with the ray before reaching the light source. If an intersection occurs
 * with a polygon that is not a light source, the point is considered to be in shade.
 *
 * @param _scene The scene containing the geometry and light sources.
 * @param _lightDirection The direction of the light source.
 * @param _intersectionPoint The point to be checked for shading.
 * @return True if the point is in shade, False otherwise.
 */
bool Camera::inShade(Scene& _scene, Direction _lightDirection, vec3 _intersectionPoint ) {

	Ray lightRay = Ray(_intersectionPoint, _lightDirection);
	vec3 intersectionPoint;
	float distanceToIntersection = 100.f;
	
	Polygon* hitPolygon = _scene.getHitGeometry(lightRay, intersectionPoint, false);
	//If the polygon is a lightsource we don't want to count it as a hit, if hitPolygon == nullptr, we didn't hit anything.
	if ((hitPolygon != nullptr) && (hitPolygon->getSurfaceType() != LIGHTSOURCE)) {		
		return true;
	}
	else {
		return false;
	}
}

//Calculate the radiance from the light source at the point of intersection
/**
 * @brief Calculates the light contribution at a given intersection point.
 *
 * This function calculates the light contribution at a given intersection point by
 * considering all the light sources in the scene. It uses Monte Carlo integration
 * to estimate the light contribution by sampling points on the light sources.
 * The light calculation takes into account the BRDF (Bidirectional Reflectance
 * Distribution Function), distance, angles between the surface normal and the
 * light direction, and the surface area of the light source.
 *
 * @param _intersectionPoint The point of intersection on the surface.
 * @param _scene The scene containing the geometry and light sources.
 * @param _normal The surface normal at the intersection point.
 * @param _BRDF The BRDF (Bidirectional Reflectance Distribution Function) value.
 * @return The calculated light contribution at the intersection point.
 */
double Camera::lightCalculation(vec3 _intersectionPoint, Scene& _scene, vec3 _normal, double _BRDF) {

	const double L = 3200.0;
	
	double numerator = 0.0;
	double estimation = 0.0;
	double distance = 0.0;
	double cosTheta = 0.0;
	double cosPhi = 0.0;
	double BRDF = 0.0;
	
	//Go through all the light sources in the scene and loop through for the lightsamples
	for (int i = 0; i < _scene.sceneLights.size(); i++) {
		for (int j = 0; j < LIGHTSAMPLES; j++) {
			//Get a random point on the light source and calculate the direction
			vec3 lightSourcePoint = ((Triangle*)_scene.sceneLights[i])->randomPointOnSurface();
			Direction lightDirection = glm::normalize((lightSourcePoint - _intersectionPoint));
			//Check if the point is NOT in shade
			if (!inShade(_scene, lightDirection, _intersectionPoint + lightDirection * 0.05f)) {
				//The ray between the intersection point and the light source 
				vec3 shadowRay = lightSourcePoint - _intersectionPoint;
				
				distance = length(shadowRay);
				cosTheta = glm::dot(_normal, shadowRay) / distance;
				cosPhi = glm::dot(_scene.sceneLights[i]->getNormal(), shadowRay) / distance;
				numerator += _BRDF * (cosTheta * cosPhi) / (distance * distance);
			}
		}	
		estimation += numerator;
		estimation = ((((Triangle*)_scene.sceneLights[i])->getArea() * L) / LIGHTSAMPLES*1.0f) * estimation;
	}
	return estimation / 1.0f * _scene.sceneLights.size();
}