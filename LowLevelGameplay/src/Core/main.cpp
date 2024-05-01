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
#include <App/Enemy.h>
#include <Core/ObjectPool.h>
#include <App/GameManager.h>
#include <App/EnemyManager.h>

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

		LLGP::GameManager* gm = new LLGP::GameManager();

		gm->Initialise();
		gm->SetupLevel();

		// Awake
		LLGP::EntityManager::Awake();

		gm->StartGame();

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

			if (LLGP::ObjectPool::GetObjectRef(LLGP::ObjectTypes::Player)->GetActive()) 
			{
				std::cout << "Player Active!" << std::endl;
				LLGP::EnemyManager::UpdateEnemyDirection(LLGP::ObjectPool::GetObjectRef(LLGP::ObjectTypes::Player)->GetTransform()->position);
			}
			else
			{
				std::cout << "Player Not Active!" << std::endl;
				LLGP::EnemyManager::UpdateEnemyDirection(LLGP::Vector3f::zero);
			}

			if ((rand() % 500) > 400) 
			{
				LLGP::EnemyManager::UpdateCitizenDestination();
			}

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