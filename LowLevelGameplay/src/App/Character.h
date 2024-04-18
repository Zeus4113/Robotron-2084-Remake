#pragma once
#include<Core/Component.h>
#include<Core/vector2.h>
#include<Core/Transform.h>

namespace LLGP 
{
	class Character : public Component
	{
	public:
		Character(GameObject* owner) : Component(owner) {}
		~Character() = default;

		void ReadInput(Vector2f movementValue);
		void Awake() override;
	private:
		Vector2f movementVector = Vector2f(0,0);
		float movementSpeed = 0.25;
	};
}
