#pragma once
#include <Core/Component.h>
#include <Core/vector2.h>
#include <Core/Event.h>

namespace LLGP {

	class Collider : public Component {

	public:

		Collider(GameObject* owner);
		~Collider();

		bool Collision(Collider* otherBox);
		void SetSize(Vector2f size) { this->_size = size; }
		Vector2f GetSize() { return _size; }
		void SetColliding(bool isTrue) { _isColliding = isTrue; }

		Event<Collider*> onCollisionEnter;
		Event<Collider*> onCollisionStay;
		Event<Collider*> onCollisionExit;

	private:
		bool _isColliding = false;
		Vector2f _size;
		Vector2f offset;
		std::vector<Collider*> _inContactColliders;
	};
}

