#pragma once
#include <Core/GameObject.h>
#include <Core/vector2.h>
#include <Core/ObjectTypes.h>

namespace LLGP 
{

	static class ObjectPool
	{
	public:
		ObjectPool() {}
		~ObjectPool() {}

		static void AddObject(ObjectTypes objectType, int objectAmount);

		static void ReturnObject(GameObject* objectToReturn);

		static GameObject* GetObject(ObjectTypes objectType, Vector2f position);

	private:
		static std::vector<GameObject*> _PooledObjects;
		static std::vector<GameObject*> _InUseObjects;
	};
}

