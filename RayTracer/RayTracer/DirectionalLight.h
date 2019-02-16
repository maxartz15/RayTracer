#pragma once
#include "Light.h"

class DirectionalLight :
	public Light
{
public:
	DirectionalLight(vec3 position, vec3 color, float intensity, float size);
	virtual ~DirectionalLight();

	vec3 GetDirection(const HitInfo& info) const;
};