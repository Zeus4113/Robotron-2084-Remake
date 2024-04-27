#include "ObjectPool.h"
#include <iostream>
#include <App/Bullet.h>
#include <App/Character.h>
#include <App/Enemy.h>
#include <App/Trap.h>
#include <App/Citizen.h>

namespace LLGP 
{

	std::vector<GameObject*> ObjectPool::_PooledObjects;
	std::vector<GameObject*> ObjectPool::_InUseObjects;

	void ObjectPool::AddObject(ObjectTypes objectType, int objectAmount)
	{
		for (int i = 0; i < objectAmount; i++)
		{
			GameObject* newObject = new GameObject();

			newObject->SetType(objectType);
			newObject->SetActive(false);

			switch (objectType)
			{
			case ObjectTypes::Bullet:
				newObject->AddComponent<Bullet>();
				newObject->SetName("Bullet");
				break;
			case ObjectTypes::Player:
				newObject->AddComponent<Character>();
				newObject->SetName("Player");
				break;
				//case ObjectTypes::Enemy:
				//	newObject->AddComponent<Enemy>();
				//	break;
				//case ObjectTypes::Trap:
				//	newObject->AddComponent<Trap>();
				//	break;
				//case ObjectTypes::Citizen:
				//	newObject->AddComponent<Citizen>();
				//	break;
			}

			_PooledObjects.push_back(newObject);

		}
	}

	void ObjectPool::ReturnObject(GameObject* objectToReturn)
	{
		for (int i = 0; i < _InUseObjects.size(); i++)
		{
			if (_InUseObjects[i] == objectToReturn)
			{
				_InUseObjects[i]->SetActive(false);
				_InUseObjects[i]->transform->position = Vector3f(0, 0, 0);
				_PooledObjects.push_back(_InUseObjects[i]);
				_InUseObjects.erase(_InUseObjects.begin() + i);

				std::cout << "Returning Object: " << _PooledObjects[_PooledObjects.size() - 1]->GetName() 
					<< " at position " << _PooledObjects[_PooledObjects.size() - 1]->GetTransform()->position.x 
					<< " " << _PooledObjects[_PooledObjects.size() - 1]->GetTransform()->position.y 
					<< std::endl;
			}
		}
	}

	GameObject* ObjectPool::GetObject(ObjectTypes objectType, Vector2f position)
	{
		for (int i = 0; i < _PooledObjects.size(); i++)
		{
			if (_PooledObjects[i] != nullptr) 
			{
				if (_PooledObjects[i]->CompareType(objectType))
				{

					_PooledObjects[i]->transform->position = Vector3f(position);
					_PooledObjects[i]->SetActive(true);
					_InUseObjects.push_back(_PooledObjects[i]);
					_PooledObjects.erase(_PooledObjects.begin() + i);

					std::cout << "Getting Object: " << _InUseObjects[_InUseObjects.size() - 1]->GetName() << " at position " << position.x << " " << position.y << std::endl;

					return _InUseObjects[_InUseObjects.size() - 1];
				}
			}
		}

		return nullptr;
	}
}
