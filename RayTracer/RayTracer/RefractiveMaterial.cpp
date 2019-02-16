#include "RefractiveMaterial.h"
#include "Tracers.h"

RefractiveMaterial::RefractiveMaterial(float refractionIndex, float roughness) :
	m_refractionIndex(refractionIndex),
	m_roughness(roughness)
{
}

RefractiveMaterial::~RefractiveMaterial()
{
}

vec3 RefractiveMaterial::Color(const Ray & ray, const Scene & scene, HitInfo & info) const
{
	vec3 c;
	vec3 specular = Trace::Specular(ray, scene, info, 250.0f);
	vec3 refraction = Trace::Refraction(ray, scene, info, m_refractionIndex);

	float shadow = Trace::Shadow(scene, info);

	c = (specular + refraction) * shadow + scene.GetAmbientLight();
	vec3::clamp(c, .0f, 1.0f);

	return c;
}
