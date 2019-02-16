#pragma once
#include "Material.h"

class RefractiveMaterial :
	public Material
{
public:
	RefractiveMaterial(float refractionIndex, float roughness);
	virtual ~RefractiveMaterial();

	virtual vec3 Color(const Ray& ray, const Scene& scene, HitInfo& info) const;
private:
	float m_refractionIndex;
	float m_roughness;
};