#include <Core/Collider.h>
#include <Core/GameObject.h>
#include <Core/PhysicsManager.h>

namespace LLGP {

	Collider::Collider(GameObject* owner) : Component(owner) 
	{ 
		PhysicsManager::RegisterCollider(this);
	}

	Collider::~Collider() 
	{ 
		PhysicsManager::UnregisterCollider(this); 
	}

	bool Collider::Collision(Collider* otherBox) {

		Vector2f pos1 = Vector2f(this->_GameObject->GetTransform()->position.x, this->_GameObject->GetTransform()->position.y);
		Vector2f pos2 = Vector2f(otherBox->_GameObject->GetTransform()->position.x, otherBox->_GameObject->GetTransform()->position.y);

		Vector2f aMin = pos1 - this->_size;
		Vector2f aMax = pos1 + this->_size;
		Vector2f bMin = pos2 - otherBox->GetSize();
		Vector2f bMax = pos2 + otherBox->GetSize();

		if (aMax.x >= bMin.x && aMin.x <= bMax.x && aMax.y >= bMin.y && aMin.y <= bMax.y) {

			if (!_isColliding) 
			{
				onCollisionEnter(otherBox);
				_isColliding = true;
				return true;
			}
			else 
			{
				onCollisionStay(otherBox);
				return true;
			}

		}
		else if (aMax.x <= bMin.x && aMin.x >= bMax.x || aMax.y <= bMin.y && aMin.y >= bMax.y)
		{
			if (_isColliding) 
			{
				onCollisionExit(otherBox);
				_isColliding = false;
				return false;
			}
		}

		return false;

	}

}
