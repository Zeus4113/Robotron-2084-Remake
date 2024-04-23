#pragma once
#include "Core/Collider.h"
#include <Core/Rigidbody.h>
#include <Core/GameObject.h>
#include <vector>

namespace LLGP{

	static class PhysicsManager {
	public:

		static void CheckCollisions();
		static void UpdatePhysics();
		static void ResolveCollision(Collider* collider, Rigidbody* rigidbody);

		static void RegisterCollider(Collider* newCollider) { _Colliders.push_back(newCollider); }
		static void UnregisterCollider(Collider* oldCollider)
		{	
			for (int i = 0; i < _Colliders.size(); ++i)
			{
				if (_Colliders[i] == oldCollider)
				{
					_Colliders[i] = nullptr;
					delete _Colliders[i];
				}
			}
		}

		static void RegisterRigidbody(Rigidbody* newRigidbody) { _Rigidbodies.push_back(newRigidbody); _Colliders.push_back(newRigidbody->GetCollider()); }
		static void UnregisterRigidbody(Rigidbody* oldRigidbody)
		{
			for (int i = 0; i < _Rigidbodies.size(); ++i)
			{
				if (_Rigidbodies[i] == oldRigidbody)
				{
					_Rigidbodies[i] = nullptr;
					delete _Rigidbodies[i];
				}
			}
		}

	private:

		static std::vector<Collider*> _Colliders;
		static std::vector<Rigidbody*> _Rigidbodies;
	};

}