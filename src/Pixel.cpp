#include "Pixel.hpp"

/**
 * @brief Default constructor for the Pixel class.
 *
 * This constructor initializes a Pixel object with a default color of (0.0, 0.0, 0.0)
 * and creates a Ray object from the eye with zero vectors as the start and direction.
 * However, there might be an issue with the commented line that attempts to push the
 * rayFromEye object into a rayList container.
 */
Pixel::Pixel() {
	color = colorDBL(0.0, 0.0, 0.0);
	Ray rayFromEye(vec3(0.0f), vec3(0.0f));
	//rayList.push_back(rayFromEye); <- Might be a problem
}

/*void Pixel::addRay(Ray& _ray) { <- Might be a problem
	color = _ray.getColor();
	*rayList.begin() = _ray;
}*/

/**
 * @brief Calculates the 3D point on the camera plane corresponding to a pixel.
 *
 * This function calculates the 3D point on the camera plane that corresponds to a
 * given pixel position. The pixel position is specified by its row (y) and column (z)
 * indices, as well as two additional indices (k and l) for sub-pixel sampling.
 * The function applies a random displacement to the calculated point based on the
 * sub-pixel indices to introduce variation in the sampled points.
 *
 * @param y The row index of the pixel.
 * @param z The column index of the pixel.
 * @param k The sub-pixel index for vertical sampling.
 * @param l The sub-pixel index for horizontal sampling.
 * @return The 3D point on the camera plane corresponding to the pixel.
 */
vec3 Pixel::getPointFromPixel(int y, int z, int k, int l) {
	float displacement = (float)rand() / RAND_MAX;

	float tminy = 0.0f + 0.00125 * l;
	float tmaxy = 0.00125f + 0.00125 * l;
	float tminz = 0.0f + 0.00125 * k;
	float tmaxz = 0.00125f + 0.00125 * k;

	float displacementY = displacement * (tmaxy - tminy) + tminy;
	float displacementZ = displacement * (tmaxz - tminz) + tminz;

	vec3 intersectionPointCameraPlane = vec3(0.0f, 1.0f - y * 0.0025f - displacementY, 1.0 - z * 0.0025f - displacementZ); // tar fram mitten av pixel f�r respektive y och z

	return intersectionPointCameraPlane;
}

/**
 * @brief Overloaded stream insertion operator for the Pixel class.
 *
 * This operator allows a Pixel object to be inserted into an output stream. It prints
 * the color components of the Pixel (red, green, and blue) multiplied by 255 and
 * separated by spaces, followed by a space character.
 *
 * @param os The output stream to insert the Pixel into.
 * @param p The Pixel object to be inserted into the output stream.
 * @return A reference to the output stream after the Pixel has been inserted.
 */
std::ostream& operator<<(std::ostream& os, const Pixel& p)
{
	os << floor(p.color.r * 255) << " " << floor(p.color.g * 255) << " " << floor(p.color.b * 255) << " ";
	return os;
}
