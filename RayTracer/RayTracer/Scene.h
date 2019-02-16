#pragma once
#include <vector>

#include "Hitable.h"
#include "Light.h"
#include "Camera.h"

class Scene
{
public:
	Scene(Camera& camera, unsigned int maxDepth = 128, unsigned int maxSamples = 1, unsigned int maxSubSamples = 1);
	virtual ~Scene();

	const Camera& GetCamera() const;
	void SetCamera(Camera& camera);

	const float GetAmbientLightIntensity() const;
	const vec3 GetAmbientLight() const;
	void SetAmbientLight(vec3 color, float intensity);

	const vec3& GetBackgroundColor() const;
	void SetBackgroundColor(vec3 color);

	const float& GetTMin() const { return m_tMin; };
	void SetTMin(float tMin);
	const float& GetTMax() const { return m_tMax; };
	void SetTMax(float tMax);

	const unsigned int& GetMaxDepth() const { return m_maxDepth; };
	const unsigned int& GetSamples() const { return m_samples; };
	const unsigned int& GetSubSamples() const { return m_subSamples; };

	std::vector<Light*> lights;
	std::vector<Hitable*> hitables;
protected:
	Camera& m_camera;

	vec3 m_ambientLight;
	float m_ambientLightIntensity;
	vec3 m_backgroundColor;

	float m_tMin;
	float m_tMax;

	unsigned int m_maxDepth = 128;
	unsigned int m_samples = 1;
	unsigned int m_subSamples = 1;
};