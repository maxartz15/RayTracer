#include "Scene.h"
#include <iostream>

Scene::Scene(Camera& camera, unsigned int maxDepth, unsigned int samples, unsigned int subSamples) :
	m_camera(camera),
	m_maxDepth(maxDepth),
	m_samples(samples),
	m_subSamples(subSamples)
{
	m_backgroundColor = vec3(0.84f, 0.91f, 0.93f);
	m_ambientLight = vec3(0.81f, 0.87f, 1.0f);
	m_ambientLightIntensity = 0.1f;
	m_tMin = 0.001f;
	m_tMax = INFINITY;
}

Scene::~Scene()
{
}

const Camera& Scene::GetCamera() const
{
	return m_camera;
}

void Scene::SetCamera(Camera& camera)
{
	m_camera = camera;
}

const float Scene::GetAmbientLightIntensity() const
{
	return m_ambientLightIntensity;
}

const vec3 Scene::GetAmbientLight() const
{
	return (m_ambientLight * m_ambientLightIntensity);
}

void Scene::SetAmbientLight(vec3 color, float intensity)
{
	m_ambientLight = color;
	m_ambientLightIntensity = intensity;
}

const vec3& Scene::GetBackgroundColor() const
{
	return m_backgroundColor;
}

void Scene::SetBackgroundColor(vec3 color)
{
	m_backgroundColor = color;
}

void Scene::SetTMin(float tMin)
{
	m_tMin = tMin;
}

void Scene::SetTMax(float tMax)
{
	m_tMax = tMax;
}

//bool Scene::Hit(const Ray& ray, float tMin, float tMax, HitInfo& info) const
//{
//	//This function is to check if we have hit the closest Hitable,
//	//this is used to know if we have to calculate the color of the object we are hitting.
//
//	HitInfo tempInfo;
//
//	bool hit = false;
//	float closest = tMax;
//
//	for (const Hitable* h : hitables)
//	{
//		if (h->Hit(ray, tMin, closest, tempInfo))
//		{
//			hit = true;
//			closest = tempInfo.t;
//			info = tempInfo;
//		}
//	}
//
//	return hit;
//}
