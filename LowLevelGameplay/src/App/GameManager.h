#pragma once
#include <Core/RenderingManager.h>
#include <Core/GameObject.h>
#include <Core/Collider.h>
#include <Core/Sprite.h>
#include <Core/ObjectPool.h>
#include <Core/input_manager.h>
#include <Core/Event.h>

namespace LLGP
{
	class GameManager
	{
	public:
		GameManager() {}
		~GameManager() {}

		void Initialise() 
		{
			ObjectPool::AddObject(LLGP::ObjectTypes::Player, 1);
			ObjectPool::AddObject(LLGP::ObjectTypes::Enemy, 10);
			ObjectPool::AddObject(LLGP::ObjectTypes::Bullet, 10);

			InputManager::onRestart += std::bind(&GameManager::RestartGame, this, std::placeholders::_1);
		}

		void SetupLevel()
		{
			// Create level borders
			GameObject* bottomBorder = new LLGP::GameObject();
			bottomBorder->transform->position = LLGP::Vector3f(
				LLGP::RenderingManager::GetWindow()->getSize().x / 2,
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
		}

		void StartGame()
		{
			// Get Player Object
			LLGP::GameObject* playerCharacter = LLGP::ObjectPool::GetObject(LLGP::ObjectTypes::Player, LLGP::Vector2f(
				LLGP::RenderingManager::GetWindow()->getSize().x / 2,
				LLGP::RenderingManager::GetWindow()->getSize().y / 2
			));

			for (int i = 0; i < 10; i++) 
			{
				Vector2f spawnPos = Vector2f::zero;

				switch (rand() % 3) {
				case 0:
					spawnPos = LLGP::Vector2f(
						rand() % LLGP::RenderingManager::GetWindow()->getSize().x,
						rand() % LLGP::RenderingManager::GetWindow()->getSize().y / 3
					);
					break;

				case 1:
					spawnPos = LLGP::Vector2f(
						rand() % LLGP::RenderingManager::GetWindow()->getSize().x,
						rand() % LLGP::RenderingManager::GetWindow()->getSize().y / 3 + LLGP::RenderingManager::GetWindow()->getSize().y / 1.5f
					);
					break;

				case 2:
					spawnPos = LLGP::Vector2f(
						rand() % LLGP::RenderingManager::GetWindow()->getSize().x / 3,
						rand() % LLGP::RenderingManager::GetWindow()->getSize().y
					);
					break;

				case 3:
					spawnPos = LLGP::Vector2f(
						rand() % LLGP::RenderingManager::GetWindow()->getSize().x / 3 + LLGP::RenderingManager::GetWindow()->getSize().x / 1.5f,
						rand() % LLGP::RenderingManager::GetWindow()->getSize().y
					);
					break;

				}

				LLGP::GameObject* enemyCharacter = LLGP::ObjectPool::GetObject(LLGP::ObjectTypes::Enemy, spawnPos);
			}
		}

		void RestartGame(bool isTrue) 
		{
			if (!isTrue) return;

			ObjectPool::ReturnAllObjects();
			StartGame();
		}
	};
}

