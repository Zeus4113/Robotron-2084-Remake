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

	void Rigidbody::SetVelocity(Vector2f newVelocity)
	{
		_Velocity = newVelocity;


		if (newVelocity == Vector2f::zero) 
		{
			_direction = MovementDirection::Idle;
		}


		if (_Velocity.x > 0) 
		{
			_direction = MovementDirection::Left;
		}
		else if (_Velocity.x < 0) 
		{
			_direction = MovementDirection::Right;
		}

		if (_Velocity.y > 0) 
		{
			_direction = MovementDirection::Up;
		}
		else if (_Velocity.y < 0) 
		{
			_direction = MovementDirection::Down;
		}
	}

	void Rigidbody::SetSize(Vector2f newSize) 
	{ 
		_Collider->SetSize(newSize); 
	}
}