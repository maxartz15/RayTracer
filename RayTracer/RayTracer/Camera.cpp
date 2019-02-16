#include "Camera.h"
#include "MathLibrary.h"

Camera::Camera(float fov, float aspect, vec3 lookFrom, vec3 lookAt, vec3 vup)
{
	SetCamera(fov, aspect, lookFrom, lookAt, vup);
}

Camera::~Camera()
{
}

void Camera::SetCamera(float fov, float aspect, vec3 lookFrom, vec3 lookAt, vec3 vup)
{
	m_fov = fov;
	m_aspect = aspect;
	m_lookFrom = lookFrom;
	m_lookAt = lookAt;
	m_vup = vup;

	vec3 u, v, w;

	float theta = fov * Math::PI / 180;
	float halfHeight = tan(theta / 2);
	float halfWidth = aspect * halfHeight;

	m_origin = lookFrom;
	w = vec3::normalized(lookFrom - lookAt);
	u = vec3::normalized(vec3::cross(vup, w));
	v = vec3::cross(w, u);

	m_lowerLeftCorner = m_origin - (halfWidth * u) - (halfHeight * v) - w;
	m_horizontal = 2.0f * halfWidth * u;
	m_vertical = 2.0f * halfHeight * v;
}

void Camera::SetFov(float fov)
{
	SetCamera(fov, m_aspect, m_lookFrom, m_lookAt, m_vup);
}

void Camera::SetAspect(float aspect)
{
	SetCamera(m_fov, aspect, m_lookFrom, m_lookAt, m_vup);
}

void Camera::SetLookFrom(vec3 lookFrom)
{
	SetCamera(m_fov, m_aspect, lookFrom, m_lookAt, m_vup);
}

void Camera::SetLookAt(vec3 lookAt)
{
	SetCamera(m_fov, m_aspect, m_lookFrom, lookAt, m_vup);
}

void Camera::SetVup(vec3 vup)
{
	SetCamera(m_fov, m_aspect, m_lookFrom, m_lookAt, vup);
}

Ray Camera::GetRay(float u, float v) const
{
	//return Ray(origin, (lower_left_corner + u * horizontal + v * vertical).normalized());
	return Ray(m_origin, (m_lowerLeftCorner + u * m_horizontal + v * m_vertical - m_origin).normalized());
}

const vec3& Camera::GetPosition() const
{
	return m_origin;
}

const vec3& Camera::GetLookFrom() const
{
	return m_lookFrom;
}

const vec3& Camera::GetLookAt() const
{
	return m_lookAt;
}
