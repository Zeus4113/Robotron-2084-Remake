#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>

#include <Core/vector2.h>
#include <Core/input_manager.h>
#include <Core/GameObject.h>
#include <Core/Collider.h>
#include <Core/Sprite.h>
#include <Core/Rigidbody.h>
#include <Core/Component.h>
#include <App/Character.h>
#include <Core/PhysicsManager.h>
#include <Core/EntityManager.h>
#include <Core/RenderingManager.h>
#include <App/Bullet.h>

#define FIXEDFRAMERATE 0.02f
#define RECTSIZE LLGP::Vector2f::one * 25

	int main()
	{
		// Setup Window
		LLGP::RenderingManager::StartRender();

		// Setup deltaTime and Physics Step
		std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();
		float deltaTime = 0.f;
		float timeSincePhysicsStep = 0.f;

		// Create GameObject (Player)
		LLGP::GameObject* playerCharacter = new LLGP::GameObject();
		playerCharacter->transform->position = LLGP::Vector3f(
			LLGP::RenderingManager::GetWindow()->getSize().x / 3,
			LLGP::RenderingManager::GetWindow()->getSize().y / 3
		);

		// Add Character Component (Player)
		playerCharacter->AddComponent<LLGP::Character>();
		
		// Add and Set Collider Component (Player)
		playerCharacter->AddComponent<LLGP::Rigidbody>();
		playerCharacter->GetComponent<LLGP::Rigidbody>()->SetSize(RECTSIZE / 2.f);
		playerCharacter->GetComponent<LLGP::Rigidbody>()->SetMass(1.f);

		// Add and Set Sprite Component (Player)
		playerCharacter->AddComponent<LLGP::Sprite>();
		playerCharacter->GetComponent<LLGP::Sprite>()->SetSize(RECTSIZE);

		// Create bullet object
		//LLGP::Bullet* bullet = new LLGP::Bullet();

		// Create Character
		LLGP::GameObject* enemyCharacter = new LLGP::GameObject();
		enemyCharacter->transform->position = LLGP::Vector3f(
			LLGP::RenderingManager::GetWindow()->getSize().x / 1.5,
			LLGP::RenderingManager::GetWindow()->getSize().y / 3
		);

		// Add and Set Collider Component (Enemy)
		enemyCharacter->AddComponent<LLGP::Rigidbody>();
		enemyCharacter->GetComponent<LLGP::Rigidbody>()->SetSize(RECTSIZE / 2.f);
		enemyCharacter->GetComponent<LLGP::Rigidbody>()->SetMass(0.5f);

		// Add and Set Sprite Component (Enemy)
		enemyCharacter->AddComponent<LLGP::Sprite>();
		enemyCharacter->GetComponent<LLGP::Sprite>()->SetSize(RECTSIZE);


		// Create level borders
		LLGP::GameObject* bottomBorder = new LLGP::GameObject();
		bottomBorder->transform->position = LLGP::Vector3f(
			LLGP::RenderingManager::GetWindow()->getSize().x / 2 , 
			LLGP::RenderingManager::GetWindow()->getSize().y 
		);

		LLGP::GameObject* topBorder = new LLGP::GameObject();
		topBorder->transform->position = LLGP::Vector3f(
			LLGP::RenderingManager::GetWindow()->getSize().x / 2,
			0
		);

		LLGP::GameObject* leftBorder = new LLGP::GameObject();
		leftBorder->transform->position = LLGP::Vector3f(
			0, 
			LLGP::RenderingManager::GetWindow()->getSize().y / 2
		);

		LLGP::GameObject* RightBorder = new LLGP::GameObject();
		RightBorder->transform->position = LLGP::Vector3f(
			LLGP::RenderingManager::GetWindow()->getSize().x, 
			LLGP::RenderingManager::GetWindow()->getSize().y / 2
		);

		// Add and Set Collider Component (Border)
		bottomBorder->AddComponent<LLGP::Collider>();
		bottomBorder->GetComponent<LLGP::Collider>()->SetSize(LLGP::Vector2f(1000, 10) / 2);

		topBorder->AddComponent<LLGP::Collider>();
		topBorder->GetComponent<LLGP::Collider>()->SetSize(LLGP::Vector2f(1000, 10) / 2);

		leftBorder->AddComponent<LLGP::Collider>();
		leftBorder->GetComponent<LLGP::Collider>()->SetSize(LLGP::Vector2f(10, 1000) / 2);

		RightBorder->AddComponent<LLGP::Collider>();
		RightBorder->GetComponent<LLGP::Collider>()->SetSize(LLGP::Vector2f(10, 1000) / 2);

		// Add and Set Sprite Component (Border)
		bottomBorder->AddComponent<LLGP::Sprite>();
		bottomBorder->GetComponent<LLGP::Sprite>()->SetSize(LLGP::Vector2f(1000, 10));

		topBorder->AddComponent<LLGP::Sprite>();
		topBorder->GetComponent<LLGP::Sprite>()->SetSize(LLGP::Vector2f(1000, 10));

		leftBorder->AddComponent<LLGP::Sprite>();
		leftBorder->GetComponent<LLGP::Sprite>()->SetSize(LLGP::Vector2f(10, 1000));

		RightBorder->AddComponent<LLGP::Sprite>();
		RightBorder->GetComponent<LLGP::Sprite>()->SetSize(LLGP::Vector2f(10, 1000));

		// Awake
		LLGP::EntityManager::Awake();

		// Update
		while (LLGP::RenderingManager::GetWindow()->isOpen())
		{
			// Update Time
			std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
			deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - lastTime).count() / 1000000.f;
			lastTime = now;

			// Check closed
			sf::Event event;
			while (LLGP::RenderingManager::GetWindow()->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					LLGP::RenderingManager::GetWindow()->close();
			}

			// Input Update
			LLGP::InputManager::CheckInput();

			// Physics Update
			timeSincePhysicsStep += deltaTime;
			while (timeSincePhysicsStep > FIXEDFRAMERATE)
			{
				LLGP::PhysicsManager::UpdatePhysics();
				LLGP::PhysicsManager::CheckCollisions();
				timeSincePhysicsStep -= FIXEDFRAMERATE;
			}

			// Render Update
			LLGP::RenderingManager::UpdateRender();
		}

		return 0;
	}