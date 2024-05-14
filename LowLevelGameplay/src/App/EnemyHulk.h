#pragma once
#include<Core/Component.h>
#include<Core/Vector2.h>
#include <Core/Event.h>

namespace LLGP 
{
	class Collider;

	class EnemyHulk : public Component
	{
	public:
		EnemyHulk(GameObject* owner);
		~EnemyHulk();

		void Move(Vector2f playerPos);
		void OnCollisionEnter(Collider* col);
		void OnDead();

		Event<int> OnEnemyDead;

	private:
		float _MovementSpeed = 0.5f;
	};
}

