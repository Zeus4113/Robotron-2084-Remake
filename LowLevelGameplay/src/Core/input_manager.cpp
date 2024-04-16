#include <Core/input_manager.h>

namespace LLGP {

	Vector2f InputManager::movementVectorObserver = Vector2f::zero;
	Event<Vector2f> InputManager::onMovementPerformed;
	Event<Vector2f> InputManager::onMovementCancelled;

}