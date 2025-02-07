#include <SFML/Graphics.hpp>
#include <MathLibrary.h>
#include <iostream>

#include "Statistics.h"
#include "Renderer.h"

#include "Utils.h"
#include "Ray.h"
#include "Hitables.h"
#include "Lights.h"
#include "Scenes.h"

void UpdateWindow(sf::RenderWindow& window, const sf::Sprite& output);

int main()
{
	std::cout << "[Controls] (Make sure to select the output window.) \n R = Render. \n T = Toggle Turntable. \n S = Save to PNG. \n I = Toggle Statitics Info. \n ESC = Exit." << std::endl;

	//Render 'resolution'.
	unsigned int selection = 0;
	unsigned int x = 1024;
	unsigned int y = 512;
	unsigned int d = 4;
	unsigned int s = 2;
	unsigned int ss = 2;

	std::cout << "[Option] Select scene (1 - 5): ";
	std::cin >> selection;

	char useDefaultSettings;
	std::cout << "[Option] Use default settings? y, n: ";
	std::cin >> useDefaultSettings;

	if (useDefaultSettings == 'n')
	{
		std::cout << " Width (unsigned int): ";
		std::cin >> x;
		y = x / 2;
		std::cout << " MaxDepth (unsigned int): ";
		std::cin >> d;
		std::cout << " Samples (unsigned int): ";
		std::cin >> s;
		std::cout << " SubSamples (unsigned int): ";
		std::cin >> ss;
		std::cout << std::endl;
	}

	//Stats.
	Statistics stats;

	//Setup output window to display the rendered image on.
	sf::RenderWindow window(sf::VideoMode(1024, 512), "Output", sf::Style::None);

	//Setup output image.
	sf::Image image;
	image.create(x, y);
	sf::Texture texture;
	texture.loadFromImage(image);
	sf::Sprite sprite;
	sprite.setTexture(texture);

	//Scale sprite to fit the window.
	sf::Vector2u windowSize = window.getSize();
	float scaleX = static_cast<float>(windowSize.x) / static_cast<float>(x);
	float scaleY = static_cast<float>(windowSize.y) / static_cast<float>(y);
	sprite.setScale(scaleX, scaleY);

	//Setup render things.
	Camera camera(70.0f, static_cast<float>(x) / static_cast<float>(y), vec3(1, 0, -1), vec3(0, 0, 1), vec3(0, 1, 0));
	
	//Load default (small) scene.
	Scene* scene;

	//Select scene
	switch (selection)
	{
	case 1:
		scene = new Scene1(camera, d, s, ss);
		break;
	case 2:
		scene = new Scene2(camera, d, s, ss);
		break;
	case 3:
		scene = new Scene3(camera, d, s, ss);
		break;
	case 4:
		scene = new Scene4(camera, d, s, ss);
		break;
	case 5:
		scene = new Scene5(camera, d, s, ss);
		break;
	default:
		scene = new Scene0(camera, d, s, ss);
		break;
	}

	Renderer renderer = Renderer(x, y);
	
	bool render = true;	//Set to true to start rendering on launch.
	bool turnTable = false;
	bool printStats = false;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::R)
			{
				render = true;
			}

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::T)
			{
				turnTable = !turnTable;
				std::cout << "TurnTable [" << turnTable << "]" << std::endl;
			}

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::S)
			{
				image.saveToFile("render.png");
				std::cout << "[Save] render.png saved." << std::endl;
			}

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::I)
			{
				printStats = !printStats;
				std::cout << "PrintStats [" << printStats << "]" << std::endl;
				if (printStats)
				{
					stats.PrintSnapShot();
				}
			}
		}

		if (turnTable)
		{
			vec3 lf = camera.GetLookFrom();
			vec3 la = camera.GetLookAt();
			Math::rotateAroundPoint2D(lf.x, lf.z, la.x, la.z, 1.f);
			camera.SetLookFrom(lf);
			render = true;
		}

		if (render)
		{
			stats.Reset();
			std::cout << "[Start] Rendering | Size: " << x << "x" << y << " maxDepth: " << d << " samples: " << s << " subSamples: " << ss << std::endl;

			//Render.
			renderer.Render(image, *scene);

			std::cout << "[End] Rendering" << std::endl;
			stats.SnapShot();
			
			//Stats.
			if (printStats)
			{
				stats.PrintSnapShot();
			}

			//Update texture/sprite when done with rendering.
			texture.update(image);
			UpdateWindow(window, sprite);
			render = false;
		}
	}

	return 0;
}

void UpdateWindow(sf::RenderWindow& window, const sf::Sprite& output)
{
	if (window.isOpen())
	{
		window.clear();
		window.draw(output);
		window.display();
	}
}