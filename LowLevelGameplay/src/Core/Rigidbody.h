#pragma once
#include <Core/Component.h>
#include <Core/vector2.h>

namespace LLGP {

	class Collider;

	class Rigidbody : public Component {
	public:
		Rigidbody(GameObject* owner) : Component(owner), _Collider(owner) { _Mass = 0.f; _Velocity = Vector2f::zero; PhysicsManager::RegisterRigidbody(this); }
		~Rigidbody() { PhysicsManager::UnregisterRigidbody(this); }
		
		void SetVelocity(Vector2f newVelocity) { _Velocity = newVelocity; }
		Vector2f GetVelocity() { return _Velocity;  }

		void SetMass(float newMass) { _Mass = newMass; }
		float GetMass() { return _Mass; }

		void SetSize(Vector2f newSize) { _Collider.SetSize(newSize); }

		Collider* GetCollider() { return &_Collider; }

	private:
		Vector2f _Velocity;
		float _Mass;
		Collider _Collider;
	};

}
