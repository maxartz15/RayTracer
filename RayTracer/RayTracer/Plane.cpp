#include "Plane.h"

Plane::Plane(vec3 center, vec3 normal, Material* material) :
	m_center(center),
	m_normal(normal),
	m_pMaterial(material)
{
}

Plane::~Plane()
{
}

bool Plane::Hit(const Ray & ray, float tMin, float tMax, HitInfo & info) const
{
	//Ref: https://docs.google.com/document/d/12m5C-Fp3xP_zohZyFc-RsvFBmUFEuJR1rkjaHqLb_Z4/edit#heading=h.19xrfrccrdjd

	//If the dot product of the normal and the ray == 0 the line and point will never intersect.
	//if (vec3::dot(ray.direction(), m_normal) < .0f)
	//{
	//	float t = vec3::dot(vec3::normalized(ray.origin() - m_center), m_normal) / vec3::dot(ray.direction(), m_normal);

	//	if (/*t >= 0 && t <= 1 && */t < tMax && t > tMin)
	//	{
	//		info.t = t;
	//		info.p = ray.point(info.t);
	//		info.normal = m_normal;
	//		info.pMaterial = m_pMaterial;

	//		return true;
	//	}
	//}

	if (vec3::dot(ray.direction(), m_normal) < .0f)
	{
		vec3 v1 = vec3::project(ray.direction(), m_normal);
		vec3 v2 = ray.origin() - m_center;
		vec3 v3 = vec3::project(v2, m_normal);
		float t = v3.length() / v1.length();

		if (t < tMax && t > tMin)
		{
			info.t = t;
			info.p = ray.point(info.t);
			info.normal = m_normal;
			info.pMaterial = m_pMaterial;

			return true;
		}
	}

	return false;
}