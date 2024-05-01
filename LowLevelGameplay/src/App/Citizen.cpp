#include "Citizen.h"
#include <Core/Rigidbody.h>
#include <Core/Sprite.h>
#include <Core/Collider.h>
#include <Core/GameObject.h>
#include <Core/RenderingManager.h>
#include <App/EnemyManager.h>

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
		owner->GetComponent<Sprite>()->SetColor(sf::Color::Green);

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
		GameObject* go = col->GetGameObject();

		if (go->CompareType(ObjectTypes::Player)) 
		{
			ObjectPool::ReturnObject(this->GetGameObject());
		}
	}

	void Citizen::GenerateDestination()
	{
		_Destination = Vector2f(rand() % RenderingManager::GetWindow()->getSize().x, rand() % RenderingManager::GetWindow()->getSize().y);

		Vector2f norm = (_Destination - Vector2f(this->GetGameObject()->transform->position.x, this->GetGameObject()->transform->position.y)).Normalise();

		this->GetGameObject()->GetComponent<Rigidbody>()->SetVelocity(norm * _MovementSpeed);
	}
}