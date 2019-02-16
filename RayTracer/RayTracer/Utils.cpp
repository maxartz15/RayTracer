#include "Utils.h"

sf::Color Utils::Vec3ToColor(const vec3& c, bool to255 = false)
{
	if (to255)
	{
		return sf::Color(sf::Uint8(unsigned int(c.r * 255)), sf::Uint8(unsigned int(c.g * 255)), sf::Uint8(unsigned int(c.b * 255)));
	}
	else
	{
		return sf::Color(sf::Uint8(unsigned int(c.r)), sf::Uint8(unsigned int(c.g)), sf::Uint8(unsigned int(c.b)));
	}
}
