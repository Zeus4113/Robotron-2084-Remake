#pragma once
#include<Core/Component.h>
#include<Core/Vector2.h>
#include <Core/Event.h>

namespace LLGP
{
	class Collider;

	class Enemy : public Component
	{
	public:
		Enemy(GameObject* owner);
		~Enemy();

		void Move(Vector2f playerPos);
		void OnCollisionEnter(Collider* col);
		void OnDead();

		Event<int> OnEnemyDead;

	private:
		float _MovementSpeed = 0.5f;
	};
}

