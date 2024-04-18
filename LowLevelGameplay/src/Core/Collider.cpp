#include <Core/Collider.h>

namespace LLGP {

	bool Collider::IsColliding(Collider* otherBox) {

		if (_location->x < otherBox->_location->x + otherBox->_size.x && _location->x > otherBox->_location->x ||
			_location->y < otherBox->_location->y + otherBox->_size.y && _location->y > otherBox->_location->y)
		{
			return true;
		}
		else
		{
			return false;
		}

	}

}
