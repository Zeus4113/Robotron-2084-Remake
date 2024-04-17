#pragma once
#include "Core/Collider.h"
#include "vector"

namespace LLGP {

	static class PhysicsManager {
	public:
		PhysicsManager() {}
		~PhysicsManager() {}

		void CheckCollisions();
		void RegisterCollider(Collider* newCollider) { _Colliders.push_back(newCollider); }
		void UnregisterCollider(Collider* oldCollider)
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

	private:

		std::vector<Collider*> _Colliders;
	};

}