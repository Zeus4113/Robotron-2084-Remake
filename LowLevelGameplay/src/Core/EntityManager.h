#pragma once
#include <vector>

namespace LLGP 
{
	class GameObject;

	static class EntityManager
	{
	public:
		EntityManager() {}
		~EntityManager() {}
		
		static void RegisterEntity(GameObject* newObject);
		static void UnregisterEntity(GameObject* oldObject);

		static void Awake();
	private:
		static std::vector<GameObject*> _Entities;
	};
}


