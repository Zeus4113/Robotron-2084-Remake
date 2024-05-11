#pragma once
#include<Core/Component.h>
#include<Core/vector2.h>
#include <Core/Event.h>

namespace LLGP 
{
	class Collider;

	class Character : public Component
	{
	public:
		Character(GameObject* owner);
		~Character() = default;

		void HandleMovement(Vector2f movementValue);
		void HandleShooting(Vector2f shootingValue);
		void OnShoot(int input);
		void Awake() override;

		void OnCollisionEnter(Collider* col);
		void OnCollisionExit(Collider* col);
		void OnCollisionStay(Collider* col);

		void OnDead();

		Event<int> onPlayerDead;

	private:
		float _MovementSpeed = 0.025f;
		Vector2f _AimVector;
	};
}
