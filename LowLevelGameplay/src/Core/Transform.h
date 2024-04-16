#pragma once
#include <Core/Vector3.h>
#include <Core/Component.h>

namespace LLGP
{
	class Transform : public Component {
	public:
		Vector3<float> position;

		//Vector3<float> rotation;
		//Vector3<float> scale;

		Transform(GameObject* owner) : Component(owner), position(0,0,0) {}
		Transform(const Transform&) = default;

	};
}