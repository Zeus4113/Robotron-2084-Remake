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
<<<<<<< Updated upstream
		InputManager::onMovementPerformed += std::bind(&Character::ReadInput, this, std::placeholders::_1);
=======
		InputManager::onMovementPerformed += std::bind(&Character::HandleMovement, this, std::placeholders::_1);
		InputManager::onMovementCancelled += std::bind(&Character::HandleMovement, this, std::placeholders::_1);
		InputManager::onShootingPerformed += std::bind(&Character::HandleShooting, this, std::placeholders::_1);
		InputManager::onShoot += std::bind(&Character::OnShoot, this, std::placeholders::_1);
	}

	void Character::OnCollisionEnter(Collider* col)
	{
		//std::cout << this->GetGameObject()->GetName() << " is touching " << col->GetGameObject()->GetName() << " (ENTER)" << std::endl;

		//if (col->GetGameObject()->CompareType(ObjectTypes::Citizen)) 
		//{
		//	ObjectPool::ReturnObject(col->GetGameObject());
		//	std::cout << "Citizen Returned" << std::endl;
		//}
	}

	void Character::OnCollisionExit(Collider* col) 
	{
		//std::cout << this->GetGameObject()->GetName() << " is touching " << col->GetGameObject()->GetName() << " (EXIT)" << std::endl;
	}

	void Character::OnCollisionStay(Collider* col)
	{
		//std::cout << this->GetGameObject()->GetName() << " is touching " << col->GetGameObject()->GetName() << " (STAY)" << std::endl;
	}
	void Character::OnDead()
	{
		this->GetGameObject()->GetComponent<Rigidbody>()->SetVelocity(Vector2f(0, 0));
		ObjectPool::ReturnObject(this->GetGameObject());
>>>>>>> Stashed changes
	}
}
