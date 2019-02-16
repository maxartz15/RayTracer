#pragma once
#include "Hitable.h"

class Material;

class Sphere :
	public Hitable
{
public:
	Sphere(vec3 center, float radius, Material* material);
	virtual ~Sphere();

	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitInfo& info) const override;

private:
	vec3 Normal(const vec3& p) const;

	vec3 m_center;
	float m_radius;
	Material* m_pMaterial = nullptr;
};