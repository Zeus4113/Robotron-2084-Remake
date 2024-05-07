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

	//void Animator::SetTexture(std::string filePath, Vector2f spriteAmount)
	//{
	//	std::cout << "Texture: " << filePath << std::endl;
	//	_spriteSheet.loadFromFile(filePath); 
	//	_spritesInSheet = spriteAmount;
	//	_sheetSize = Vector2f(_spriteSheet.getSize());
	//	std::cout << "Size: " << _sheetSize.x << ", " << _sheetSize.y << std::endl;
	//	_rectCutout = sf::IntRect(0, 0, _sheetSize.x / _spritesInSheet.x, _sheetSize.y / _spritesInSheet.y);
	//}

	void Animator::UpdateSprite(float deltaTime)
	{

		_updateTime += deltaTime;


		MovementDirection direction = this->GetGameObject()->GetComponent<Rigidbody>()->GetDirection();
		

		switch (direction) {
			case MovementDirection::Left:
				_currentRow = 1;
				break;

			case MovementDirection::Right:
				_currentRow = 0;
				break;

			case MovementDirection::Up:
				_currentRow = 2;
				break;

			case MovementDirection::Down:
				_currentRow = 3;
				break;

			default:

				break;
		}

		if (_updateTime > _frameTime) 
		{
			_updateTime = 0;

			if (direction != MovementDirection::Idle) 
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

		//std::cout << "Row: " << _currentRow << " Collumn: " << _currentCollumn << std::endl;;

		this->GetGameObject()->GetComponent<Sprite>()->UpdateTexture(_currentRow, _currentCollumn);
	}
}
