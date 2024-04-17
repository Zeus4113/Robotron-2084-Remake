#include <Core/Collider.h>
#include <iostream>

namespace LLGP {

	void Collider::Collision(Collider* otherBox) {

		if (_location->x < otherBox->_location->x + otherBox->_size.x && _location->x > otherBox->_location->x ||
			_location->y < otherBox->_location->y + otherBox->_size.y && _location->y > otherBox->_location->y)
		{
			isColliding = true;
			std::cout << "Collision Detected!" << std::endl;
		}
		else
		{
			isColliding = false;
		}

	}

}
