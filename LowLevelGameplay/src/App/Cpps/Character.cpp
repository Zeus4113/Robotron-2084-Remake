#include <App/Character.h>
#include <App/Bullet.h>

#include <Core/input_manager.h>
#include <Core/GameObject.h>
#include <Core/Rigidbody.h>
#include <Core/Collider.h>
#include <Core/Sprite.h>
#include <Core/ObjectPool.h>
#include<Core/Event.h>
#include <Core/Animator.h>


namespace LLGP {

	Character::Character(GameObject* owner) : Component(owner)
	{
		// Add and Set Rigidbody Component
		owner->AddComponent<LLGP::Rigidbody>();
		owner->GetComponent<LLGP::Rigidbody>()->SetSize(Vector2f(40.f, 40.f) / 3.f);
		owner->GetComponent<LLGP::Rigidbody>()->SetMass(1.f);

		// Add and Set Sprite Component
		owner->AddComponent<LLGP::Sprite>();
		owner->GetComponent<LLGP::Sprite>()->SetSize(Vector2f(40.f, 40.f));
		owner->GetComponent<LLGP::Sprite>()->SetTexture("images/Player.png", Vector2f(3, 4));

		owner->AddComponent<Animator>();
		owner->GetComponent<Animator>()->SetPlaying(false);
		owner->GetComponent<Animator>()->SetRow(2);

		// Bind Collider Event
		if (owner->GetComponent<Collider>())
		{
			owner->GetComponent<Collider>()->onCollisionEnter += std::bind(&Character::OnCollisionEnter, this, std::placeholders::_1);
			owner->GetComponent<Collider>()->onCollisionExit += std::bind(&Character::OnCollisionExit, this, std::placeholders::_1);
			owner->GetComponent<Collider>()->onCollisionStay += std::bind(&Character::OnCollisionStay, this, std::placeholders::_1);
		}
	}
	
	void Character::HandleMovement(Vector2f movementValue)
	{
		if (this->GetGameObject()->GetActive()) 
		{
			//Vector2f norm = movementValue.Normalise();

			Component::GetGameObject()->GetComponent<Rigidbody>()->SetVelocity(movementValue * 3);

			if (movementValue == Vector2f::zero) 
			{
				this->GetGameObject()->GetComponent<Animator>()->SetPlaying(false);
			}
			else 
			{
				this->GetGameObject()->GetComponent<Animator>()->SetPlaying(true);

				if (movementValue.x > 0) 
				{
					this->GetGameObject()->GetComponent<Animator>()->SetRow(MovementDirection::Right);
				}
				else if (movementValue.x < 0) 
				{
					this->GetGameObject()->GetComponent<Animator>()->SetRow(MovementDirection::Left);
				}

				if (movementValue.y > 0)
				{
					this->GetGameObject()->GetComponent<Animator>()->SetRow(MovementDirection::Up);
				}
				else if (movementValue.y < 0)
				{
					this->GetGameObject()->GetComponent<Animator>()->SetRow(MovementDirection::Down);
				}
			}
		}
	}

	void Character::HandleShooting(Vector2f shootingValue) 
	{
		if (this->GetGameObject()->GetActive()) 
		{
			//Vector2f norm = shootingValue.Normalise();
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

			if (newBullet != nullptr) 
			{
				Bullet* bulletComponent = newBullet->GetComponent<Bullet>();

				bulletComponent->Init(_AimVector, 10.f);
			}
		}
	}

	void Character::Awake() 
	{
		InputManager::onMovementPerformed += std::bind(&Character::HandleMovement, this, std::placeholders::_1);
		InputManager::onMovementCancelled += std::bind(&Character::HandleMovement, this, std::placeholders::_1);
		InputManager::onShootingPerformed += std::bind(&Character::HandleShooting, this, std::placeholders::_1);
		InputManager::onShoot += std::bind(&Character::OnShoot, this, std::placeholders::_1);
	}

	void Character::OnCollisionEnter(Collider* col)
	{
		std::cout << this->GetGameObject()->GetName() << " is touching " << col->GetGameObject()->GetName() << " (ENTER)" << std::endl;

		if (col->GetGameObject()->CompareType(ObjectTypes::Trap)) 
		{
			this->OnDead();
		}
		else if (col->GetGameObject()->CompareType(ObjectTypes::Enemy))
		{
			this->OnDead();
		}
		else if (col->GetGameObject()->CompareType(ObjectTypes::EnemyHulk))
		{
			this->OnDead();
		}

	}

	void Character::OnCollisionExit(Collider* col) 
	{
		std::cout << this->GetGameObject()->GetName() << " is touching " << col->GetGameObject()->GetName() << " (EXIT)" << std::endl;
	}

	void Character::OnCollisionStay(Collider* col)
	{
		//std::cout << this->GetGameObject()->GetName() << " is touching " << col->GetGameObject()->GetName() << " (STAY)" << std::endl;
	}
	void Character::OnDead()
	{
		this->GetGameObject()->GetComponent<Rigidbody>()->SetVelocity(Vector2f(0, 0));
		ObjectPool::ReturnObject(this->GetGameObject());
		onPlayerDead.Invoke(1);
	}
}
