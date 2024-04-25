#pragma once
#include <Core/GameObject.h>

namespace LLGP 
{
	class Collider;

	class Bullet : public GameObject
	{
	public:
		Bullet(Vector2f direction, float force) : _Force(force), _Direction(direction){}
		~Bullet() {}
		 
		void Awake() override;
		void Destroy(Collider* col);

	private:
		float _Force;
		Vector2f _Direction;
	};
}


