#pragma once
#include<Core/Component.h>
#include <Core/vector2.h>

namespace LLGP
{
	class Collider;

	class Citizen : public Component
	{
	public:
		Citizen(GameObject* owner);
		~Citizen();

		void OnCollisionEnter(Collider* col);
        void OnDead();
		void GenerateDestination();

	private:
		Vector2f _Destination;
		float _MovementSpeed = 0.5f;
	};
}

