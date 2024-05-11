#include <App/Trap.h>
#include <Core/GameObject.h>
#include <Core/Sprite.h>
#include <Core/Collider.h>
#include <Core/Event.h>

namespace LLGP 
{
	Trap::Trap(GameObject* owner) : Component(owner)
	{
		// Add and Set Rigidbody Component
		owner->AddComponent<LLGP::Collider>();
		owner->GetComponent<LLGP::Collider>()->SetSize(Vector2f(25.f, 25.f) / 2.f);

		// Add and Set Sprite Component
		owner->AddComponent<LLGP::Sprite>();
		owner->GetComponent<LLGP::Sprite>()->SetSize(Vector2f(25.f, 25.f));
		owner->GetComponent<LLGP::Sprite>()->SetColor(sf::Color::Yellow);

		if (owner->GetComponent<Collider>())
		{
			owner->GetComponent<Collider>()->onCollisionEnter += std::bind(&Trap::OnCollisionEnter, this, std::placeholders::_1);
		}
	}

	Trap::~Trap()
	{

	}

	void Trap::OnCollisionEnter(Collider* col)
	{
		//std::cout << this->GetGameObject()->GetName() << " is touching " << col->GetGameObject()->GetName() << std::endl;

		//GameObject* go = col->GetGameObject();

		//if (go->CompareType(ObjectTypes::Player))
		//{
		//	go->GetComponent<Character>()->OnDead();
		//}

		//if (go->CompareType(ObjectTypes::Enemy)) 
		//{
		//	go->GetComponent<Enemy>()->OnDead();
		//}
	}
}