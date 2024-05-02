#include <Core/Collider.h>

namespace LLGP {

	bool Collider::IsColliding(Collider* otherBox) {

<<<<<<< Updated upstream
		if (_location->x < otherBox->_location->x + otherBox->_size.x && _location->x > otherBox->_location->x ||
			_location->y < otherBox->_location->y + otherBox->_size.y && _location->y > otherBox->_location->y)
=======
	Collider::~Collider() 
	{ 
		PhysicsManager::UnregisterCollider(this); 
	}

	void Collider::Reset() 
	{
		_inContactColliders.clear();
	}

	bool Collider::Collision(Collider* otherBox) {

		Vector2f pos1 = Vector2f(this->_GameObject->GetTransform()->position.x, this->_GameObject->GetTransform()->position.y);
		Vector2f pos2 = Vector2f(otherBox->_GameObject->GetTransform()->position.x, otherBox->_GameObject->GetTransform()->position.y);

		Vector2f aMin = pos1 - this->_size;
		Vector2f aMax = pos1 + this->_size;
		Vector2f bMin = pos2 - otherBox->GetSize();
		Vector2f bMax = pos2 + otherBox->GetSize();

		if (aMax.x >= bMin.x && aMin.x <= bMax.x && aMax.y >= bMin.y && aMin.y <= bMax.y) {

			if (std::find(_inContactColliders.begin(), _inContactColliders.end(), otherBox) == _inContactColliders.end())
			{
				_inContactColliders.push_back(otherBox);
				onCollisionEnter(otherBox);
				otherBox->onCollisionEnter(this);
				_isColliding = true;
				return true;
			}
			else if(std::find(_inContactColliders.begin(), _inContactColliders.end(), otherBox) != _inContactColliders.end())
			{
				onCollisionStay(otherBox);
				otherBox->onCollisionStay(this);
				return true;
			}

		}
		else if (aMax.x <= bMin.x && aMin.x >= bMax.x || aMax.y <= bMin.y && aMin.y >= bMax.y)
>>>>>>> Stashed changes
		{
			return true;
		}
		else
		{
			return false;
		}

	}

}
