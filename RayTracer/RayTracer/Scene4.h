#pragma once
#include "Scene.h"
#include "Hitables.h"
#include "Lights.h"
#include "Materials.h"
#include "Acceleration.h"

class Scene4 :
	public Scene
{
public:
	Scene4(Camera& camera, unsigned int maxDepth = 128, unsigned int maxSamples = 1, unsigned int maxSubSamples = 1) :
		Scene(camera, maxDepth, maxSamples, maxSubSamples)
	{
		m_camera.SetLookAt(vec3(2.5f, 1, 0));
		m_camera.SetLookFrom(vec3(2.5f, 1, -3.0f));

		hitables.push_back(new Plane(vec3(.0f, -1.0f, 0.0f), vec3(.0f, 1.0f, .0f), new CheckerBoardMaterial(vec3(.0f, .0f, .0f), vec3(1.f, 1.0f, 1.0f))));
		hitables.push_back(new Plane(vec3(.0f, 0.0f, 5.0f), vec3(.0f, .0f, -1.0f), new CheckerBoardMaterial(vec3(.0f, .0f, .0f), vec3(1.f, 1.0f, 1.0f))));
		hitables.push_back(new Plane(vec3(-5.0f, 0.0f, 0.0f), vec3(1.0f, .0f, .0f), new CheckerBoardMaterial(vec3(.0f, .0f, .0f), vec3(1.f, 1.0f, 1.0f))));

		hitables.push_back(new Sphere(vec3(0, 1, 0), .5f, new NormalMaterial()));

		hitables.push_back(new Sphere(vec3(1.1f, .4f, 0), .5f, new ReflectiveMaterial(vec3(.9f, .9f, .9f), 0.0f, 275.0f)));
		hitables.push_back(new Sphere(vec3(1.1f, 1.6f, 0), .5f, new ReflectiveMaterial(vec3(.9f, .9f, .9f), 0.3f, 25.0f)));

		hitables.push_back(new Sphere(vec3(2.2f, 1, 0), .5f, new PhongMaterial(vec3(.9f, .9f, .9f), 250.0f)));

		hitables.push_back(new Sphere(vec3(3.3f, 1, 0), .5f, new DiffuseMaterial(vec3(.9f, .9f, .9f))));

		hitables.push_back(new Sphere(vec3(4.4f, .4f, 0), .5f, new RefractiveMaterial(1.1f, 0)));
		hitables.push_back(new Sphere(vec3(4.4f, 1.6f, 0), .5f, new RefractiveMaterial(1.3f, 0.3f)));

		hitables.push_back(new Sphere(vec3(5.5f, 1, 0), .5f, new FresnelMaterial(2.5f)));

		lights.push_back(new DirectionalLight(vec3(1.5f, 3.0f, -3.0f), vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.01f));
	};
	virtual ~Scene4() {};
};