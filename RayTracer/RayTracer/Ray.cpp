#include "Ray.h"

Ray::Ray(const vec3& origin, const vec3& direction) :
	m_origin(origin),
	m_direction(direction)
{
}

Ray::~Ray()
{
}

vec3 Ray::origin() const
{
	return m_origin;
}

vec3 Ray::direction() const
{
	return m_direction;
}

vec3 Ray::point(float t) const
{
	return (m_origin + t * m_direction);
}