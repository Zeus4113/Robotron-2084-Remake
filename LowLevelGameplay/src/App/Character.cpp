#include <App/Character.h>
#include <Core/input_manager.h>
#include <Core/GameObject.h>
#include <Core/Rigidbody.h>
#include <App/Bullet.h>

namespace LLGP {

	void Character::HandleMovement(Vector2f movementValue)
	{
		//Component::GetGameObject()->MoveObject(movementValue * _MovementSpeed);
		Component::GetGameObject()->GetComponent<Rigidbody>()->SetVelocity(movementValue * 3);
		//std::cout << "Movement: " << movementValue.x << " " << movementValue.y << std::endl;
	}

	void Character::HandleShooting(Vector2f shootingValue) {

		//std::cout << "Shooting Vector: " << shootingValue.x << " " << shootingValue.y << std::endl;
		_AimVector = shootingValue;
	}

	void Character::OnShoot(int input) {
		
		Bullet* newBullet = new Bullet(_AimVector, 10.f);
		newBullet->transform->position = (this->GetGameObject()->transform->position + Vector3f(_AimVector.x * 15, _AimVector.y * 15));
		newBullet->Awake();
		std::cout << "Hit" << std::endl;
	}

	void Character::Awake() 
	{
		InputManager::onMovementPerformed += std::bind(&Character::HandleMovement, this, std::placeholders::_1);
		InputManager::onMovementCancelled += std::bind(&Character::HandleMovement, this, std::placeholders::_1);
		InputManager::onShootingPerformed += std::bind(&Character::HandleShooting, this, std::placeholders::_1);
		InputManager::onShoot += std::bind(&Character::OnShoot, this, std::placeholders::_1);
	}
}
