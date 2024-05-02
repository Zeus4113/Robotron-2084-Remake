#pragma once
#include <Core/RenderingManager.h>
#include <Core/PhysicsManager.h>
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

		void Initialise();

		void SetupLevel();

		void StartGame();

		void NextLevel();

		void RestartGame(bool isTrue);
	private:
		int _difficultyLevel = 1;
		int _enemyMultiplier = 4;
		int _trapMultiplier = 3;
		int _citizenMultiplier = 2;
	};
}

