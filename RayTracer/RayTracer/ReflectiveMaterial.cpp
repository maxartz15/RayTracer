#include "ReflectiveMaterial.h"
#include "Tracers.h"

ReflectiveMaterial::ReflectiveMaterial(vec3 color, float roughness, float shininess) :
	m_color(color),
	m_roughness(roughness),
	m_shininess(shininess)
{
}


ReflectiveMaterial::~ReflectiveMaterial()
{
}

vec3 ReflectiveMaterial::Color(const Ray & ray, const Scene & scene, HitInfo & info) const
{
	vec3 c;
	vec3 specular = Trace::Specular(ray, scene, info, m_shininess);
	vec3 reflection = Trace::Reflection(ray, scene, info, m_roughness);
	
	//TODO: Shadow on reflective surfaces are different? When there is a reflection amount it could be the 1-amount * shadow for the intensity.
	float shadow = Trace::Shadow(scene, info);
	shadow = 1.0f;

	c = m_color * ((specular * (1 - m_roughness)) + reflection) * shadow + scene.GetAmbientLight();
	vec3::clamp(c, .0f, 1.0f);

	return c;
}