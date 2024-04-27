#include "Bullet.h"
#include <Core/Collider.h>
#include <Core/Rigidbody.h>
#include <Core/Sprite.h>
#include <Core/GameObject.h>
#include <Core/ObjectPool.h>

namespace LLGP
{
	Bullet::Bullet(GameObject* owner) : Component(owner)
	{
		owner->AddComponent<LLGP::Rigidbody>();
		owner->AddComponent<LLGP::Sprite>();

		owner->GetComponent<LLGP::Rigidbody>()->SetDrag(0);
		owner->GetComponent<LLGP::Rigidbody>()->SetMass(1);
		owner->GetComponent<LLGP::Rigidbody>()->SetSize(LLGP::Vector2f::one * 6.25f);
		owner->GetComponent<LLGP::Sprite>()->SetSize(LLGP::Vector2f::one * 12.5f);

		if (owner->GetComponent<Collider>())
		{
			owner->GetComponent<Collider>()->onCollision += std::bind(&Bullet::Destroy, this, std::placeholders::_1);
		}
	}

	void Bullet::Init(Vector2f direction, float force)
	{
		this->GetGameObject()->GetComponent<Rigidbody>()->SetVelocity(direction * force);
		std::cout << direction.x << " " << direction.y << std::endl;
	}

	void Bullet::Destroy(Collider* col)
	{
		this->GetGameObject()->GetComponent<Rigidbody>()->SetVelocity(Vector2f(0,0));
		ObjectPool::ReturnObject(this->GetGameObject());
		
	}

}