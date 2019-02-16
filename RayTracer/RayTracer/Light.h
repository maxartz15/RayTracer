#pragma once
#include <MathLibrary.h>
#include "Hitable.h"

class Light
{
public:
	Light(vec3 position, vec3 color, float intensity, float range, float size);
	virtual ~Light();

	virtual vec3 GetDirection(const HitInfo& info) const = 0;

	vec3 m_position;
	vec3 m_color;
	float m_intensity;
	float m_range;
	float m_size;
};