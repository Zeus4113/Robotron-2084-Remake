#include "Animator.h"
#include "Core/GameObject.h"
#include "Core/Rigidbody.h"
#include <Core/MovementDirections.h>
#include <Core/Sprite.h>
#include <Core/RenderingManager.h>
#include <iostream>

namespace LLGP 
{
	Animator::Animator(GameObject* owner) : Component(owner)
	{
		_updateTime = 0;
		RenderingManager::RegisterAnimator(this);
	}

	Animator::~Animator()
	{
		RenderingManager::UnregisterAnimator(this);
	}

	void Animator::UpdateSprite(float deltaTime)
	{

		_updateTime += deltaTime;

		if (_updateTime > _frameTime) 
		{
			_updateTime = 0;

			if (_isPlaying) 
			{
				_currentCollumn++;

				if (_currentCollumn * (this->GetGameObject()->GetComponent<Sprite>()->GetSpriteSize()) >= this->GetGameObject()->GetComponent<Sprite>()->GetTextureSize().x)
				{
					_currentCollumn = 0;
				}
			}
			else 
			{
				_currentCollumn = 1;
			}

		}

		this->GetGameObject()->GetComponent<Sprite>()->UpdateTexture(_currentRow, _currentCollumn);
	}
}
