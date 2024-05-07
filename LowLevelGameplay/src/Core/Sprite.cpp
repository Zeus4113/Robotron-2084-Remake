#include <Core/Sprite.h>
#include <Core/RenderingManager.h>
#include <Core/GameObject.h>

namespace LLGP 
{
	Sprite::Sprite(GameObject* owner) : Component(owner)
	{
		RenderingManager::RegisterSprite(this);
	}

	Sprite::~Sprite()
	{
		RenderingManager::UnregisterSprite(this);
	}

	void Sprite::SetTexture(std::string filePath, Vector2f spriteAmount)
	{
		_spriteTexture.loadFromFile(filePath); 
		_spriteShape.setTexture(&_spriteTexture);
		_spritesInSheet = spriteAmount;
	}

	void Sprite::UpdateTexture(int row, int collumn)
	{
		_spriteShape.setTextureRect(sf::IntRect(
			(_spriteTexture.getSize().x / _spritesInSheet.x) * collumn,
			(_spriteTexture.getSize().y / _spritesInSheet.y) * row,
			_spriteTexture.getSize().x / _spritesInSheet.x,
			_spriteTexture.getSize().y / _spritesInSheet.y));
	}

	void Sprite::UpdateRender()
	{
		_spriteShape.setPosition(_GameObject->transform->position.x, _GameObject->transform->position.y);
	}
}