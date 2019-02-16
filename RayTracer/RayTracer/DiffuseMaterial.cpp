#include "DiffuseMaterial.h"
#include "Tracers.h"

DiffuseMaterial::DiffuseMaterial(vec3 color) :
	m_color(color)
{
}


DiffuseMaterial::~DiffuseMaterial()
{
}

vec3 DiffuseMaterial::Color(const Ray& ray, const Scene& scene, HitInfo& info) const
{
	ray;

	vec3 diffuse = Trace::Diffuse(scene, info);
	float shadow = Trace::Shadow(scene, info);

	vec3 c = m_color * (diffuse) * shadow + scene.GetAmbientLight();
	vec3::clamp(c, .0f, 1.0f);

	return c;
}