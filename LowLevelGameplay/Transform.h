#pragma once
#include "Vector3.h"

namespace LLGP
{
	//template<typename T> requires arithmatic<T>

	struct Transform {
	public:
		Vector3<float> position;
		Vector3<float> rotation;
		Vector3<float> scale;

		Transform() : position(0,0,0), rotation(0,0,0), scale(0,0,0) {}
		Transform(const Transform&) = default;

		template<typename T> requires arithmatic<T>
		Transform(const Vector3<T> _pos, const Vector3<T> _rot, const Vector3<T> _sca) : position(_pos), rotation(_rot), scale(_sca) {}

		template<typename U> requires arithmatic<U>
		explicit Transform(const Transform& in) :
			position(static_cast<Vector3<T>>(in.position)), rotation(static_cast<Vector3<T>>(in.rotation)), scale(static_cast<Vector3<T>>(in.scale)) {}

	};
}