#pragma once
#include <Core/Component.h>

namespace LLGP 
{

	class Collider;

	class Trap : public Component
	{
	public:
		Trap(GameObject* owner);
		~Trap();

		void OnCollisionEnter(Collider* col);
	};
}

