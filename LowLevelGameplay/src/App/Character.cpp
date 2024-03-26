#include <App/Character.h>
#include <Core/input_manager.h>

namespace LLGP {

	void Character::HandleMovement(Vector2f movementValue)
	{
		std::cout << "Movement: " << movementValue.x << " " << movementValue.y << std::endl;
	}

	void Character::Awake() 
	{
		InputManager::onMovementPerformed += std::bind(&Character::HandleMovement, this, std::placeholders::_1);
	}
}
