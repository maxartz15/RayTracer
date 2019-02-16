#pragma once
#include "AccelerationStructure.h"

class Sphere;
class Scene;

class SphereStructure :
	public AccelerationStructure
{
public:
	SphereStructure(Scene& scene, vec3 center, float radius);
	virtual ~SphereStructure();

	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitInfo& info) const override;
	virtual void AddHitable(Hitable& hitable) override;
	virtual void ReserveHitables(unsigned int amount);

	vec3 m_center;
	float m_radius;
private:
	Scene& m_scene;
	Sphere* m_sphere;

};

