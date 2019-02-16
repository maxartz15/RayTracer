#pragma once
#include "Material.h"

class PhongMaterial :
	public Material
{
public:
	PhongMaterial(vec3 color, float shininess);
	virtual ~PhongMaterial();

	virtual vec3 Color(const Ray& ray, const Scene& scene, HitInfo& info) const;

private:
	vec3 m_color;
	float m_shininess;
};