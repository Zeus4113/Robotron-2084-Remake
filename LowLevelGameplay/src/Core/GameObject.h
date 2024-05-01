#pragma once
#include <concepts>
#include <string>
#include <vector>
#include <memory>
#include <Core/vector2.h>

#include <Core/component_concept.h>
#include <Core/object.h>
#include <Core/Transform.h>
#include <Core/ObjectTypes.h>

namespace LLGP
{
	class GameObject : public Object
	{
	public:
		GameObject();
		~GameObject();

		//GameObject(const GameObject&) = default;

		Transform* transform;
		inline void SetName(std::string newName) { m_Name = newName; }
		inline std::string GetName() { if (this != nullptr) return m_Name; }

		void SetActive(bool newActive) { m_Active = newActive; }
		inline bool GetActive() { if(this != nullptr) return m_Active; }

		inline void SetTag(std::string newTag) { m_Tag = newTag; }
		inline bool CompareTag(std::string comp) { if (this != nullptr) return m_Tag == comp; }

		inline void SetType(ObjectTypes newType) { m_Type = newType; }
		inline bool CompareType(ObjectTypes comp) { if (this != nullptr) return m_Type == comp; }

		virtual void Awake();

		template<class T> requires isComponent<T>
		T* AddComponent()
		{
			std::unique_ptr<Component> newComp = std::make_unique<T>(this);
			m_Components.push_back(std::move(newComp));
			return static_cast<T*>(m_Components[m_Components.size()-1].get());
		}

		template<class T> requires isComponent<T> 
		T* GetComponent() {
			T* returnComp = nullptr;
			for (int i = 0; i < m_Components.size(); i++)
			{
				returnComp = dynamic_cast<T*>(m_Components[i].get());
				if (returnComp != nullptr)
				{
					return returnComp;
				}
			}
			return nullptr;
			
		}
		template<class T> requires isComponent<T> bool RemoveComponent(T* comp) { return false; }

		void MoveObject(Vector2f movementVector) { transform->position += movementVector; }
		inline Transform* GetTransform() { if (this != nullptr) return transform; }

	private:
		std::string m_Name;
		bool m_Active;
		std::string m_Tag;
		ObjectTypes m_Type;
		

	protected:
		std::vector<std::unique_ptr<Component>> m_Components;

	};
}