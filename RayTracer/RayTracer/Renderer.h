#pragma once
#include<SFML/Graphics/Image.hpp>
#include<MathLibrary.h>

class Scene;

class Renderer
{
public:
	Renderer(unsigned int width, unsigned int height);
	~Renderer();

	void Render(sf::Image& output, Scene& scene) const;
	void Render(sf::Image& output, Scene& scene, const unsigned int startX, const unsigned int startY, const unsigned int endX, const unsigned int endY) const;

private:
	unsigned int m_width;
	unsigned int m_height;
};