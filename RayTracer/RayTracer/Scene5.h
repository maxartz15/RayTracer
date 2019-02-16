#pragma once
#include "Scene.h"
#include "Hitables.h"
#include "Lights.h"
#include "Materials.h"
#include "Acceleration.h"

class Scene5 :
	public Scene
{
public:
	Scene5(Camera& camera, unsigned int maxDepth = 128, unsigned int maxSamples = 1, unsigned int maxSubSamples = 1) :
		Scene(camera, maxDepth, maxSamples, maxSubSamples)
	{
		camera.SetLookFrom(vec3(0, 0, -125));

		int _maxDepth = 5;
		int _size = 10;
		float _radiusDivider = 0.35f; // https://en.wikipedia.org/wiki/Sphere_packing_in_a_sphere
		float _radius = 100;
		unsigned int _c = 0;

		std::vector<SphereStructure*> _s;
		_s.push_back(new SphereStructure(*this, vec3(0, 0, 0), _radius));
		hitables.push_back(_s[0]);
		StructureInStructure(_maxDepth, _size, _radius, _radiusDivider, _s, *this, _c);
		std::cout << _c << std::endl;

		lights.push_back(new DirectionalLight(vec3(3.0f, 3.0f, -1.0f), vec3(1.0f, 1.0f, 1.0f), 1.0f, .0f));
	};
	virtual ~Scene5() {};

private:
	void StructureInStructure(int depth, int size, float sphereSize, float sizeDivider, std::vector<SphereStructure*> s, Scene& scene, unsigned int& count);
};

void Scene5::StructureInStructure(int depth, int size, float radius, float radiusDivider, std::vector<SphereStructure*> s, Scene& scene, unsigned int& count)
{
	std::vector<SphereStructure*> _lastS;
	radius *= radiusDivider;

	if (depth == 0)
	{
		for (SphereStructure* ss : s)
		{
			ss->ReserveHitables(size);
			ss->AddHitable(*new Sphere(ss->m_center, radius, new DiffuseMaterial(vec3(0, 0, 0)))); //yeah yeah.. this isn't so memory efficent...
			count++;

			Material* m = new DiffuseMaterial(vec3::random01());
			for (int i = 0; i < size - 1; i++)
			{
				ss->AddHitable(*new Sphere(ss->m_center + ((vec3::randomPointInUnitSphere() - vec3::randomPointInUnitSphere()) * (ss->m_radius * radiusDivider)), radius * 0.5f, m));
				count++;
			}
		}
	}
	else
	{
		for (SphereStructure* ss : s)
		{
			ss->ReserveHitables(size);
			for (int i = 0; i < size; i++)
			{
				SphereStructure* nss = new SphereStructure(scene, ss->m_center + ((vec3::randomPointInUnitSphere() - vec3::randomPointInUnitSphere()) * (ss->m_radius * radiusDivider)), radius);
				ss->AddHitable(*nss);
				_lastS.push_back(nss);
			}
		}
	}

	if (depth > 0)
	{
		StructureInStructure(depth - 1, size, radius, radiusDivider, _lastS, scene, count);
	}

	//for (int i = depth; i > 0; i--)
	//{
	//	StructureInStructure(depth - 1, size, radius, radiusDivider, _lastS, scene, count);
	//}
}