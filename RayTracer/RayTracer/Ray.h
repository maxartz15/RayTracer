#pragma once
#include <MathLibrary.h>

class Ray
{
public:
	Ray(const vec3& origin, const vec3& direction);
	~Ray();

	vec3 origin() const;
	vec3 direction() const;
	vec3 point(float t) const;

private:
	vec3 m_origin;
	vec3 m_direction;
};