#pragma once
#include "object.h"

namespace LLGP 
{
	class GameObject;

	class Component : public Object 
	{
	public:
		Component(GameObject* owner) : _GameObject(owner) {}
		virtual ~Component() {}

		GameObject* GetGameObject() { return _GameObject; }

		virtual void OwnerActiveChange(bool newActive) {}  

	protected:
		GameObject* _GameObject;
	};
}
