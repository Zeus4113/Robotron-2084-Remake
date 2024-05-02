#include "GameManager.h"
#include <Core/RenderingManager.h>
#include <Core/GameObject.h>
#include <Core/Collider.h>
#include <Core/Sprite.h>
#include <Core/ObjectPool.h>
#include <Core/input_manager.h>
#include <Core/Event.h>
#include <App/EnemyManager.h>

namespace LLGP 
{
	void GameManager::Initialise()
	{
		ObjectPool::AddObject(LLGP::ObjectTypes::Player, 1);
		ObjectPool::AddObject(LLGP::ObjectTypes::Enemy, 15);
		ObjectPool::AddObject(LLGP::ObjectTypes::Bullet, 25);
		ObjectPool::AddObject(LLGP::ObjectTypes::Trap, 10);
		ObjectPool::AddObject(LLGP::ObjectTypes::Citizen, 5);

		_DifficultyLevel = 1;

		InputManager::onRestart += std::bind(&GameManager::RestartGame, this, std::placeholders::_1);
	}

	void GameManager::SetupLevel()
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

	void GameManager::StartGame()
	{
		// Get Player Object
		LLGP::GameObject* playerCharacter = LLGP::ObjectPool::GetObject(LLGP::ObjectTypes::Player, LLGP::Vector2f(
			LLGP::RenderingManager::GetWindow()->getSize().x / 2,
			LLGP::RenderingManager::GetWindow()->getSize().y / 2
		));

		EnemyManager::SetupEnemies(_DifficultyLevel * _EnemyMultiplier, _DifficultyLevel * _CitizenMultiplier, _DifficultyLevel * _TrapMultiplier);
	}

	void GameManager::NextLevel()
	{
		ObjectPool::ReturnAllObjects();

		_DifficultyLevel++;

		StartGame();
	}

	void GameManager::RestartGame(bool isTrue)
	{
		if (!isTrue) return;
		
		ObjectPool::ReturnAllObjects();

		_DifficultyLevel = 1;

		StartGame();
	}
}