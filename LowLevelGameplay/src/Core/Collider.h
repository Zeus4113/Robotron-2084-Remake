#pragma once
#include <Core/Component.h>
#include <Core/vector2.h>

namespace LLGP {

	class Collider : public Component {

	public:

		Collider(GameObject* owner);
		~Collider();

		bool Collision(Collider* otherBox);
		void SetSize(Vector2f size) { this->_size = size; }
		Vector2f GetSize() { return _size; }

	private:

		Vector2f _size;
		Vector2f offset;
	};
}

