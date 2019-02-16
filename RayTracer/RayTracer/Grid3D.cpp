#include "Grid3D.h"
#include "Hitable.h"
#include "Ray.h"
#include "Shape.h"

Grid3D::Grid3D(vec3 gridSize, unsigned int cellSize, vec3 gridOffset)
{
	m_cellSize = cellSize;
	m_gridOffset = gridOffset;

	m_xCells = static_cast<int>(gridSize.x / cellSize);
	m_yCells = static_cast<int>(gridSize.y / cellSize);
	m_zCells = static_cast<int>(gridSize.z / cellSize);

	for (int x = 0; x < m_xCells; ++x)
	{
		std::vector<std::vector<Cell3D*>> cy;
		for (int y = 0; y < m_yCells; ++y)
		{
			std::vector<Cell3D*> cz;
			for (int z = 0; z < m_zCells; ++z)
			{
				cz.push_back(new Cell3D(vec3(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z))));
			}
			cy.push_back(cz);
		}
		m_cells.push_back(cy);
	}
}

Grid3D::~Grid3D()
{
	for (const auto& x : m_cells)
	{
		for (const auto& y : x)
		{
			for (auto& c : y)
			{
				delete(c);
			}
		}
	}
}

void Grid3D::RegisterHitable(Shape* hitable)
{
	if (hitable != nullptr)
	{
		const BoundingBox& bb = hitable->GetBoundingBox();

		//Transform world pos into grid pos.
		vec3 gMin = WorldToGridPos(bb.min);
		vec3 gMax = WorldToGridPos(bb.max);

		//Find cells in between the min and max.
		int x = static_cast<int>(gMax.x - gMin.x);
		int y = static_cast<int>(gMax.y - gMin.y);
		int z = static_cast<int>(gMax.z - gMin.z);

		for (int i = 0; i <= x; ++i)
		{
			for (int j = 0; j <= y; ++j)
			{
				for (int k = 0; k <= z; ++k)
				{
					Cell3D* cell = GetCell(vec3(gMin.x + i, gMin.y + j, gMin.z + k), false);
					cell->hitables.push_back(hitable);
					cell->hasHitables = true;
				}
			}
		}
	}
}

Cell3D* Grid3D::GetCell(const vec3 gridPosition, bool markAsChecked)
{
	//Check gridPos
	if (gridPosition.x < 0 || gridPosition.x > m_xCells ||
		gridPosition.y < 0 || gridPosition.y > m_yCells ||
		gridPosition.z < 0 || gridPosition.z > m_zCells)
	{
		return nullptr;
	}

	//Find grid cell.
	Cell3D* c = m_cells[static_cast<unsigned int>(gridPosition.x)][static_cast<unsigned int>(gridPosition.y)][static_cast<unsigned int>(gridPosition.z)];

	//Mark grid cell as checked.
	//if (markAsChecked && c != nullptr)
	//{
	//	c->checked = true;
	//}

	markAsChecked;

	return c;
}

void Grid3D::ResetCellChecks()
{
	for (const auto& x : m_cells)
	{
		for (const auto& y : x)
		{
			for (auto& c : y)
			{
				c->checked = false;
			}
		}
	}
}

vec3 Grid3D::WorldToGridPos(const vec3& worldPos)
{
	return (vec3((worldPos + m_gridOffset) / static_cast<float>(m_cellSize))).floored();
}

vec3 Grid3D::GridToWorldPos(const vec3& GridPos)
{
	return vec3((GridPos * static_cast<float>(m_cellSize) - m_gridOffset));
}

bool Grid3D::RayGridIntersection(const Ray& ray, float tMin, float tMax, HitInfo& info)
{
	for (const auto& x : m_cells)
	{
		for (const auto& y : x)
		{
			for (auto& c : y)
			{
				if (c->hasHitables && !c->checked && CellIntersection(c->gridPos, ray, tMin, tMax, info))
				{
					c->checked = true;
					return true;
				}
			}
		}
	}
	return false;
}

bool Grid3D::CellIntersection(vec3 cellGridPos, const Ray& ray, float tMin, float tMax, HitInfo& info)
{
	vec3 cellwpos = GridToWorldPos(cellGridPos);
	float cellSize = static_cast<float>(m_cellSize);

	//Construct cube.
	//Intersection test w cube.

	//Front.
	vec3 normal(0, 0, -1);
	vec3 center(cellwpos + vec3(0, 0, cellSize));

	if (vec3::dot(ray.direction(), normal) < .0f)
	{
		vec3 v1 = vec3::project(ray.direction(), normal);
		vec3 v2 = ray.origin() - center;
		vec3 v3 = vec3::project(v2, normal);
		float t = v3.length() / v1.length();

		vec3 p = ray.point(t);
		if (p.x >= center.x && p.x <= center.x + cellSize &&
			p.y >= center.y && p.y >= center.y + cellSize)
		{
			if (t < tMax && t > tMin)
			{
				info.t = t;
				info.p = ray.point(t);
				return true;
			}
		}
	}

	//Back.
	normal = vec3(0, 0, 1);
	center = vec3(cellwpos);

	if (vec3::dot(ray.direction(), normal) < .0f)
	{
		vec3 v1 = vec3::project(ray.direction(), normal);
		vec3 v2 = ray.origin() - center;
		vec3 v3 = vec3::project(v2, normal);
		float t = v3.length() / v1.length();

		vec3 p = ray.point(t);
		if (p.x >= center.x && p.x <= center.x + cellSize &&
			p.y >= center.y && p.y >= center.y + cellSize)
		{
			if (t < tMax && t > tMin)
			{
				info.t = t;
				info.p = ray.point(t);
				return true;
			}
		}
	}

	//Top. 
	normal = vec3(0, -1, 0);
	center = vec3(cellwpos + vec3(0, cellSize, 0));

	if (vec3::dot(ray.direction(), normal) < .0f)
	{
		vec3 v1 = vec3::project(ray.direction(), normal);
		vec3 v2 = ray.origin() - center;
		vec3 v3 = vec3::project(v2, normal);
		float t = v3.length() / v1.length();

		vec3 p = ray.point(t);
		if (p.x >= center.x && p.x <= center.x + cellSize &&
			p.z >= center.z && p.z >= center.z + cellSize)
		{
			if (t < tMax && t > tMin)
			{
				info.t = t;
				info.p = ray.point(t);
				return true;
			}
		}
	}

	//Down. 
	normal = vec3(0, 1, 0);
	center = vec3(cellwpos);

	if (vec3::dot(ray.direction(), normal) < .0f)
	{
		vec3 v1 = vec3::project(ray.direction(), normal);
		vec3 v2 = ray.origin() - center;
		vec3 v3 = vec3::project(v2, normal);
		float t = v3.length() / v1.length();

		vec3 p = ray.point(t);
		if (p.x >= center.x && p.x <= center.x + cellSize &&
			p.z >= center.z && p.z >= center.z + cellSize)
		{
			if (t < tMax && t > tMin)
			{
				info.t = t;
				info.p = ray.point(t);
				return true;
			}
		}
	}

	//Right. 
	normal = vec3(-1, 0, 0);
	center = vec3(cellwpos + vec3(cellSize, 0, 0));

	if (vec3::dot(ray.direction(), normal) < .0f)
	{
		vec3 v1 = vec3::project(ray.direction(), normal);
		vec3 v2 = ray.origin() - center;
		vec3 v3 = vec3::project(v2, normal);
		float t = v3.length() / v1.length();

		vec3 p = ray.point(t);
		if (p.y >= center.y && p.y <= center.y + cellSize &&
			p.z >= center.z && p.z >= center.z + cellSize)
		{
			if (t < tMax && t > tMin)
			{
				info.t = t;
				info.p = ray.point(t);
				return true;
			}
		}
	}

	//Left. 
	normal = vec3(1, 0, 0);
	center = vec3(cellwpos);

	if (vec3::dot(ray.direction(), normal) < .0f)
	{
		vec3 v1 = vec3::project(ray.direction(), normal);
		vec3 v2 = ray.origin() - center;
		vec3 v3 = vec3::project(v2, normal);
		float t = v3.length() / v1.length();

		vec3 p = ray.point(t);
		if (p.y >= center.y && p.y <= center.y + cellSize &&
			p.z >= center.z && p.z >= center.z + cellSize)
		{
			if (t < tMax && t > tMin)
			{
				info.t = t;
				info.p = ray.point(t);
				return true;
			}
		}
	}

	//Return results.
	return false;
}