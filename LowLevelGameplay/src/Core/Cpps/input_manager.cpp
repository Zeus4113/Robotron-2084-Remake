#include <Core/input_manager.h>

namespace LLGP {

	Vector2f InputManager::movementVectorObserver = Vector2f::zero;
	Event<Vector2f> InputManager::onMovementPerformed;
	Event<Vector2f> InputManager::onMovementCancelled;
	Event<Vector2f> InputManager::onMovementStarted;

	Vector2f InputManager::shootingVectorObserver = Vector2f::zero;
	Event<Vector2f> InputManager::onShootingPerformed;
	Event<Vector2f> InputManager::onShootingCancelled;

	Event<int> InputManager::onShoot;
	Event<bool> InputManager::onRestart;
	Event<bool> InputManager::onPause;

	bool InputManager::isPressed;
	bool InputManager::isRestartPressed = false;

	void InputManager::CheckInput() {

		// Movement Input Detection

		Vector2f movementVector = Vector2f(
			sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::A),
			sf::Keyboard::isKeyPressed(sf::Keyboard::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::W)
		);

		if (movementVector != Vector2f::zero) 
		{
			movementVector = movementVector.Normalise();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) 
		{
			if (!isRestartPressed) 
			{
				isRestartPressed = true;
				onRestart(true);
			}
		}
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::R)) 
		{
			isRestartPressed = false;
		}

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

		// Shooting Input Detection

		Vector2f shootingVector = Vector2f(
			sf::Keyboard::isKeyPressed(sf::Keyboard::Right) - sf::Keyboard::isKeyPressed(sf::Keyboard::Left),
			sf::Keyboard::isKeyPressed(sf::Keyboard::Down) - sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		);

		if (shootingVector != Vector2f::zero)
		{
			shootingVector = shootingVector.Normalise();
		}

		if (shootingVector != shootingVectorObserver) {

			if (shootingVector == Vector2f::zero) {
				onShootingCancelled(shootingVector);
			}
		}

		if (shootingVector != Vector2f::zero) {
			onShootingPerformed(shootingVector);
		}

		shootingVectorObserver = shootingVector;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

			if (shootingVector != Vector2f::zero && !isPressed) {
				onShoot(0);
			}

			isPressed = true;
		}

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			isPressed = false;
		}
	}

}