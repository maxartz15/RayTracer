#include "NormalMaterial.h"

NormalMaterial::NormalMaterial()
{
}

NormalMaterial::~NormalMaterial()
{
}

vec3 NormalMaterial::Color(const Ray & ray, const Scene & scene, HitInfo & info) const
{
	ray;
	scene;

	return 0.5f * vec3(info.normal.x + 1, info.normal.y + 1, info.normal.z + 1);
}