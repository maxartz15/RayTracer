#pragma once
#include "Material.h"

class CheckerBoardMaterial :
	public Material
{
public:
	CheckerBoardMaterial(vec3 color, vec3 secondColor);
	virtual ~CheckerBoardMaterial();

	virtual vec3 Color(const Ray& ray, const Scene& scene, HitInfo& info) const;

private:
	vec3 m_color;
	vec3 m_secondColor;
};