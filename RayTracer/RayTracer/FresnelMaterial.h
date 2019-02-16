#pragma once
#include "Material.h"
class FresnelMaterial :
	public Material
{
public:
	FresnelMaterial(float power);
	virtual ~FresnelMaterial();

	virtual vec3 Color(const Ray& ray, const Scene& scene, HitInfo& info) const;

private:
	float m_power;
};

