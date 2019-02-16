#include "CheckerBoardMaterial.h"
#include "Tracers.h"

CheckerBoardMaterial::CheckerBoardMaterial(vec3 color, vec3 secondColor) :
	m_color(color),
	m_secondColor(secondColor)
{
}


CheckerBoardMaterial::~CheckerBoardMaterial()
{
}

vec3 CheckerBoardMaterial::Color(const Ray& ray, const Scene& scene, HitInfo& info) const
{
	ray;

	vec3 c;
	vec3 color = vec3(1.0f, 1.0f, 1.0f);

	float gridSize = 1.0;

	int gridPositionX = static_cast<int>(round(info.p.x / gridSize));
	int gridPositionY = static_cast<int>(round(info.p.y / gridSize));
	int gridPositionZ = static_cast<int>(round(info.p.z / gridSize));

	int grid = gridPositionX + gridPositionY + gridPositionZ;
	color = (grid % 2 == 0) ? m_color : m_secondColor;

	vec3 diffuse = Trace::Diffuse(scene, info);
	float shadow = Trace::Shadow(scene, info);

	c = color * (diffuse) * shadow + scene.GetAmbientLight();
	vec3::clamp(c, .0f, 1.0f);

	return c;
}