#pragma once
#include "Shape.h"

class Material;

class SphereShape :
	public Shape
{
public:
	SphereShape(vec3 center, float radius, Material& material);
	virtual ~SphereShape();

	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitInfo& info) const override;
	virtual const BoundingBox& GetBoundingBox() override;

private:
	vec3 Normal(const vec3& p) const;

	vec3 m_center;
	float m_radius;
	Material* m_pMaterial;
};