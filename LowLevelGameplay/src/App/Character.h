#pragma once
#include<Core/Component.h>
#include<Core/vector2.h>

namespace LLGP 
{
	class Character : public Component
	{
	public:
		Character(GameObject* owner) : Component(owner) {}
		~Character() = default;

		void HandleMovement(Vector2f movementValue);
		void HandleShooting(Vector2f shootingValue);
		void OnShoot(int input);
		void Awake() override;
	private:
		float _MovementSpeed = 0.025f;
	};
}
