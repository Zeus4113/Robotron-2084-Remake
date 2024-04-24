#pragma once
#include <Core/GameObject.h>
#include <vector>


namespace LLGP{

	class Collider;
	class Rigidbody;

	static class PhysicsManager {
	public:

		static void CheckCollisions();
		static void UpdatePhysics();
		static void ResolveCollision(Collider* collider, Rigidbody* rigidbody);

		static void RegisterCollider(Collider* newCollider);
		static void UnregisterCollider(Collider* oldCollider);

		static void RegisterRigidbody(Rigidbody* newRigidbody);
		static void UnregisterRigidbody(Rigidbody* oldRigidbody);

	private:

		static std::vector<Collider*> _Colliders;
		static std::vector<Rigidbody*> _Rigidbodies;
	};

}