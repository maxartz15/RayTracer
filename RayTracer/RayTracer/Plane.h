#pragma once
#include "Hitable.h"

class Material;

class Plane :
	public Hitable
{
public:
	Plane(vec3 center, vec3 normal, Material* material);
	virtual ~Plane();

	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitInfo& info) const override;

private:
	vec3 m_normal;
	vec3 m_center;

	Material* m_pMaterial = nullptr;
};

