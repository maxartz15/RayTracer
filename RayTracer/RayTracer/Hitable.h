#pragma once
#include <MathLibrary.h>
#include "Ray.h"

class Material;

struct HitInfo
{
	unsigned int curDepth = 0;
	float t = 0;
	vec3 p;
	vec3 normal;
	Material* pMaterial = nullptr;
};

class Hitable
{
public:
	Hitable() {};
	virtual ~Hitable() {};

	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitInfo& info) const = 0;
};