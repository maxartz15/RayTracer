#pragma once
#include <MathLibrary.h>
#include <vector>

class Ray;
class Hitable;
class Scene;
class Material;
struct HitInfo;

namespace Trace
{
	bool Trace(const Ray& ray, const Scene& scene, HitInfo& info, float tMin, float tMax);
	bool Trace(const Ray& ray, const Scene& scene, HitInfo& info, float tMin, float tMax, const std::vector<Hitable*> hitables);
	vec3 Color(const Ray& ray, const Scene& scene, HitInfo& info);
	float Shadow(const Scene& scene, HitInfo& info);
	vec3 Diffuse(const Scene& scene, const HitInfo& info);
	vec3 Specular(const Ray& ray, const Scene& scene, const HitInfo& info, float shininess);
	vec3 Reflection(const Ray& ray, const Scene& scene, HitInfo& info, float reflectiveness);
	vec3 Refraction(const Ray& ray, const Scene& scene, HitInfo& info, float refractionIndex);
	float Fresnel(const Scene& scene, HitInfo& info, float power, bool inverted);
}