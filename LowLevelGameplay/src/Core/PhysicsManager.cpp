#include "PhysicsManager.h"

namespace LLGP {

	void PhysicsManager::CheckCollisions() {

		for(Collider* c : _Colliders) 
		{
			for (Collider* x : _Colliders)
			{
				if (x != c) {
					c->Collision(x);
				}
			}
		}

	}

}