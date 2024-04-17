#include <Core/input_manager.h>

namespace LLGP {

	Vector2f InputManager::movementVectorObserver = Vector2f::zero;
	Event<Vector2f> InputManager::onMovementPerformed;
	Event<Vector2f> InputManager::onMovementCancelled;
	Event<Vector2f> InputManager::onMovementStarted;

	void InputManager::CheckInput() {

		Vector2f movementVector = Vector2f(
			sf::Keyboard::isKeyPressed(sf::Keyboard::Right) - sf::Keyboard::isKeyPressed(sf::Keyboard::Left),
			sf::Keyboard::isKeyPressed(sf::Keyboard::Up) - sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
		);

		if (movementVector != movementVectorObserver) {

			if (movementVector == Vector2f::zero) {
				onMovementCancelled(movementVector);
			}
			else {
				onMovementStarted(movementVector);
			}
		}

		if (movementVector != Vector2f::zero) {
			onMovementPerformed(movementVector);
		}

		movementVectorObserver = movementVector;
	}

}