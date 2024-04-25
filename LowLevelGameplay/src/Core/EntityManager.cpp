#include <Core/EntityManager.h>
#include <Core/GameObject.h>

namespace LLGP 
{
	std::vector<GameObject*> EntityManager::_Entities;

	void EntityManager::RegisterEntity(GameObject* newObject) 
	{
		_Entities.push_back(newObject);
	}

	void EntityManager::UnregisterEntity(GameObject* oldObject) 
	{
		for (int i = 0; i < _Entities.size(); ++i)
		{
			if (_Entities[i] == oldObject)
			{
				_Entities[i] = nullptr;
				delete _Entities[i];
			}
		}
	}

	void EntityManager::Awake() 
	{
		for (GameObject* o : _Entities) 
		{
			o->Awake();
		}
	}
}