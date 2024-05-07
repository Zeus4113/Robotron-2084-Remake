#pragma once
#include <Core/Component.h>
#include <Core/vector2.h>
#include <Core/MovementDirections.h>

namespace LLGP {

	class Collider;

	class Rigidbody : public Component {

	public:

		Rigidbody(GameObject* owner);
		~Rigidbody();
		
		void SetVelocity(Vector2f newVelocity);
		Vector2f GetVelocity() { return _Velocity;  }
		float GetMagnitude() { return _Velocity.x * _Velocity.x + _Velocity.y * _Velocity.y; }
		MovementDirection GetDirection() { return _direction; }

		void DampenVelocity() 
		{
			float xValue = _Velocity.x;
			float yValue = _Velocity.y;

			if (xValue > 9.99999944E-11f)
			{
				xValue -= _Drag;
				if (xValue < 9.99999944E-11f) xValue = 0.f;
			}
			else if (xValue < 9.99999944E-11f)
			{
				xValue += _Drag;
				if (xValue > 9.99999944E-11f) xValue = 0.f;
			}

			if (yValue > 9.99999944E-11f)
			{
				yValue -= _Drag;
				if (yValue < 9.99999944E-11f) yValue = 0.f;
			}
			else if (yValue < 9.99999944E-11f)
			{
				yValue += _Drag;
				if (yValue > 9.99999944E-11f) yValue = 0.f;
			}

			SetVelocity(Vector2f(xValue, yValue));
		}

		void SetMass(float newMass) { _Mass = newMass; }
		float GetMass() { return _Mass; }

		void SetSize(Vector2f newSize);

		float GetDrag() { return _Drag; }
		void SetDrag(float newDrag) { _Drag = newDrag; }

		Collider* GetCollider() { return _Collider; }

	private:

		MovementDirection _direction;
		Vector2f _Velocity;
		float _Mass;
		Collider* _Collider;
		float _Drag;
	};
}
