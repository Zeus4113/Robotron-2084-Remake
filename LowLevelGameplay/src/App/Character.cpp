#include <App/Character.h>
#include <Core/input_manager.h>
#include <Core/GameObject.h>

namespace LLGP {

	void Character::HandleMovement(Vector2f movementValue)
	{
		Component::GetGameObject()->MoveObject(movementValue * _MovementSpeed);

		//std::cout << "Movement: " << movementValue.x << " " << movementValue.y << std::endl;
	}

	void Character::HandleShooting(Vector2f shootingValue) {

		//std::cout << "Shooting Vector: " << shootingValue.x << " " << shootingValue.y << std::endl;
	}

	void Character::OnShoot(int input) {
		//std::cout << "Shot fired!" << std::endl;
	}

	void Character::Awake() 
	{
		InputManager::onMovementPerformed += std::bind(&Character::HandleMovement, this, std::placeholders::_1);
		InputManager::onShootingPerformed += std::bind(&Character::HandleShooting, this, std::placeholders::_1);
		InputManager::onShoot += std::bind(&Character::OnShoot, this, std::placeholders::_1);
	}
}
