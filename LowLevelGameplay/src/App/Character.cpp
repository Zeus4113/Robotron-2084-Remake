#include <App/Character.h>
#include <Core/input_manager.h>
#include <Core/GameObject.h>

namespace LLGP {

	void Character::ReadInput(Vector2f movementValue)
	{
		Component::GetGameObject()->transform->position.x += movementValue.x * movementSpeed;
		Component::GetGameObject()->transform->position.y -= movementValue.y * movementSpeed;
	}

	void Character::Awake() 
	{
		InputManager::onMovementPerformed += std::bind(&Character::ReadInput, this, std::placeholders::_1);
	}
}
