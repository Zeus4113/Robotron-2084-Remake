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
		void Awake() override;
	};
}
