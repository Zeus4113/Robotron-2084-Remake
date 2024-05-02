#pragma once
#include <Core/object.h>

namespace LLGP 
{
	class GameObject;

	class Component : public Object 
	{
	public:
		Component(GameObject* owner) : _GameObject(owner) {}
		virtual ~Component() = 0;

		GameObject* GetGameObject() { return _GameObject; }

		virtual void OwnerActiveChange(bool newActive) {} 

		virtual void Awake() {}

		virtual void Reset(){}

	protected:
		GameObject* _GameObject;
	};
}
