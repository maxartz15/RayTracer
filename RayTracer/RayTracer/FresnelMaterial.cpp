#include "FresnelMaterial.h"
#include "Tracers.h"

FresnelMaterial::FresnelMaterial(float power) :
	m_power(power)
{
}


FresnelMaterial::~FresnelMaterial()
{
}

vec3 FresnelMaterial::Color(const Ray& ray, const Scene& scene, HitInfo& info) const
{
	ray;

	vec3 c(1, 1, 1);
	float fresnel = Trace::Fresnel(scene, info, m_power, false);
	
	c *= fresnel;
	vec3::clamp(c, .0f, 1.0f);

	return c;
}
