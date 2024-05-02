#include "ObjectPool.h"
#include <iostream>
#include <Core/ObjectTypes.h>
#include <Core/Collider.h>

namespace LLGP 
{

	std::vector<GameObject*> ObjectPool::_PooledObjects;
	std::vector<GameObject*> ObjectPool::_InUseObjects;

	GameObject* ObjectPool::AddObject(ObjectTypes objectType, int objectAmount)
	{
		GameObject* newObject = new GameObject();

		for (int i = 0; i < objectAmount; i++)
		{

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

			case ObjectTypes::Enemy:
				newObject->AddComponent<Enemy>();
				newObject->SetName("Enemy");
				break;

			case ObjectTypes::Trap:
				newObject->AddComponent<Trap>();
				newObject->SetName("Trap");
				break;
 
			case ObjectTypes::Citizen:
				newObject->AddComponent<Citizen>();
				newObject->SetName("Citizen");
				break;
			}

			_PooledObjects.push_back(newObject);
		
		}

		return newObject;
	}

	void ObjectPool::ReturnObject(GameObject* objectToReturn)
	{
		for (int i = 0; i < _InUseObjects.size(); i++)
		{
			if (_InUseObjects[i] == objectToReturn)
			{
				_InUseObjects[i]->SetActive(false);
				_InUseObjects[i]->GetComponent<Collider>()->Reset();
				_InUseObjects[i]->transform->position = Vector3f(0, 0, 0);
				_PooledObjects.push_back(_InUseObjects[i]);
				_InUseObjects.erase(_InUseObjects.begin() + i);

				std::cout << "Returning Object: " << _PooledObjects.size() << " " << _InUseObjects.size() << std::endl;

				/*std::cout << "Returning Object: " << _PooledObjects[_PooledObjects.size() - 1]->GetName() 
					<< " at position " << _PooledObjects[_PooledObjects.size() - 1]->GetTransform()->position.x 
					<< " " << _PooledObjects[_PooledObjects.size() - 1]->GetTransform()->position.y 
					<< std::endl;*/
			}
		}
	}

	void ObjectPool::ReturnAllObjects()
	{
		for (int i = 0; i < _InUseObjects.size(); i++) 
		{
			_InUseObjects[i]->SetActive(false);
			_InUseObjects[i]->GetComponent<Collider>()->Reset();
			_InUseObjects[i]->transform->position = Vector3f(0, 0, 0);
			_PooledObjects.push_back(_InUseObjects[i]);
			_InUseObjects.erase(_InUseObjects.begin() + i);

			std::cout << "Returning Object: " << _PooledObjects[_PooledObjects.size() - 1]->GetName()
				<< " at position " << _PooledObjects[_PooledObjects.size() - 1]->GetTransform()->position.x
				<< " " << _PooledObjects[_PooledObjects.size() - 1]->GetTransform()->position.y
				<< std::endl;
		}
	}

	GameObject* ObjectPool::GetObject(ObjectTypes objectType, Vector2f position)
	{
		if (_PooledObjects.size() == 0) return nullptr;

		bool l_isFound = false;
		int l_foundIndex = -1;

		for (int i = 0; i < _PooledObjects.size(); i++)
		{
			if (_PooledObjects[i]->CompareType(objectType))
			{
				l_isFound = true;
				l_foundIndex = i;
				break;
			}
		}

		GameObject* l_tmp = l_isFound
			? _PooledObjects[l_isFound]
			: AddObject(objectType, 1);

		_PooledObjects.erase(_PooledObjects.begin() + l_isFound);

		l_tmp->transform->position = Vector3f(position);
		l_tmp->SetActive(true);
		l_tmp->GetComponent<Collider>()->Reset();
		_InUseObjects.push_back(l_tmp);

		std::cout << "Getting Object: " << _PooledObjects.size() << " " << _InUseObjects.size() << std::endl;

		//std::cout << "Getting Object: " << _InUseObjects[_InUseObjects.size() - 1]->GetName() << " at position " << position.x << " " << position.y << std::endl;

		//std::cout << "Getting Null Object " << (int)objectType << std::endl;
		return l_tmp;
	}

	GameObject* ObjectPool::GetObjectRef(ObjectTypes objectType)
	{
		for (int i = 0; i < _InUseObjects.size(); i++)
		{
			if (_InUseObjects[i] != nullptr)
			{
				if (_InUseObjects[i]->CompareType(objectType))
				{
					return _InUseObjects[i];
				}
			}
		}

		for (int i = 0; i < _PooledObjects.size(); i++)
		{
			if (_PooledObjects[i] != nullptr)
			{
				if (_PooledObjects[i]->CompareType(objectType))
				{
					return _PooledObjects[i];
				}
			}
		}

		return nullptr;
	}
}
