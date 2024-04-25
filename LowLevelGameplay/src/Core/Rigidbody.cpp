#include <Core/Rigidbody.h>
#include <Core/Collider.h>
#include <Core/PhysicsManager.h>

namespace LLGP {

	Rigidbody::Rigidbody(GameObject* owner) : Component(owner)
	{ 
		_Collider = _GameObject->AddComponent<Collider>();
		_Mass = 0.1f; 
		_Drag = 0.025f;
		_Velocity = Vector2f::zero; 

		PhysicsManager::RegisterRigidbody(this); 
	}

	Rigidbody::~Rigidbody() 
	{ 
		PhysicsManager::UnregisterRigidbody(this); 
		//_GameObject->RemoveComponent<Collider>();
	}

	void Rigidbody::SetSize(Vector2f newSize) 
	{ 
		_Collider->SetSize(newSize); 
	}
}