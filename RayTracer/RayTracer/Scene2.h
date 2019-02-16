#pragma once
#include "Scene.h"
#include "Hitables.h"
#include "Lights.h"
#include "Materials.h"

class Scene2 :
	public Scene
{
public:
	Scene2(Camera& camera, unsigned int maxDepth = 128, unsigned int maxSamples = 1, unsigned int maxSubSamples = 1) :
		Scene(camera, maxDepth, maxSamples, maxSubSamples)
	{
		m_camera.SetLookAt(vec3(0, 0, 0));
		m_camera.SetLookFrom(vec3(-4, 0, -4));
		m_camera.SetFov(30);

		hitables.push_back(new Plane(vec3(.0f, -5.0f, 0.0f), vec3(.0f, 1.0f, .0f), new DiffuseMaterial(vec3(0.0f, 1.0f, 0.0f))));
		hitables.push_back(new Plane(vec3(.0f, .0f, 5.0f), vec3(.0f, .0f, -1.0f), new DiffuseMaterial(vec3(1.0f, 1.0f, 1.0f))));
		hitables.push_back(new Plane(vec3(5.0f, .0f, .0f), vec3(-1.0f, .0f, .0f), new DiffuseMaterial(vec3(1.0f, 1.0f, 1.0f))));
		hitables.push_back(new Plane(vec3(-5.0f, .0f, .0f), vec3(1.0f, .0f, 0.0f), new DiffuseMaterial(vec3(1.0f, 1.0f, 1.0f))));
		hitables.push_back(new Plane(vec3(.0f, .0f, -5.0f), vec3(.0f, .0f, 1.0f), new DiffuseMaterial(vec3(1.0f, 1.0f, 1.0f))));
		hitables.push_back(new Plane(vec3(.0f, 5.0f, 0.0f), vec3(.0f, -1.0f, .0f), new DiffuseMaterial(vec3(0.0f, 0.0f, 1.0f))));

		hitables.push_back(new Sphere(vec3(.9f, 0.0f, -.9f), 1.0f, new ReflectiveMaterial(vec3(1.f, 1.f, 1.f), 0.4f, 25.f)));
		hitables.push_back(new Sphere(vec3(-.9f, 0.0f, .9f), 1.0f, new ReflectiveMaterial(vec3(1.f, 1.f, 1.f), 0.0f, 250.f)));

		lights.push_back(new PointLight(vec3(3, 0, -3), vec3(1.0f, 1.0f, 1.0f), 1.0f, 10.0f, .025f));
		lights.push_back(new PointLight(vec3(-3, 0, 3), vec3(1.0f, 1.0f, 1.0f), 1.0f, 10.0f, .025f));

	};
	virtual ~Scene2() {};
};