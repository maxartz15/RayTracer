#pragma once
#include <MathLibrary.h>
#include "Ray.h"

class Camera
{
public:
	Camera(float fov, float aspect, vec3 lookFrom, vec3 lookAt, vec3 vup);
	~Camera();

	void SetCamera(float fov, float aspect, vec3 lookFrom, vec3 lookAt, vec3 vup);
	void SetFov(float fov);
	void SetAspect(float aspect);
	void SetLookFrom(vec3 lookFrom);
	void SetLookAt(vec3 lookAt);
	void SetVup(vec3 vup);

	Ray GetRay(float u, float v) const;
	const vec3& GetPosition() const;
	const vec3& GetLookFrom() const;
	const vec3& GetLookAt() const;

private:
	vec3 m_lowerLeftCorner;
	vec3 m_horizontal;
	vec3 m_vertical;
	vec3 m_origin;

	//Inserted data.
	float m_fov;
	float m_aspect;
	vec3 m_lookFrom;
	vec3 m_lookAt;
	vec3 m_vup;
};
