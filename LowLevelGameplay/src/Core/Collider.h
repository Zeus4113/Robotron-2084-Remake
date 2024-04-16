#pragma once
#include <Core/Component.h>
#include <Core/vector2.h>

namespace LLGP {

	class Collider :Component {

	public:
		Collider() = default;
		Collider(GameObject* owner, Vector2f* location, Vector2f size) : Component(owner), _size(size), _location(location) {}
		virtual ~Collider() = 0;

		void Collision(Collider* otherBox);

	protected:
		Vector2f _size;
		Vector2f* _location;
		bool isColliding;
	};
}

