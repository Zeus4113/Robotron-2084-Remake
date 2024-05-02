#include "EnemyManager.h"
#include "Core/ObjectPool.h"
#include "Core/RenderingManager.h"
#include <App/GameManager.h>
#include <iostream>

namespace LLGP 
{
	std::vector<Enemy*> EnemyManager::_Enemies;
	std::vector<Citizen*> EnemyManager::_Citizens;

	int EnemyManager::_EnemiesRemaining;
	int EnemyManager::_CitizensRemaining;

	GameManager* EnemyManager::_gm;

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

	void EnemyManager::SetupEnemies(int enemyAmount, int citizenAmount, int trapAmount) 
	{
		_EnemiesRemaining = enemyAmount;
		_CitizensRemaining = citizenAmount;

		std::cout << enemyAmount << " " << citizenAmount << std::endl;

		for (int i = 0; i < enemyAmount; i++)
		{
			LLGP::ObjectPool::GetObject(LLGP::ObjectTypes::Enemy, GetSpawnPosition());
		}

		for (int i = 0; i < trapAmount; i++)
		{
			LLGP::ObjectPool::GetObject(LLGP::ObjectTypes::Trap, GetSpawnPosition());
		}

		for (int i = 0; i < citizenAmount; i++)
		{
			LLGP::ObjectPool::GetObject(LLGP::ObjectTypes::Citizen, GetSpawnPosition());
		}
	}

	void EnemyManager::EnemyKilled() 
	{
		_EnemiesRemaining--;

		if (_EnemiesRemaining <= 0 && _CitizensRemaining <= 0) 
		{
			_gm->NextLevel();
		}
	}

	void EnemyManager::CitizenSaved()
	{
		_CitizensRemaining--;

		if (_EnemiesRemaining <= 0 && _CitizensRemaining <= 0)
		{
			_gm->NextLevel();
		}
	}



	Vector2f EnemyManager::GetSpawnPosition()
	{
		while (true)
		{
			Vector2f spawnPos = Vector2f::zero;
			Vector2f playerPos = Vector2f(
				LLGP::ObjectPool::GetObjectRef(LLGP::ObjectTypes::Player)->transform->position.x,
				LLGP::ObjectPool::GetObjectRef(LLGP::ObjectTypes::Player)->transform->position.y
			);


			spawnPos = LLGP::Vector2f(
				rand() % LLGP::RenderingManager::GetWindow()->getSize().x,
				rand() % LLGP::RenderingManager::GetWindow()->getSize().y
			);

			if ((spawnPos - playerPos).GetMagnitude() > 100.f)
			{
				return spawnPos;
			}
		}
		return Vector2f::zero;
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