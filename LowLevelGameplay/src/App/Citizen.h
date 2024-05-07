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
		void Move(Vector2f destination);

		Vector2f GetDestination() { return _Destination; }

	private:
		Vector2f _Destination;
		float _MovementSpeed = 0.5f;
	};
}

