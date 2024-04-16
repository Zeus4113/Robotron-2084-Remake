#include <Core/GameObject.h>

namespace LLGP
{
	GameObject::GameObject() {
		transform = this->AddComponent<Transform>();
	}
}
