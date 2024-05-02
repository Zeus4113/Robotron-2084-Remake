#pragma once
#include <Core/Component.h>
#include <Core/vector2.h>

namespace LLGP {

	class Collider : public Component {

	public:
		Collider() = default;
		Collider(GameObject* owner, Vector2f* location, Vector2f size) : Component(owner), _size(size), _location(location) {}
		~Collider() = default;

		bool IsColliding(Collider* otherBox);

<<<<<<< Updated upstream
	protected:
=======
		bool Collision(Collider* otherBox);
		void SetSize(Vector2f size) { this->_size = size; }
		Vector2f GetSize() { return _size; }
		void SetColliding(bool isTrue) { _isColliding = isTrue; }
		void Reset() override;

		Event<Collider*> onCollisionEnter;
		Event<Collider*> onCollisionStay;
		Event<Collider*> onCollisionExit;

	private:
		bool _isColliding = false;
>>>>>>> Stashed changes
		Vector2f _size;
		Vector2f* _location;
	};
}

