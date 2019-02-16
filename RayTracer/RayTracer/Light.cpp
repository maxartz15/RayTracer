#include "Light.h"

Light::Light(vec3 position, vec3 color, float intensity, float range, float size) :
	m_position(position),
	m_color(color),
	m_intensity(intensity),
	m_range(range),
	m_size(size)
{
}

Light::~Light()
{
}
