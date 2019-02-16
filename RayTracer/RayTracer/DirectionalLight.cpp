#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(vec3 position, vec3 color, float intensity, float size) :
	Light(position, color, intensity, INFINITY, size)
{
	m_position = position * 100000;
}

DirectionalLight::~DirectionalLight()
{
}

vec3 DirectionalLight::GetDirection(const HitInfo& info) const
{
	info;
	return (m_position).normalized();
}