#pragma once
#include "Hitable.h"

struct BoundingBox
{
	vec3 min;
	vec3 max;
};

class Shape :
	public Hitable
{
public:
	Shape() {};
	virtual ~Shape() {};

	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitInfo& info) const = 0;
	virtual const BoundingBox& GetBoundingBox() = 0;

protected:
	BoundingBox m_boundingBox;
	bool m_calculated = false;
};