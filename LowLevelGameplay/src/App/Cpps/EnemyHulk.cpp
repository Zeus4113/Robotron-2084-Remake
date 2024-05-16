#include <App/EnemyHulk.h>
#include<Core/Rigidbody.h>
#include<Core/Sprite.h>
#include <Core/Collider.h>
#include<Core/GameObject.h>
#include<Core/Event.h>
#include <Core/ObjectPool.h>
#include <App/EnemyManager.h>
#include <App/ScoreManager.h>
#include <Core/Animator.h>

namespace LLGP
{
	EnemyHulk::EnemyHulk(GameObject* owner) : Component(owner)
	{

		// Add and Set Rigidbody Component
		owner->AddComponent<LLGP::Rigidbody>();
		owner->GetComponent<LLGP::Rigidbody>()->SetSize(Vector2f(50.f, 50.f) / 3.);
		owner->GetComponent<LLGP::Rigidbody>()->SetMass(1.f);

		// Add and Set Sprite Component
		owner->AddComponent<LLGP::Sprite>();
		owner->GetComponent<LLGP::Sprite>()->SetSize(Vector2f(50.f, 50.f));
		owner->GetComponent<LLGP::Sprite>()->SetTexture("images/EnemyHulk.png", Vector2f(3, 3));

		owner->AddComponent<Animator>();
		owner->GetComponent<Animator>()->SetPlaying(true);

		if (owner->GetComponent<Collider>())
		{
			owner->GetComponent<Collider>()->onCollisionEnter += std::bind(&EnemyHulk::OnCollisionEnter, this, std::placeholders::_1);
		}
	}

	EnemyHulk::~EnemyHulk()
	{

	}

	void EnemyHulk::Move(Vector2f citizenPos)
	{

		Vector2f direction = Vector2f(
			citizenPos.x - this->GetGameObject()->transform->position.x,
			citizenPos.y - this->GetGameObject()->transform->position.y
		);

		Vector2f norm = direction.Normalise();
		this->GetGameObject()->GetComponent<Rigidbody>()->SetVelocity(Vector2f(norm.x, norm.y) * _MovementSpeed);

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
				this->GetGameObject()->GetComponent<Animator>()->SetRow(MovementDirection::Up);
			}
		}
	}

	void EnemyHulk::OnCollisionEnter(Collider* col)
	{

	}

	void EnemyHulk::OnDead()
	{
		this->GetGameObject()->GetComponent<Rigidbody>()->SetVelocity(Vector2f(0, 0));
		ObjectPool::ReturnObject(this->GetGameObject());
		//ScoreManager::EnemyKilled();
		OnEnemyDead.Invoke(1);
	}

}