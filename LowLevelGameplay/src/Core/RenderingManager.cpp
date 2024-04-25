#include <Core/RenderingManager.h>
#include <Core/Sprite.h>

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
				_Sprites[i] = nullptr;
				delete _Sprites[i];
			}
		}
	}

	void RenderingManager::UpdateRender()
	{
		_Window->clear();

		for (Sprite* s : _Sprites) {
			s->UpdateRender();
			_Window->draw(s->GetShape());
		}

		_Window->display();
	}
}