#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

namespace LLGP 
{
	class Sprite;

	static class RenderingManager
	{
	public:
		RenderingManager() {}
		~RenderingManager() {}

		static void RegisterSprite(Sprite* newSprite);
		static void UnregisterSprite(Sprite* oldSprite);

		static void StartRender();
		static void UpdateRender();

		static sf::RenderWindow* GetWindow() { return _Window; }

	private:
		static std::vector<Sprite*> _Sprites;
		static sf::RenderWindow* _Window;
	};
}

