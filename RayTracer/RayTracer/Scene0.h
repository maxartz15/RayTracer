#pragma once
#include "Scene.h"
#include "Hitables.h"
#include "Lights.h"
#include "Materials.h"

class Scene0 :
	public Scene
{
public:
	Scene0(Camera& camera, unsigned int maxDepth = 128, unsigned int maxSamples = 1, unsigned int maxSubSamples = 1) :
		Scene(camera, maxDepth, maxSamples, maxSubSamples)
	{
		hitables.push_back(new Sphere(vec3(0, 0, 1), .5f, new PhongMaterial(vec3(.8f, .8f, .8f), 100.0f)));
		lights.push_back(new PointLight(vec3(3.0f, 3.0f, -3.0f), vec3(1.0f, 1.0f, 1.0f), 1.0f, 10.0f, .0f));
	};
	virtual ~Scene0() {};
};