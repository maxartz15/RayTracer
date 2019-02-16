#include "PhongMaterial.h"
#include "Tracers.h"

PhongMaterial::PhongMaterial(vec3 color, float shininess) :
	m_color(color),
	m_shininess(shininess)
{
}

PhongMaterial::~PhongMaterial()
{
}

vec3 PhongMaterial::Color(const Ray & ray, const Scene & scene, HitInfo & info) const
{
	ray;

	vec3 diffuse = Trace::Diffuse(scene, info);
	vec3 specular = Trace::Specular(ray, scene, info, m_shininess);
	float shadow = Trace::Shadow(scene, info);

	vec3 c = m_color * (diffuse + specular) * shadow + scene.GetAmbientLight();
	vec3::clamp(c, .0f, 1.0f);

	return c;
}