#pragma once
#include <Core/Component.h>
#include <SFML/Graphics.hpp>
#include <string>
#include <Core/vector2.h>

namespace LLGP 
{
	class Animator : public Component
	{
	public:
		Animator(GameObject* owner);
		~Animator();

		void UpdateSprite(float deltaTime);
		void SetRow(int newRow) { _currentRow = newRow; }
		void SetPlaying(bool isPlaying) { _isPlaying = isPlaying; }
		
	private:
		float _updateTime;
		float _frameTime = 0.1f;

		int _currentRow = 0;
		int _currentCollumn = 0;

		bool _isPlaying = true;

	};
}


