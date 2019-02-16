#pragma once
#include "Scene.h"
#include "Hitables.h"
#include "Lights.h"
#include "Materials.h"

class Scene3 :
	public Scene
{
public:
	Scene3(Camera& camera, unsigned int maxDepth = 128, unsigned int maxSamples = 1, unsigned int maxSubSamples = 1) :
		Scene(camera, maxDepth, maxSamples, maxSubSamples)
	{
		camera.SetLookFrom(vec3(0, 1.5f, -1));
		camera.SetLookAt(vec3(0, 0, .25f));

		hitables.push_back(new Plane(vec3(.0f, -1.0f, 0.0f), vec3(.0f, 1.0f, .0f), new CheckerBoardMaterial(vec3(1.0f, 1.0f, 1.0f), vec3(0.3f, 0.3f, 0.3f))));
		hitables.push_back(new Sphere(vec3(0.0f, 0.0f, 1.0f), 0.5f, new DiffuseMaterial(vec3(1.0f, 1.0f, 1.0f))));

		lights.push_back(new PointLight(vec3(-2.0f, 3.0f, 2.0f), vec3(1.0f, 1.0f, 1.0f), 1.0f, 10.0f, 0.1f));

	};
	virtual ~Scene3() {};
};