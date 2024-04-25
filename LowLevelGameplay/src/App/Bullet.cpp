#include "Bullet.h"
#include <Core/Collider.h>
#include <Core/Rigidbody.h>
#include <Core/Sprite.h>

namespace LLGP
{
	void Bullet::Destroy(Collider* col) 
	{
		std::cout << "Destroy" << std::endl;



		//for (int i = 0; i < m_Components.size(); i++) 
		//{
		//	m_Components[i] = nullptr;

		//	delete *(m_Components.begin() + i);
		//	m_Components.erase(m_Components.begin() + i);
		//}

		//delete this;
	}

	void Bullet::Awake()
	{
		this->AddComponent<LLGP::Rigidbody>();
		this->AddComponent<LLGP::Sprite>();

		this->GetComponent<LLGP::Rigidbody>()->SetDrag(0);
		this->GetComponent<LLGP::Rigidbody>()->SetMass(1);
		this->GetComponent<LLGP::Rigidbody>()->SetVelocity(LLGP::Vector2f(1.5, 1.5));
		this->GetComponent<LLGP::Rigidbody>()->SetSize(LLGP::Vector2f::one * 6.25f);
		this->GetComponent<LLGP::Sprite>()->SetSize(LLGP::Vector2f::one * 12.5f);

		this->GetComponent<Rigidbody>()->SetVelocity(_Direction * _Force);

		if (this->GetComponent<Collider>()) 
		{
			this->GetComponent<Collider>()->onCollision += std::bind(&Bullet::Destroy, this, std::placeholders::_1);
		}
	}
}