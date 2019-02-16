#include "PointLight.h"

PointLight::PointLight(vec3 position, vec3 color, float intensity, float range, float size) :
	Light(position, color, intensity, range, size)
{
}

PointLight::~PointLight()
{
}

vec3 PointLight::GetDirection(const HitInfo& info) const
{
	return (m_position - info.p).normalized();
}