#pragma once
#include "Material.h"
class ReflectiveMaterial :
	public Material
{
public:
	ReflectiveMaterial(vec3 color, float roughness, float shininess);
	virtual ~ReflectiveMaterial();

	virtual vec3 Color(const Ray& ray, const Scene& scene, HitInfo& info) const;
private:
	vec3 m_color;
	float m_roughness;
	float m_shininess;
};

