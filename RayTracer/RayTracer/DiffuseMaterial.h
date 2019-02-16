#pragma once
#include "Material.h"

class DiffuseMaterial :
	public Material
{
public:
	DiffuseMaterial(vec3 color);
	virtual ~DiffuseMaterial();

	virtual vec3 Color(const Ray& ray, const Scene& scene, HitInfo& info) const;

private:
	vec3 m_color;
};

