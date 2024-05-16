#pragma once
#include <Core/ObjectPool.h>


namespace LLGP 
{
	class GameManager;

	class EnemyHulk;

	class EnemyManager
	{
	public:
		EnemyManager() {}
		~EnemyManager() {}

		void SetupManager(GameManager* gm);

		void UpdateEnemyDirection(Vector2f playerPos);

		void SpawnEnemies(int enemyAmount, int citizenAmount, int trapAmount);

		Vector2f GetRandomPosition(bool avoidPlayer);

		void UpdateCitizenDestination();

        void UpdateHulkDirection(Vector2f playerPos);

	private:
		std::vector<Enemy*> _Enemies;
		std::vector<EnemyHulk*> _Hulks;
		std::vector<Citizen*> _Citizens;
		GameManager* _gm;
	};
}

