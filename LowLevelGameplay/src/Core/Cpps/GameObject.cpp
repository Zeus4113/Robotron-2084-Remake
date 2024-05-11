#include <Core/GameObject.h>
#include <Core/EntityManager.h>

namespace LLGP
{
	GameObject::GameObject() 
	{
		transform = this->AddComponent<Transform>();
		EntityManager::RegisterEntity(this);
	}

	GameObject::~GameObject() 
	{
		EntityManager::UnregisterEntity(this);
	}

	void GameObject::Awake()
	{
		for (int i = 0; i < m_Components.size(); i++) 
		{
			m_Components[i]->Awake();
		}
	}
}
