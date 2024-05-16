#include <Core/PhysicsManager.h>
#include <Core/Collider.h>
#include <Core/Rigidbody.h>
#include <iostream>

namespace LLGP {

	std::vector<Collider*> PhysicsManager::_Colliders;
	std::vector<Rigidbody*> PhysicsManager::_Rigidbodies;

	void PhysicsManager::RegisterCollider(LLGP::Collider* newCollider) 
	{ 
		_Colliders.push_back(newCollider); 
		//std::cout << "New Collider Added: " << newCollider->GetGameObject()->GetName() << std::endl;
	}

	void PhysicsManager::UnregisterCollider(Collider* oldCollider)
	{
		for (int i = 0; i < _Colliders.size(); ++i)
		{
			if (_Colliders[i] == oldCollider)
			{
				_Colliders.erase(_Colliders.begin() + i);
			}
		}
	}

	void PhysicsManager::RegisterRigidbody(Rigidbody* newRigidbody) 
	{ 
		_Rigidbodies.push_back(newRigidbody); //_Colliders.push_back(newRigidbody->GetCollider()); 
		//std::cout << "New Rigidbody Added: " << newRigidbody->GetGameObject()->GetName() << std::endl;
	}

	void PhysicsManager::UnregisterRigidbody(Rigidbody* oldRigidbody)
	{
		for (int i = 0; i < _Rigidbodies.size(); ++i)
		{
			if (_Rigidbodies[i] == oldRigidbody)
			{
				_Rigidbodies.erase(_Rigidbodies.begin() + i);
			}
		}
	}

	void PhysicsManager::CheckCollisions() {

		//for (int i = 0; i < _Rigidbodies.size(); i++)
		//{
		//	if (_Rigidbodies[i]->GetGameObject()->GetActive()) 
		//	{
		//		for (int j = 0; j < _Colliders.size(); j++)
		//		{
		//			if (_Colliders[i]->GetGameObject()->GetActive())
		//			{
		//				if (_Rigidbodies[i]->GetGameObject() != _Colliders[j]->GetGameObject()) {

		//					if (_Rigidbodies[i]->GetCollider()->Collision(_Colliders[j])) {

		//						ResolveCollision(_Colliders[i], _Colliders[j]);
		//					}
		//				}
		//			}
		//		}
		//	}
		//}

		for (int i = 0; i < _Colliders.size(); i++) 
		{
			if (_Colliders[i]->GetGameObject()->GetActive()) 
			{
				for (int j = i + 1; j < _Colliders.size(); j++) 
				{
					if (_Colliders[j]->GetGameObject()->GetActive()) 
					{
						if (_Colliders[i]->Collision(_Colliders[j]))
						{
							_Colliders[i]->SetColliding(true);
							ResolveCollision(_Colliders[i], _Colliders[j]);
						}
					}
				}
			}
		}
	}

	void PhysicsManager::InitialiseColliders() 
	{
		for (int i = 0; i < _Colliders.size(); i++)
		{
			if (_Colliders[i]->GetGameObject()->GetActive())
			{
				for (int j = i + 1; j < _Colliders.size(); j++)
				{
					if (_Colliders[j]->GetGameObject()->GetActive())
					{
						if (_Colliders[i]->Collision(_Colliders[j]))
						{
							_Colliders[i]->SetColliding(true);
						}
					}
				}
			}
		}
	}

	void PhysicsManager::UpdatePhysics() {

		for (Rigidbody* r : _Rigidbodies) 
		{
			if (r->GetGameObject()->GetActive()) 
			{
				GameObject* obj = r->GetGameObject();
				obj->MoveObject(r->GetVelocity());
				r->DampenVelocity();
			}
		}
	}

	void PhysicsManager::ResolveCollision(Collider* collider, Collider* collider2) {

		if (!collider->_isSolid || !collider2->_isSolid) return;

		if (collider == nullptr || collider2 == nullptr) return;

		Rigidbody* rigidbody = nullptr;
		Rigidbody* rigidbody2 = nullptr;

		if (collider->GetGameObject()->GetComponent<Rigidbody>()) 
		{
			rigidbody = collider->GetGameObject()->GetComponent<Rigidbody>();
		}

		if (collider2->GetGameObject()->GetComponent<Rigidbody>()) 
		{
			rigidbody2 = collider2->GetGameObject()->GetComponent<Rigidbody>();
		}

		//std::cout << "Collision: " << collider->GetGameObject()->GetName() << " hit " << collider2->GetGameObject()->GetName() << std::endl;

		if(rigidbody != nullptr && rigidbody2 != nullptr)
		{
			float mass1 = rigidbody->GetMass();
			float mass2 = rigidbody2->GetMass();
			float totalMass = mass1 + mass2;

			Vector2f ratioVelocty = (rigidbody->GetVelocity() + rigidbody2->GetVelocity()) / totalMass;
			Vector2f velocity1 = ratioVelocty * mass1;
			Vector2f velocity2 = ratioVelocty * mass2;

			rigidbody->SetVelocity(-velocity1);
			rigidbody2->SetVelocity(velocity2);

			rigidbody->GetGameObject()->MoveObject(rigidbody->GetVelocity());
			rigidbody2->GetGameObject()->MoveObject(rigidbody2->GetVelocity());
		}
		else if(rigidbody != nullptr && rigidbody2 == nullptr)
		{
			rigidbody->SetVelocity(-rigidbody->GetVelocity());

			rigidbody->GetGameObject()->MoveObject(rigidbody->GetVelocity());
		}
		else if (rigidbody == nullptr && rigidbody2 != nullptr)
		{
			rigidbody2->SetVelocity(-rigidbody2->GetVelocity());

			rigidbody2->GetGameObject()->MoveObject(rigidbody2->GetVelocity());
		}



	}

}