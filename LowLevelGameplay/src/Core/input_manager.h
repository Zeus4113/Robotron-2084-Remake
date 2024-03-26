#pragma once
#include <Core/Event.h>
#include <Core/vector2.h>
#include <vector>

namespace LLGP 
{
	static class InputManager
	{
	private:
		static Vector2f movementVectorObserver;
	public:
		static Event<int> inputEvent;
		static Event<Vector2f> onMovementPerformed;
		static Event<Vector2f> onMovementCancelled;

		static void CheckInput() {

			Vector2f movementVector = Vector2f(
				sf::Keyboard::isKeyPressed(sf::Keyboard::Right) - sf::Keyboard::isKeyPressed(sf::Keyboard::Left), 
				sf::Keyboard::isKeyPressed(sf::Keyboard::Up) - sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
			);

			if (movementVector != movementVectorObserver) {
				if (movementVector == Vector2f::zero) {
					onMovementCancelled(movementVector);
				}
				else {
					onMovementPerformed(movementVector);
				}
			}

			movementVectorObserver = movementVector;
		}
	};
}
