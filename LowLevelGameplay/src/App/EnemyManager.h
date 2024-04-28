#pragma once
#include <Core/ObjectPool.h>

namespace LLGP 
{
	static class EnemyManager
	{
	public:
		EnemyManager() {}
		~EnemyManager() {}

		static void RegisterEnemy(Enemy* newEnemy);

		static void UnregisterEnemy(Enemy* oldEnemy);

		static void UpdateEnemyDirection(Vector3f playerPos);

	private:
		static std::vector<Enemy*> _Enemies;
	};
}

