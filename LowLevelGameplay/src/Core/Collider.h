#pragma once
#include <Core/Component.h>
#include <Core/vector2.h>

namespace LLGP {

	class Collider : public Component {

	public:
		Collider() = default;
		Collider(GameObject* owner, Vector2f* location, Vector2f size) : Component(owner), _size(size), _location(location) { isColliding = false; }
		~Collider() { }

		void Collision(Collider* otherBox);

		void SetOwner(GameObject* owner) { _GameObject = owner; }
		void SetLocation(Vector2f* location) { this->_location = location; }
		void SetSize(Vector2f size) { this->_size = size; }

	protected:
		Vector2f _size;
		Vector2f* _location;
		bool isColliding = false;
	};
}

