#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>

#include <Core/vector2.h>
#include <Core/input_manager.h>
#include <Core/GameObject.h>

#include <App/Character.h>

#define FIXEDFRAMERATE 0.02f

	std::vector<LLGP::Component*> g_componentList;

	int main()
	{
		// Initial setup
		sf::RenderWindow window(sf::VideoMode(990, 540), "SFML works!");
		std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();
		float deltaTime = 0.f;
		float timeSincePhysicsStep = 0.f;

		// Input & Player Refs
		LLGP::GameObject* playerCharacter = new LLGP::GameObject();
		g_componentList.push_back(playerCharacter->AddComponent<LLGP::Character>());

		// Player Initialisation
		playerCharacter->transform->position = LLGP::Vector3f(0, 0);
		for (LLGP::Component* c : g_componentList) {
			c->Awake();
		}

		//TODO: Move this garbage elsewhere heathen!!
		
		// Create Vectors
		LLGP::Vector2<float> rectSize = LLGP::Vector2<float>::one * 100;
		LLGP::Vector2<float> rectPos = LLGP::Vector2<float>(495, 270);

		// Create Texture
		sf::Texture rectTex; rectTex.loadFromFile("images/robotronsprites.png");
		LLGP::Vector2i spritesInTex(8, 9);
		LLGP::Vector2i rectTexSize(rectTex.getSize());
		sf::IntRect rectTexUV(0, (rectTexSize.y / spritesInTex.y) * 5, rectTexSize.x / spritesInTex.x, rectTexSize.y / spritesInTex.y);

		// Create and set sprite data
		sf::RectangleShape rectangle(rectSize);
		rectangle.setTexture(&rectTex);
		rectangle.setTextureRect(rectTexUV);
		rectangle.setOrigin(rectSize / 2);
		rectangle.setPosition(rectPos);

		// Update
		while (window.isOpen())
		{
			// Update Time
			std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
			deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - lastTime).count() / 1000000.f;
			lastTime = now;

			// Check closed
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			LLGP::InputManager::CheckInput();

			// Physics Update
			timeSincePhysicsStep += deltaTime;
			while (timeSincePhysicsStep > FIXEDFRAMERATE)
			{
				std::cout << "Time since last step:" << timeSincePhysicsStep << "\n";
				//std::cout << "Current Time: " << deltaTime << "\n";
				timeSincePhysicsStep -= FIXEDFRAMERATE;
			}

			// Render
			window.clear();
			window.draw(rectangle);
			window.display();
		}

		return 0;
	}

//}