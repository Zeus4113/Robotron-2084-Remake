#include "PhysicsManager.h"
#include <iostream>

namespace LLGP {

	std::vector<Collider*> PhysicsManager::_Colliders;

	void PhysicsManager::CheckCollisions() {

		for (int i = 0; i < _Colliders.size() - 1; i++) 
		{
			for (int j = i+1; j < _Colliders.size(); j++) 
			{
				std::cout << _Colliders[i]->Collision(_Colliders[j]) << std::endl;
			}
		}

	}

}