#include "Citizen.h"
#include <Core/Rigidbody.h>
#include <Core/Sprite.h>
#include <Core/Collider.h>
#include <Core/GameObject.h>
#include <Core/RenderingManager.h>
#include <App/EnemyManager.h>
#include <App/ScoreManager.h>
#include <Core/Animator.h>

namespace LLGP
{
	Citizen::Citizen(GameObject* owner) : Component(owner)
	{
		// Add and Set Rigidbody Component
		owner->AddComponent<Rigidbody>();
		owner->GetComponent<Rigidbody>()->SetSize(Vector2f(25.f, 25.f) / 2.f);
		owner->GetComponent<Rigidbody>()->SetMass(1.f);

		// Add and Set Sprite Component
		owner->AddComponent<Sprite>();
		owner->GetComponent<Sprite>()->SetSize(Vector2f(25.f, 25.f));
		owner->GetComponent<LLGP::Sprite>()->SetTexture("images/CitizenSpriteSheet.png", Vector2f(3, 4));

		owner->AddComponent<Animator>();
		owner->GetComponent<Animator>()->SetPlaying(false);
		owner->GetComponent<Animator>()->SetRow(2);

		if (owner->GetComponent<Collider>())
		{
			owner->GetComponent<Collider>()->onCollisionEnter += std::bind(&Citizen::OnCollisionEnter, this, std::placeholders::_1);
		}

		EnemyManager::RegisterCitizen(this);
	}

	Citizen::~Citizen()
	{
		EnemyManager::UnregisterCitizen(this);
	}

	void Citizen::OnCollisionEnter(Collider* col)
	{
		//std::cout << this->GetGameObject()->GetName() << " is touching " << col->GetGameObject()->GetName() << std::endl;

		if (col->GetGameObject()->CompareType(ObjectTypes::Player))
		{
			this->OnDead();
		}
		else 
		{
			_Destination = EnemyManager::GetRandomPosition(false);
		}
	}

	void Citizen::OnDead() 
	{
		ObjectPool::ReturnObject(this->GetGameObject());
		ScoreManager::CitizenRescued();
	}

	void Citizen::Move(Vector2f destination) 
	{
		_Destination = destination;

		//std::cout << _Destination.x << " " << _Destination.y << std::endl;

		Vector2f norm = (_Destination - Vector2f(this->GetGameObject()->transform->position.x, this->GetGameObject()->transform->position.y)).Normalise();
		this->GetGameObject()->GetComponent<Rigidbody>()->SetVelocity(norm * _MovementSpeed);

		if (norm == Vector2f::zero)
		{
			this->GetGameObject()->GetComponent<Animator>()->SetPlaying(false);
		}
		else
		{
			this->GetGameObject()->GetComponent<Animator>()->SetPlaying(true);

			if (norm.x > 0)
			{
				this->GetGameObject()->GetComponent<Animator>()->SetRow(MovementDirection::Right);
			}
			else if (norm.x < 0)
			{
				this->GetGameObject()->GetComponent<Animator>()->SetRow(MovementDirection::Left);
			}

			if (norm.y > 0)
			{
				this->GetGameObject()->GetComponent<Animator>()->SetRow(MovementDirection::Up);
			}
			else if (norm.y < 0)
			{
				this->GetGameObject()->GetComponent<Animator>()->SetRow(MovementDirection::Down);
			}
		}
	}

	//void Citizen::InitialiseDestination() 
	//{
	//	_Destination = Vector2f(this->GetGameObject()->transform->position.x, this->GetGameObject()->transform->position.y);
	//}

	//void Citizen::CheckDestination() 
	//{
	//	//std::cout << "Position: " << this->GetGameObject()->transform->position.x << ", " << this->GetGameObject()->transform->position.y << std::endl << "Destination: " << _Destination.x << ", " << _Destination.y << std::endl;

	//	if (Vector2f(this->GetGameObject()->transform->position.x, this->GetGameObject()->transform->position.y) == _Destination)
	//	{
	//		this->GenerateDestination();
	//	}
	//}

	//void Citizen::GenerateDestination()
	//{
	//	_Destination = Vector2f(rand() % RenderingManager::GetWindow()->getSize().x, rand() % RenderingManager::GetWindow()->getSize().y);

	//	std::cout << "Movement Destination: " << _Destination.x << " " << _Destination.y << std::endl;
	//	std::cout << "Movement Position: " << this->GetGameObject()->transform->position.x << " " << this->GetGameObject()->transform->position.y << std::endl;

	//	Vector2f norm = (_Destination - Vector2f(this->GetGameObject()->transform->position.x, this->GetGameObject()->transform->position.y)).Normalise();

	//	std::cout << "Movement Value: " << norm.x << " " << norm.y << std::endl;

	//	this->GetGameObject()->GetComponent<Rigidbody>()->SetVelocity(norm * _MovementSpeed);

	//	std::cout << "Velocity: " << this->GetGameObject()->GetComponent<Rigidbody>()->GetVelocity().x << " " << this->GetGameObject()->GetComponent<Rigidbody>()->GetVelocity().y << std::endl;

	//	if (norm == Vector2f::zero)
	//	{
	//		this->GetGameObject()->GetComponent<Animator>()->SetPlaying(false);
	//	}
	//	else
	//	{
	//		this->GetGameObject()->GetComponent<Animator>()->SetPlaying(true);

	//		if (norm.x > 0)
	//		{
	//			this->GetGameObject()->GetComponent<Animator>()->SetRow(MovementDirection::Right);
	//		}
	//		else if (norm.x < 0)
	//		{
	//			this->GetGameObject()->GetComponent<Animator>()->SetRow(MovementDirection::Left);
	//		}

	//		if (norm.y > 0)
	//		{
	//			this->GetGameObject()->GetComponent<Animator>()->SetRow(MovementDirection::Up);
	//		}
	//		else if (norm.y < 0)
	//		{
	//			this->GetGameObject()->GetComponent<Animator>()->SetRow(MovementDirection::Down);
	//		}
	//	}
	//}
}