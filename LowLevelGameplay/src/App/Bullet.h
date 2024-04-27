#pragma once
#include <Core/Component.h>
#include <Core/vector2.h>

namespace LLGP 
{
	class Collider;

	class Bullet : public Component
	{
	public:
		Bullet(GameObject* owner);
		~Bullet() = default;
		 
		void Init(Vector2f direction, float force);
		void Destroy(Collider* col);

	private:
		float _Force;
		Vector2f _Direction;
	};
}


