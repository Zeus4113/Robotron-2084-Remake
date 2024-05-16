#include <App/EnemyManager.h>
#include <Core/RenderingManager.h>
#include <App/ScoreManager.h>
#include <iostream>
#include <Core/Rigidbody.h>
#include <Core/ObjectPool.h>
#include <Core/GameObject.h>
#include <App/GameManager.h>
#include <App/EnemyHulk.h>

namespace LLGP 
{

	void EnemyManager::SetupManager(GameManager* gm)
	{
		_gm = gm;

		std::vector<GameObject*> EnemyObjects = ObjectPool::GetAllObjectsOfType(ObjectTypes::Enemy);

		for (GameObject* o : EnemyObjects) 
		{
			_Enemies.push_back(o->GetComponent<Enemy>());
		}

		std::vector<GameObject*> CitizenObjects = ObjectPool::GetAllObjectsOfType(ObjectTypes::Citizen);

		for (GameObject* o : CitizenObjects)
		{
			_Citizens.push_back(o->GetComponent<Citizen>());
		}


		std::vector<GameObject*> HulkObjects = ObjectPool::GetAllObjectsOfType(ObjectTypes::EnemyHulk);

		for (GameObject* o : HulkObjects)
		{
			_Hulks.push_back(o->GetComponent<EnemyHulk>());
		}

	}

	void EnemyManager::UpdateCitizenDestination()
	{
		for (Citizen* c : _Citizens)
		{
			if (c->GetGameObject()->GetActive()) 
			{		
				Vector2f vec = Vector2f(c->GetDestination().x - c->GetGameObject()->transform->position.x, c->GetDestination().y - c->GetGameObject()->transform->position.y);
				float mag = vec.GetMagnitude();

				if (mag < 50.f)
				{
					c->Move(GetRandomPosition(false));
				}
				else 
				{
					c->Move(c->GetDestination());
				}
			}
		}
	}

	void EnemyManager::UpdateHulkDirection(Vector2f playerPos) 
	{
		Vector2f closestCitizen = Vector2f::zero;

		for (EnemyHulk* h : _Hulks) 
		{
			if (h->GetGameObject()->GetActive()) 
			{
				Vector2f hulkPosition = Vector2f(h->GetGameObject()->transform->position.x, h->GetGameObject()->transform->position.y);

				for (Citizen* c : _Citizens) 
				{
					if (c->GetGameObject()->GetActive()) 
					{
						Vector2f civPos = Vector2f(c->GetGameObject()->transform->position.x, c->GetGameObject()->transform->position.y);

						if (closestCitizen == Vector2f::zero) closestCitizen = civPos;
						else 
						{
							if ((civPos - hulkPosition).GetMagnitude() < (hulkPosition - closestCitizen).GetMagnitude() )
							{
								closestCitizen = civPos;
							}
						}
					}
				}

				if (closestCitizen == Vector2f::zero) 
				{
					closestCitizen = playerPos;
				}
			}

			h->Move(closestCitizen);		
		}
	}

	void EnemyManager::UpdateEnemyDirection(Vector2f playerPos)
	{
		for (Enemy* e : _Enemies)
		{
			if (!(playerPos.x == 0 && playerPos.y == 0)) 
			{
				if (e->GetGameObject()->GetActive()) {
					e->Move(playerPos);
				}
			}
		}
	}

	void EnemyManager::SpawnEnemies(int enemyAmount, int citizenAmount, int trapAmount)
	{
		for (int i = 0; i < enemyAmount; i++)
		{
			LLGP::ObjectPool::GetObject(LLGP::ObjectTypes::Enemy, GetRandomPosition(true));
		}

		for (int i = 0; i < std::ceil(enemyAmount / 3); i++)
		{
			LLGP::ObjectPool::GetObject(LLGP::ObjectTypes::EnemyHulk, GetRandomPosition(true));
		}

		for (int i = 0; i < trapAmount; i++)
		{
			LLGP::ObjectPool::GetObject(LLGP::ObjectTypes::Trap, GetRandomPosition(true));
		}

		for (int i = 0; i < citizenAmount; i++)
		{
			GameObject* go = LLGP::ObjectPool::GetObject(LLGP::ObjectTypes::Citizen, GetRandomPosition(true));
			go->GetComponent<Citizen>()->Move(GetRandomPosition(false));

		}

		_gm->GetScoreManager()->SetLevelRequirements(enemyAmount, citizenAmount);
	}

	Vector2f EnemyManager::GetRandomPosition(bool avoidPlayer)
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

			//std::cout << spawnPos.x << " " << spawnPos.y << std::endl;

			if (avoidPlayer) 
			{
				if ((spawnPos - playerPos).GetMagnitude() > 100.f)
				{
					return spawnPos;
				}
			}
			else 
			{
				return spawnPos;
			}
		}
		return Vector2f::zero;
	}
}