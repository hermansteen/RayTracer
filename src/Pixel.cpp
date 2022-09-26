#include "Pixel.hpp"

Pixel::Pixel() {

}

std::ostream& operator<<(std::ostream& os, const Pixel& p)
{
	os << floor(p.color.r * 255) << " " << floor(p.color.g * 255) << " " << floor(p.color.b * 255) << " ";
	return os;
}
