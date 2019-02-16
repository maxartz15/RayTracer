#pragma once
#include "Material.h"

class NormalMaterial :
	public Material
{
public:
	NormalMaterial();
	virtual ~NormalMaterial();

	virtual vec3 Color(const Ray& ray, const Scene& scene, HitInfo& info) const;
};
