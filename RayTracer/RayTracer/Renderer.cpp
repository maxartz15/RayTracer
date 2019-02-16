#include "Renderer.h"

#include <iostream>
#include <assert.h>

#include "Statistics.h"

#include "Ray.h"
#include "Scene.h"
#include "Tracers.h"
#include "Utils.h"

Renderer::Renderer(unsigned int width, unsigned int height) :
	m_width(width),
	m_height(height)
{
}

Renderer::~Renderer()
{
}

void Renderer::Render(sf::Image & output, Scene & scene) const
{
	Render(output, scene, 0, 0, m_width, m_height);
}

void Renderer::Render(sf::Image& output, Scene& scene, const unsigned int startX, const unsigned int startY, const unsigned int endX, const unsigned int endY) const
{
	if (startX < 0 || startX > m_width || startY < 0 || startY > m_height ||
		endY < startX || endX > m_width || endY < startY || endY > m_height)
	{
		std::cout << "Cannot render: " << startX << " " << endX << " | " << startY << " " << endY << std::endl;
	}
	else
	{
		for (unsigned int j = startY; j < endY; ++j)
		{
			for (unsigned int i = startX; i < endX; ++i)
			{
				vec3 c;

				//Sampling around pixel with one main centered sample.
				for (unsigned int s = 0; s < scene.GetSamples(); ++s)
				{
					Statistics::increaseMainTraces();

					float u, v;
					if (s == 0)
					{
						u = static_cast<float>(i) / static_cast<float>(m_width);
						v = static_cast<float>(j) / static_cast<float>(m_height);
					}
					else
					{
						//u = (static_cast<float>(i) + (Math::notSoRandomFloat01() * 2 - 1)) / static_cast<float>(m_width);
						//v = (static_cast<float>(j) + (Math::notSoRandomFloat01() * 2 - 1)) / static_cast<float>(m_height);

						u = (static_cast<float>(i) + (Math::notSoRandomFloat01() * .5f - .25f)) / static_cast<float>(m_width);
						v = (static_cast<float>(j) + (Math::notSoRandomFloat01() * .5f - .25f)) / static_cast<float>(m_height);
					}

					HitInfo info;
					c += Trace::Color(scene.GetCamera().GetRay(u, v), scene, info);
				}

				c /= static_cast<float>(scene.GetSamples());

				sf::Color cc = Utils::Vec3ToColor(c, true);

				//Flip the result.
				output.setPixel(m_width - 1 - i, m_height - 1 - j, cc);
			}
		}
	}
}