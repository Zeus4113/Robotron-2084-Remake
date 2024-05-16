#include <Core/ObjectPool.h>
#include <iostream>
#include <Core/ObjectTypes.h>
#include <Core/GameObject.h>
#include <Core/Collider.h>
#include <App/ScoreManager.h>
#include <App/GameManager.h>

namespace LLGP 
{

	std::vector<GameObject*> ObjectPool::_PooledObjects;
	std::vector<GameObject*> ObjectPool::_InUseObjects;

	std::vector<GameObject*> ObjectPool::GetAllObjectsOfType(ObjectTypes objectType) 
	{
		std::vector<GameObject*> objectsToReturn;

		for (GameObject* o : _PooledObjects)
		{
			if (o->CompareType(objectType)) 
			{
				objectsToReturn.push_back(o);
			}
		}

		return objectsToReturn;
	}

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
			case ObjectTypes::EnemyHulk:
				newObject->AddComponent<EnemyHulk>();
				newObject->SetName("Enemy Hulk");
				break;
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
				_InUseObjects[i]->GetComponent<Collider>()->Reset();

				_InUseObjects[i]->transform->position = Vector3f(0, 0, 0);
				_PooledObjects.push_back(_InUseObjects[i]);
				_InUseObjects.erase(_InUseObjects.begin() + i);

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
			i--;

			/*std::cout << "Returning Object (ALL): " << _PooledObjects[_PooledObjects.size() - 1]->GetName()
				<< " at position " << _PooledObjects[_PooledObjects.size() - 1]->GetTransform()->position.x
				<< " " << _PooledObjects[_PooledObjects.size() - 1]->GetTransform()->position.y
				<< std::endl;*/
		}
	}

	GameObject* ObjectPool::GetObject(ObjectTypes objectType, Vector2f position)
	{
		if (_PooledObjects.size() == 0) return nullptr;

		for (int i = 0; i < _PooledObjects.size(); i++)
		{
			if (_PooledObjects[i]->CompareType(objectType))
			{
				_PooledObjects[i]->transform->position = Vector3f(position);
				_PooledObjects[i]->SetActive(true);

				_InUseObjects.push_back(_PooledObjects[i]);
				_PooledObjects.erase(_PooledObjects.begin() + i);

				//std::cout << "Getting Object: " << _InUseObjects[_InUseObjects.size() - 1]->GetName() << " at position " << position.x << " " << position.y << std::endl;

				return _InUseObjects[_InUseObjects.size() - 1];
			}		
		}


		return nullptr;
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
