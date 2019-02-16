#include "Tracers.h"

#include <algorithm>

#include "Ray.h"
#include "Hitable.h"
#include "Scene.h"
#include "Material.h"

#include "Acceleration.h"
#include "Statistics.h"

bool Trace::Trace(const Ray& ray, const Scene& scene, HitInfo& info, float tMin, float tMax)
{
	return Trace::Trace(ray, scene, info, tMin, tMax, scene.hitables);

#pragma region old
	//HitInfo tempInfo;
	//tempInfo.curDepth = info.curDepth;

	//bool hit = false;
	//float closest = tMax;

	//if (info.curDepth < scene.GetMaxDepth())
	//{
	//	for (const Hitable* h : scene.hitables)
	//	{
	//		Statistics::increaseTraces();

	//		if (h->Hit(ray, tMin, closest, tempInfo))
	//		{
	//			Statistics::increaseHits();

	//			hit = true;
	//			closest = tempInfo.t;
	//			info = tempInfo;
	//		}
	//	}
	//	info.curDepth++;
	//}

	//return hit;
#pragma endregion
}

bool Trace::Trace(const Ray& ray, const Scene& scene, HitInfo& info, float tMin, float tMax, const std::vector<Hitable*> hitables)
{
	HitInfo tempInfo;
	tempInfo.curDepth = info.curDepth;

	bool hit = false;
	float closest = tMax;

	if (info.curDepth < scene.GetMaxDepth())
	{
		for (const Hitable* h : hitables)
		{
			Statistics::increaseTraces();

			if (h->Hit(ray, tMin, closest, tempInfo))
			{
				Statistics::increaseHits();

				hit = true;
				closest = tempInfo.t;
				info = tempInfo;
			}
		}
		info.curDepth++;
	}

	return hit;
}

vec3 Trace::Color(const Ray& ray, const Scene& scene, HitInfo& info)
{
	HitInfo tempInfo;
	tempInfo.curDepth = info.curDepth;

	if (Trace::Trace(ray, scene, tempInfo, scene.GetTMin(), scene.GetTMax()))
	{
		info = tempInfo;
		if (tempInfo.pMaterial != nullptr)
		{
			//TODO: Calculate the color here instead of inside the material.
			//This could also be done in a seperate function, this way I could still have different lighting models.
			return info.pMaterial->Color(ray, scene, info);
		}
	}
	
	//If we haven't hit anything.
	return scene.GetBackgroundColor();
}

float Trace::Shadow(const Scene& scene, HitInfo& info)
{
	float shadow = 0;
	unsigned int ss = scene.GetSubSamples();

	for (unsigned int s = 0; s < ss; ++s)
	{
		Statistics::increaseColorCalculations();

		for (const Light* l : scene.lights)
		{
			//Create cur depth in here to avoid reaching max depth for a shadow.
			HitInfo tempInfo;
			tempInfo.curDepth = info.curDepth;

			//New dir with random offset based on the shadow softness.
			vec3 dir = l->GetDirection(info);
			if (l->m_size > 0.0f)
			{
				dir = (dir + vec3::randomPointInUnitSphere2() * l->m_size).normalized();
			}

			//Using max distance to avoid hitting things behind the light.
			float maxDistance = vec3::distance(info.p, l->m_position);

			Ray shadowRay = Ray(info.p, dir);

			if (Trace::Trace(shadowRay, scene, tempInfo, scene.GetTMin(), maxDistance))
			{
				shadow++;
			}
		}
	}

	shadow = std::clamp(1 - (shadow / (scene.lights.size() * ss)), .0f, 1.0f);

	return shadow;

	//TODO: Maybe add a shadow strength property, just multiply it then with the resulting value.
}

vec3 Trace::Diffuse(const Scene& scene, const HitInfo& info)
{
	Statistics::increaseColorCalculations();

	vec3 c;

	for (const Light* l : scene.lights)
	{
		float dis = vec3::distance(info.p, l->m_position);
		float falloff = 1 - (dis / l->m_range);

		c += (l->m_intensity * l->m_color * std::max(vec3::dot(info.normal, l->GetDirection(info)), .0f) * falloff);
	}

	vec3::clamp(c, .0f, 1.0f);

	return c;
}

vec3 Trace::Specular(const Ray& ray, const Scene& scene, const HitInfo& info, float shininess)
{
	Statistics::increaseColorCalculations();

	vec3 c;
	float spec = .0f;

	for (const Light* l : scene.lights)
	{
		vec3 o = ray.origin(); //Based on ray origin instead of camera origin because when bounces are made we need the spec from that position.
		vec3 lr = vec3::reflect(l->GetDirection(info), info.normal);
		float d = std::max(vec3::dot((o - info.p).normalized(), lr), .0f);
		spec += std::powf(d, shininess);
		c += l->m_color * d;
	}

	c = c * spec;
	vec3::clamp(c, .0f, 1.0f);

	return c;
}

vec3 Trace::Reflection(const Ray& ray, const Scene& scene, HitInfo& info, float roughness)
{
	vec3 c;

	vec3 dir = vec3::reflect(ray.direction().inversed(), info.normal).normalize();

	//Do we need more than one sample?
	unsigned int ss = 1;
	if (roughness > 0.0f)
	{
		ss = scene.GetSubSamples();
	}

	for (unsigned int s = 0; s < ss; ++s)
	{
		Statistics::increaseColorCalculations();

		//Create cur depth in here to reset max depth for each reflection.
		HitInfo tempInfo;
		tempInfo.curDepth = info.curDepth;

		//New ray with random direction based in the roughness.
		if (roughness > 0.0f)
		{
			dir = (dir + vec3::randomPointInUnitSphere2() * roughness).normalized();
		}

		Ray r = Ray(info.p, dir);

		//To keep track of if the ray has hit something that returns a color.
		bool color = false;

		if (Trace::Trace(r, scene, tempInfo, scene.GetTMin(), scene.GetTMax()))
		{
			//info = tempInfo;
			if (tempInfo.pMaterial != nullptr)
			{
				c += tempInfo.pMaterial->Color(r, scene, tempInfo);
				color = true;
			}
		}

		if (!color)
		{
			c += scene.GetBackgroundColor();
		}
	}

	return (c /= static_cast<float>(ss));
}

vec3 Trace::Refraction(const Ray & ray, const Scene & scene, HitInfo & info, float refractionIndex)
{
	Statistics::increaseColorCalculations();

	HitInfo tempInfo;
	tempInfo.curDepth = info.curDepth;

	//vec3 dir = vec3::refract(ray.direction(), info.normal, refractionIndex).normalized();
	//vec3 dir = vec3::refract2(ray.direction(), info.normal, refractionIndex).normalized();
	//vec3 dir = vec3::refract3(ray.direction(), info.normal, 1.0f, refractionIndex).normalized();
	vec3 dir = vec3::refract4(ray.direction(), info.normal, refractionIndex).normalized();

	Ray r = Ray(info.p, dir);

	if (Trace::Trace(r, scene, tempInfo, scene.GetTMin(), scene.GetTMax()))
	{
		info = tempInfo;
		if (info.pMaterial != nullptr)
		{
			return info.pMaterial->Color(r, scene, info);
		}
	}

	return scene.GetBackgroundColor();

	//TODO: look at reflection and refraction combined, how much does reflect and how much does refract.
}

float Trace::Fresnel(const Scene& scene, HitInfo& info, float power, bool inverted = false)
{
	Statistics::increaseColorCalculations();

	vec3 o = (scene.GetCamera().GetPosition() - info.p).normalized();

	float c = std::max(vec3::dot(info.normal, o), .0f);

	if (!inverted)
		c = 1 - c;

	c = std::powf(c, power);

	return c;
}