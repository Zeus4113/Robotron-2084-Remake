#include "EnemyManager.h"

namespace LLGP 
{
	std::vector<Enemy*> EnemyManager::_Enemies;
	std::vector<Citizen*> EnemyManager::_Citizens;

	void EnemyManager::RegisterEnemy(Enemy* newEnemy)
	{
		_Enemies.push_back(newEnemy);
	}

	void EnemyManager::UnregisterEnemy(Enemy* oldEnemy)
	{
		for (int i = 0; i < _Enemies.size(); ++i)
		{
			if (_Enemies[i] == oldEnemy)
			{
				_Enemies.erase(_Enemies.begin() + i);
			}
		}
	}

	void EnemyManager::RegisterCitizen(Citizen* newCitizen)
	{
		_Citizens.push_back(newCitizen);
	}

	void EnemyManager::UnregisterCitizen(Citizen* oldCitizen)
	{
		for (int i = 0; i < _Citizens.size(); ++i)
		{
			if (_Citizens[i] == oldCitizen)
			{
				_Citizens.erase(_Citizens.begin() + i);
			}
		}
	}

	void EnemyManager::UpdateCitizenDestination()
	{
		for (Citizen* c : _Citizens)
		{
			if (c->GetGameObject()->GetActive()) {
				c->GenerateDestination();
			}
		}
	}

	void EnemyManager::UpdateEnemyDirection(Vector3f playerPos)
	{
		for (Enemy* e : _Enemies)
		{
			if (!(playerPos.x == 0 && playerPos.y == 0)) 
			{
				if (e->GetGameObject()->GetActive()) {
					e->Move(Vector2(playerPos.x, playerPos.y));
				}
			}
		}
	}
}