       #include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>

#include <Core/vector2.h>
#include <Core/input_manager.h>
#include <Core/GameObject.h>
#include <Core/Collider.h>

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
		//g_componentList.push_back(playerCharacter->AddComponent<LLGP::Collider>());

		// Player Initialisation
		playerCharacter->transform->position = LLGP::Vector3f(window.getSize().x / 2, window.getSize().y / 2);

<<<<<<< Updated upstream
		for (LLGP::Component* c : g_componentList) {
			c->Awake();
		}
=======
		LLGP::EnemyManager::SetGameManager(gm);

		// Awake
		LLGP::EntityManager::Awake();
>>>>>>> Stashed changes

		//TODO: Move this garbage elsewhere heathen!!
		
		// Create Vectors
		LLGP::Vector2f rectSize = LLGP::Vector2f::one * 100;
		LLGP::Vector2f rectPos = LLGP::Vector2f(495, 270);

		// Create Texture
		//sf::Texture rectTex; rectTex.loadFromFile("images/robotronsprites.png");
		//LLGP::Vector2i spritesInTex(8, 9);
		//LLGP::Vector2i rectTexSize(rectTex.getSize());
		//sf::IntRect rectTexUV(0, (rectTexSize.y / spritesInTex.y) * 5, rectTexSize.x / spritesInTex.x, rectTexSize.y / spritesInTex.y);

		// Create and set sprite data
		sf::RectangleShape playerSprite(rectSize);
		playerSprite.setOrigin(rectSize / 2);
		playerSprite.setPosition(playerCharacter->transform->position.x, playerCharacter->transform->position.y);

		//rectangle.setTexture(&rectTex);
		//rectangle.setTextureRect(rectTexUV);

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

<<<<<<< Updated upstream
=======
			// Enemies Update
			if (LLGP::ObjectPool::GetObjectRef(LLGP::ObjectTypes::Player)->GetActive()) 
			{
				LLGP::EnemyManager::UpdateEnemyDirection(LLGP::ObjectPool::GetObjectRef(LLGP::ObjectTypes::Player)->GetTransform()->position);
			}
			else
			{
				LLGP::EnemyManager::UpdateEnemyDirection(LLGP::Vector3f::zero);
			}

			if ((rand() % 500) > 400) 
			{
				LLGP::EnemyManager::UpdateCitizenDestination();
			}

>>>>>>> Stashed changes
			// Physics Update
			timeSincePhysicsStep += deltaTime;
			while (timeSincePhysicsStep > FIXEDFRAMERATE)
			{
				//std::cout << "Time since last step:" << timeSincePhysicsStep << "\n";
				//std::cout << "Current Time: " << deltaTime << "\n";

				//playerCharacter->GetComponent<LLGP::Character>()->Move();

				timeSincePhysicsStep -= FIXEDFRAMERATE;

			}

			playerSprite.setPosition(playerCharacter->transform->position.x, playerCharacter->transform->position.y);

			// Render
			window.clear();
			window.draw(playerSprite);
			window.display();
		}

		return 0;
	}

//}