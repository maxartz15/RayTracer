#pragma once
#include <MathLibrary.h>
#include "Ray.h"
#include "Hitable.h"
#include "Scene.h"

class Material
{
public:
	virtual vec3 Color(const Ray& ray, const Scene& scene, HitInfo& info) const = 0;
};