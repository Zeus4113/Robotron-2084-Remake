#pragma once
#include <Core/ObjectPool.h>

namespace LLGP 
{
	class GameManager;

	class EnemyManager
	{
	public:
		EnemyManager() {}
		~EnemyManager() {}

		void SetupManager(GameManager* gm);

		void UpdateEnemyDirection(Vector3f playerPos);

		void SpawnEnemies(int enemyAmount, int citizenAmount, int trapAmount);

		Vector2f GetRandomPosition(bool avoidPlayer);

		void UpdateCitizenDestination();

	private:
		std::vector<Enemy*> _Enemies;
		std::vector<Citizen*> _Citizens;
		GameManager* _gm;
	};
}

