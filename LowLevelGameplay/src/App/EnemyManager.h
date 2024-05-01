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

		static void RegisterCitizen(Citizen* newCitizen);

		static void UnregisterCitizen(Citizen* oldCitizen);

		static void UpdateEnemyDirection(Vector3f playerPos);

		static void UpdateCitizenDestination();

	private:
		static std::vector<Enemy*> _Enemies;
		static std::vector<Citizen*> _Citizens;
	};
}

