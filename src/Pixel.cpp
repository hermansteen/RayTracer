#include "Pixel.hpp"

Pixel::Pixel() {

}

std::ostream& operator<<(std::ostream& os, const Pixel& p)
{
	os << p.color.r << " " << p.color.g << " " << p.color.b << " ";
	return os;
}
