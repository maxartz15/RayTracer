#include "Sphere.h"

Sphere::Sphere(vec3 center, float radius, Material* material) :
	m_center(center),
	m_radius(radius),
	m_pMaterial(material)
{
}

Sphere::~Sphere()
{
}

bool Sphere::Hit(const Ray& ray, float tMin, float tMax, HitInfo& info) const
{
	//Ref: https://docs.google.com/document/d/12m5C-Fp3xP_zohZyFc-RsvFBmUFEuJR1rkjaHqLb_Z4/edit#heading=h.w7zjcmpnu6lf Sphere Intersection

	float t = vec3::dot((m_center - ray.origin()), ray.direction());
	vec3 p = ray.origin() + ray.direction() * t;
	float y = vec3::length(m_center - p);

	//Only if the ray is smaller we did hit the sphere else we didn't.
	//And if the sqrt of a negative y is undefined so it won't work.
	if (y < m_radius)
	{
		float x = sqrtf(m_radius * m_radius - y * y);
		
		//Intersection 1
		float t1 = t - x;
		if (t1 < tMax && t1 > tMin)
		{
			info.t = t1;
			info.p = ray.point(info.t);
			info.normal = Normal(info.p);
			info.pMaterial = m_pMaterial;

			return true;
		}

		//If intersection 1 didn't work out check for the second one.
		//Intersection 2
		//float t2 = t + x;
		//if (t2 < tMax && t2 > tMin)
		//{
		//	info.t = t2;
		//	info.p = ray.point(info.t);
		//	info.normal = Normal(info.p);
		//	info.pMaterial = m_pMaterial;

		//	return true;
		//}
	}

	return false;
}

vec3 Sphere::Normal(const vec3& p) const
{
	//Ref: https://docs.google.com/document/d/12m5C-Fp3xP_zohZyFc-RsvFBmUFEuJR1rkjaHqLb_Z4/edit#heading=h.mp2omxmr1ruh Sphere Normal

	return (p - m_center).normalized();
}