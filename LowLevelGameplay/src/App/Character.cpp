#include <App/Character.h>
#include <App/Bullet.h>

#include <Core/input_manager.h>
#include <Core/GameObject.h>
#include <Core/Rigidbody.h>
#include <Core/Sprite.h>
#include <Core/ObjectPool.h>


namespace LLGP {

	Character::Character(GameObject* owner) : Component(owner)
	{
		// Add and Set Rigidbody Component
		this->GetGameObject()->AddComponent<LLGP::Rigidbody>();
		this->GetGameObject()->GetComponent<LLGP::Rigidbody>()->SetSize(Vector2f(25.f, 25.f) / 2.f);
		this->GetGameObject()->GetComponent<LLGP::Rigidbody>()->SetMass(1.f);

		// Add and Set Sprite Component
		this->GetGameObject()->AddComponent<LLGP::Sprite>();
		this->GetGameObject()->GetComponent<LLGP::Sprite>()->SetSize(Vector2f(25.f, 25.f));
	}
	
	void Character::HandleMovement(Vector2f movementValue)
	{
		if (this->GetGameObject()->GetActive()) 
		{
			Component::GetGameObject()->GetComponent<Rigidbody>()->SetVelocity(movementValue * 3);
		}
	}

	void Character::HandleShooting(Vector2f shootingValue) 
	{
		if (this->GetGameObject()->GetActive()) 
		{
			_AimVector = shootingValue;
		}
	}

	void Character::OnShoot(int input) {
		
		if (this->GetGameObject()->GetActive()) 
		{
			GameObject* newBullet = ObjectPool::GetObject(ObjectTypes::Bullet, Vector2f(
				(this->GetGameObject()->transform->position + Vector3f(_AimVector.x * 25, _AimVector.y * 25)).x,
				(this->GetGameObject()->transform->position + Vector3f(_AimVector.x * 25, _AimVector.y * 25)).y
				));

			Bullet* bulletComponent = newBullet->GetComponent<Bullet>();

			bulletComponent->Init(_AimVector, 10.f);
		}
	}

	void Character::Awake() 
	{
		InputManager::onMovementPerformed += std::bind(&Character::HandleMovement, this, std::placeholders::_1);
		InputManager::onMovementCancelled += std::bind(&Character::HandleMovement, this, std::placeholders::_1);
		InputManager::onShootingPerformed += std::bind(&Character::HandleShooting, this, std::placeholders::_1);
		InputManager::onShoot += std::bind(&Character::OnShoot, this, std::placeholders::_1);
	}
}
