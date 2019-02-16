#pragma once
#include "Light.h"

class PointLight :
	public Light
{
public:
	PointLight(vec3 position, vec3 color, float intensity, float range, float size);
	virtual ~PointLight();

	virtual vec3 GetDirection(const HitInfo& info) const;

private:

};