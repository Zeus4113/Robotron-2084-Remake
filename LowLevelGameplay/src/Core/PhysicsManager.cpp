#include "PhysicsManager.h"
#include <Core/Collider.h>
#include <Core/Rigidbody.h>
#include <iostream>

namespace LLGP {

	std::vector<Collider*> PhysicsManager::_Colliders;
	std::vector<Rigidbody*> PhysicsManager::_Rigidbodies;

	void PhysicsManager::RegisterCollider(LLGP::Collider* newCollider) 
	{ 
		_Colliders.push_back(newCollider); 
	}

	void PhysicsManager::UnregisterCollider(Collider* oldCollider)
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

	void PhysicsManager::RegisterRigidbody(Rigidbody* newRigidbody) 
	{ 
		_Rigidbodies.push_back(newRigidbody); _Colliders.push_back(newRigidbody->GetCollider()); 
	}

	void PhysicsManager::UnregisterRigidbody(Rigidbody* oldRigidbody)
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

	void PhysicsManager::CheckCollisions() {

		for (int i = 0; i < _Rigidbodies.size(); i++)
		{
			for (int j = 0; j < _Colliders.size(); j++)
			{

				if (_Rigidbodies[i]->GetGameObject() != _Colliders[j]->GetGameObject()) {

					if (_Rigidbodies[i]->GetCollider()->Collision(_Colliders[j])) {
						std::cout << "Hit 2" << std::endl;

						ResolveCollision(_Colliders[j], _Rigidbodies[i]);
					}
				}
			}
		}
	}

	void PhysicsManager::UpdatePhysics() {

		for (Rigidbody* r : _Rigidbodies) {
			GameObject* obj = r->GetGameObject();
			obj->MoveObject(r->GetVelocity());
		}
	}

	void PhysicsManager::ResolveCollision(Collider* collider, Rigidbody* rigidbody) {

		if (collider->GetGameObject()->GetComponent<Rigidbody>()) {
			Rigidbody* rigidbody2 = collider->GetGameObject()->GetComponent<Rigidbody>();

			float mass1 = rigidbody->GetMass();
			float mass2 = rigidbody2->GetMass();
			float totalMass = mass1 + mass2;

			Vector2f ratioVelocty = (rigidbody->GetVelocity() + rigidbody->GetVelocity()) / totalMass;
			Vector2f velocity1 = ratioVelocty * mass1;
			Vector2f velocity2 = ratioVelocty * mass2;

			rigidbody->SetVelocity(-velocity1);
			rigidbody->SetVelocity(-velocity2);

			rigidbody->GetGameObject()->MoveObject(rigidbody->GetVelocity());
			rigidbody2->GetGameObject()->MoveObject(rigidbody2->GetVelocity());
		}
		else 
		{
			rigidbody->SetVelocity(-rigidbody->GetVelocity());

			rigidbody->GetGameObject()->MoveObject(rigidbody->GetVelocity());
		}



	}

}