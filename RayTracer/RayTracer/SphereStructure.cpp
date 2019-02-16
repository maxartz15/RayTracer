#include "SphereStructure.h"
#include "Sphere.h"
#include "Hitable.h"
#include "Tracers.h"
#include "Scene.h"

SphereStructure::SphereStructure(Scene& scene, vec3 center, float radius) :
	m_scene(scene),
	m_center(center),
	m_radius(radius)
{
	m_sphere = new Sphere(m_center, m_radius, nullptr);
}

SphereStructure::~SphereStructure()
{
}

bool SphereStructure::Hit(const Ray & ray, float tMin, float tMax, HitInfo & info) const
{
	HitInfo tempInfo;
	tempInfo.curDepth = info.curDepth;

	if (m_sphere->Hit(ray, tMin, tMax, tempInfo))
	{
		//We hit this sphere, now check for the hitables inside.

		tempInfo = HitInfo();
		tempInfo.curDepth = info.curDepth;

		if (Trace::Trace(ray, m_scene, tempInfo, tMin, tMax, m_hitables))
		{
			info = tempInfo;

			//We hit a hitable in the sphere.
			return true;
		}
	}

	//We didn't hit any of our hitables.
	return false;
}

void SphereStructure::AddHitable(Hitable& hitable)
{
	m_hitables.push_back(&hitable);
}

void SphereStructure::ReserveHitables(unsigned int amount)
{
	m_hitables.reserve(amount);
}
