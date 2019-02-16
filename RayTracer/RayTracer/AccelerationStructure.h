#pragma once
#include "Hitable.h"
#include <vector>

class AccelerationStructure :
	public Hitable
{
public:
	AccelerationStructure() {};
	virtual ~AccelerationStructure() {};

	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitInfo& info) const = 0;
	virtual void AddHitable(Hitable& hitable) = 0;
	virtual void ReserveHitables(unsigned int amount) = 0;

protected:
	std::vector<Hitable*> m_hitables;
};