#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>

#include <Core/vector2.h>
#include <Core/input_manager.h>
#include <Core/GameObject.h>
#include <Core/Collider.h>
#include <Core/Sprite.h>
#include <Core/Component.h>
#include <App/Character.h>
#include <Core/PhysicsManager.h>

#define FIXEDFRAMERATE 0.02f

	std::vector<LLGP::Component*> g_componentList;

	int main()
	{
		// Initial setup

		sf::RenderWindow window(sf::VideoMode(990, 540), "SFML works!");
		std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();
		float deltaTime = 0.f;
		float timeSincePhysicsStep = 0.f;

		// Create Vectors
		LLGP::Vector2f rectSize = LLGP::Vector2f::one * 25;
		LLGP::Vector2f rectPos = LLGP::Vector2f(495, 270);

		// Create GameObject (Player)
		LLGP::GameObject* playerCharacter = new LLGP::GameObject();
		playerCharacter->transform->position = LLGP::Vector3f(window.getSize().x / 3, window.getSize().y / 3);

		// Add Character Component (Player)
		g_componentList.push_back(playerCharacter->AddComponent<LLGP::Character>());
		
		// Add and Set Collider Component (Player)
		g_componentList.push_back(playerCharacter->AddComponent<LLGP::Rigidbody>());
		playerCharacter->GetComponent<LLGP::Rigidbody>()->SetSize(rectSize /2.f);
		playerCharacter->GetComponent<LLGP::Rigidbody>()->SetMass(1.f);

		// Add and Set Sprite Component (Player)
		g_componentList.push_back(playerCharacter->AddComponent<LLGP::Sprite>());
		playerCharacter->GetComponent<LLGP::Sprite>()->SetSize(rectSize);

		// Create Character
		LLGP::GameObject* enemyCharacter = new LLGP::GameObject();
		enemyCharacter->transform->position = LLGP::Vector3f(window.getSize().x / 1.5, window.getSize().y / 3);

		// Add and Set Collider Component (Enemy)
		g_componentList.push_back(enemyCharacter->AddComponent<LLGP::Rigidbody>());
		enemyCharacter->GetComponent<LLGP::Rigidbody>()->SetSize(rectSize / 2.f);
		enemyCharacter->GetComponent<LLGP::Rigidbody>()->SetMass(0.5f);

		// Add and Set Sprite Component (Enemy)
		g_componentList.push_back(enemyCharacter->AddComponent<LLGP::Sprite>());
		enemyCharacter->GetComponent<LLGP::Sprite>()->SetSize(rectSize);


		// Create level borders
		LLGP::GameObject* bottomBorder = new LLGP::GameObject();
		bottomBorder->transform->position = LLGP::Vector3f(window.getSize().x / 2 , window.getSize().y );

		LLGP::GameObject* topBorder = new LLGP::GameObject();
		topBorder->transform->position = LLGP::Vector3f(window.getSize().x / 2, 0);

		LLGP::GameObject* leftBorder = new LLGP::GameObject();
		leftBorder->transform->position = LLGP::Vector3f(0, window.getSize().y / 2);

		LLGP::GameObject* RightBorder = new LLGP::GameObject();
		RightBorder->transform->position = LLGP::Vector3f(window.getSize().x, window.getSize().y / 2);

		// Add and Set Collider Component (Border)
		g_componentList.push_back(bottomBorder->AddComponent<LLGP::Collider>());
		bottomBorder->GetComponent<LLGP::Collider>()->SetSize(LLGP::Vector2f(1000, 10) / 2);

		g_componentList.push_back(topBorder->AddComponent<LLGP::Collider>());
		topBorder->GetComponent<LLGP::Collider>()->SetSize(LLGP::Vector2f(1000, 10) / 2);

		g_componentList.push_back(leftBorder->AddComponent<LLGP::Collider>());
		leftBorder->GetComponent<LLGP::Collider>()->SetSize(LLGP::Vector2f(10, 1000) / 2);

		g_componentList.push_back(RightBorder->AddComponent<LLGP::Collider>());
		RightBorder->GetComponent<LLGP::Collider>()->SetSize(LLGP::Vector2f(10, 1000) / 2);

		// Add and Set Sprite Component (Border)
		g_componentList.push_back(bottomBorder->AddComponent<LLGP::Sprite>());
		bottomBorder->GetComponent<LLGP::Sprite>()->SetSize(LLGP::Vector2f(1000, 10));

		g_componentList.push_back(topBorder->AddComponent<LLGP::Sprite>());
		topBorder->GetComponent<LLGP::Sprite>()->SetSize(LLGP::Vector2f(1000, 10));

		g_componentList.push_back(leftBorder->AddComponent<LLGP::Sprite>());
		leftBorder->GetComponent<LLGP::Sprite>()->SetSize(LLGP::Vector2f(10, 1000));

		g_componentList.push_back(RightBorder->AddComponent<LLGP::Sprite>());
		RightBorder->GetComponent<LLGP::Sprite>()->SetSize(LLGP::Vector2f(10, 1000));

		// Register Colliders
		LLGP::PhysicsManager::RegisterRigidbody(playerCharacter->GetComponent<LLGP::Rigidbody>());
		LLGP::PhysicsManager::RegisterCollider(bottomBorder->GetComponent<LLGP::Collider>());
		LLGP::PhysicsManager::RegisterCollider(topBorder->GetComponent<LLGP::Collider>());
		LLGP::PhysicsManager::RegisterCollider(leftBorder->GetComponent<LLGP::Collider>());
		LLGP::PhysicsManager::RegisterCollider(RightBorder->GetComponent<LLGP::Collider>());

		// Awake
		for (LLGP::Component* c : g_componentList) {
			c->Awake();
		}

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
				LLGP::PhysicsManager::UpdatePhysics();
				LLGP::PhysicsManager::CheckCollisions();
				timeSincePhysicsStep -= FIXEDFRAMERATE;
			}

			// Render
			window.clear();

			for (LLGP::Component* C : g_componentList) {
				if (dynamic_cast<LLGP::Sprite*>(C)) {
					dynamic_cast<LLGP::Sprite*>(C)->UpdateRender();
					window.draw(dynamic_cast<LLGP::Sprite*>(C)->GetShape());
				}
			}

			window.display();
		}

		return 0;
	}