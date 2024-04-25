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

	void Sprite::UpdateRender()
	{
		_spriteShape.setPosition(_GameObject->transform->position.x, _GameObject->transform->position.y);
	}
}