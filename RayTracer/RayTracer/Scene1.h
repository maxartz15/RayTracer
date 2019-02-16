#pragma once
#include "Scene.h"
#include "Hitables.h"
#include "Lights.h"
#include "Materials.h"

class Scene1 :
	public Scene
{
public:
	Scene1(Camera& camera, unsigned int maxDepth = 128, unsigned int maxSamples = 1, unsigned int maxSubSamples = 1) :
		Scene(camera, maxDepth, maxSamples, maxSubSamples)
	{
		hitables.push_back(new Sphere(vec3(0, 0, 1), .5f, new PhongMaterial(vec3(.8f, .8f, .8f), 100.0f)));
		hitables.push_back(new Sphere(vec3(3, 1, 3), .5f, new PhongMaterial(vec3(.8f, .8f, .8f), 100.0f)));
		hitables.push_back(new Sphere(vec3(-2, 1.5f, 2), .5f, new PhongMaterial(vec3(.8f, .8f, .8f), 100.0f)));
		hitables.push_back(new Sphere(vec3(1, .5f, 1.5f), .5f, new PhongMaterial(vec3(.8f, .8f, .8f), 100.0f)));

		//hitables.push_back(new Plane(vec3(.0f, -1.0f, 0.0f), vec3(.0f, 1.0f, .0f), *new PhongMaterial(vec3(.8f, .8f, .8f), 100.0f)));
		hitables.push_back(new Plane(vec3(.0f, -1.0f, 0.0f), vec3(.0f, 1.0f, .0f), new CheckerBoardMaterial(vec3(.0f, .0f, .0f), vec3(1.f, 1.0f, 1.0f))));
		hitables.push_back(new Plane(vec3(.0f, .0f, 5.0f), vec3(.0f, .0f, -1.0f), new PhongMaterial(vec3(.8f, .8f, .8f), 100.0f)));
		hitables.push_back(new Plane(vec3(-5.0f, .0f, 0.0f), vec3(1.0f, .0f, .0f), new ReflectiveMaterial(vec3(.8f, .8f, .8f), 0.f, 255.0f)));
		hitables.push_back(new Plane(vec3(5.0f, .0f, 0.0f), vec3(-1.0f, .0f, .0f), new ReflectiveMaterial(vec3(.8f, .8f, .8f), 0.f, 255.0f)));

		lights.push_back(new PointLight(vec3(3.0f, 3.0f, 1.0f), vec3(1.0f, .0f, .0f), 1.0f, 10.0f, .0f));
		lights.push_back(new PointLight(vec3(-3.0f, 3.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f), 1.0f, 10.0f, .0f));
		lights.push_back(new PointLight(vec3(0.0f, 3.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f), 1.0f, 10.0f, .0f));
	};
	virtual ~Scene1() {};
};