#include "Enemy.h"
#include<Core/Rigidbody.h>
#include<Core/Sprite.h>
#include <Core/Collider.h>
#include<Core/GameObject.h>
#include<Core/Event.h>
#include <Core/ObjectPool.h>
#include <App/EnemyManager.h>

namespace LLGP 
{
	Enemy::Enemy(GameObject* owner) : Component(owner)
	{
		EnemyManager::RegisterEnemy(this);

		// Add and Set Rigidbody Component
		owner->AddComponent<LLGP::Rigidbody>();
		owner->GetComponent<LLGP::Rigidbody>()->SetSize(Vector2f(25.f, 25.f) / 2.f);
		owner->GetComponent<LLGP::Rigidbody>()->SetMass(1.f);

		// Add and Set Sprite Component
		owner->AddComponent<LLGP::Sprite>();
		owner->GetComponent<LLGP::Sprite>()->SetSize(Vector2f(25.f, 25.f));

		if (owner->GetComponent<Collider>())
		{
			owner->GetComponent<Collider>()->onCollisionEnter += std::bind(&Enemy::OnCollisionEnter, this, std::placeholders::_1);
		}
	}

	Enemy::~Enemy()
	{
		EnemyManager::UnregisterEnemy(this);
	}

	void Enemy::Move(Vector2f playerPos)
	{
		Vector2f direction = Vector2f(
			playerPos.x - this->GetGameObject()->transform->position.x,
			playerPos.y - this->GetGameObject()->transform->position.y
		);

		Vector2f norm = direction.Normalise();
		this->GetGameObject()->GetComponent<Rigidbody>()->SetVelocity(Vector2f(norm.x, norm.y) * _MovementSpeed);

	}

	void Enemy::OnCollisionEnter(Collider* col)
	{
		std::cout << this->GetGameObject()->GetName() << " is touching " << col->GetGameObject()->GetName() << std::endl;

		if (col->GetGameObject()->CompareType(ObjectTypes::Player)) 
		{
			col->GetGameObject()->GetComponent<Character>()->OnDead();
		}
	}

	void Enemy::OnDead()
	{
		this->GetGameObject()->GetComponent<Rigidbody>()->SetVelocity(Vector2f(0, 0));
		ObjectPool::ReturnObject(this->GetGameObject());
	}

}