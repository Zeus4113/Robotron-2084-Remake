#include <Core/RenderingManager.h>
#include <Core/Sprite.h>
#include <Core/GameObject.h>

namespace LLGP 
{
	std::vector<Sprite*> RenderingManager::_Sprites;
	sf::RenderWindow* RenderingManager::_Window;

	void RenderingManager::StartRender() 
	{
		_Window = new sf::RenderWindow(sf::VideoMode(990, 540), "Render Window");
	}

	void RenderingManager::RegisterSprite(Sprite* newSprite)
	{
		_Sprites.push_back(newSprite);
	}

	void RenderingManager::UnregisterSprite(Sprite* oldSprite)
	{
		for (int i = 0; i < _Sprites.size(); ++i)
		{
			if (_Sprites[i] == oldSprite)
			{
				_Sprites.erase(_Sprites.begin() + i);
			}
		}
	}

	void RenderingManager::UpdateRender()
	{
		_Window->clear();

		for (Sprite* s : _Sprites) 
		{
			if (s->GetGameObject()->GetActive()) 
			{
				s->UpdateRender();
				_Window->draw(s->GetShape());
			}
		}
		_Window->display();
	}
}