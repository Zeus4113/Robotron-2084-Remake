#include "EnemyManager.h"

namespace LLGP 
{
	std::vector<Enemy*> EnemyManager::_Enemies;


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
	void EnemyManager::UpdateEnemyDirection(Vector3f playerPos)
	{
		for (Enemy* e : _Enemies)
		{
			if (e->GetGameObject()->GetActive()) {
				e->Move(Vector2(playerPos.x, playerPos.y));
			}
		}
	}
}