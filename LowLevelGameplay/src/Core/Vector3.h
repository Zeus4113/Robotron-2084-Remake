#pragma once
#include <Core/arithmetic_concept.h>

namespace LLGP
{
	template<typename T> requires arithmatic<T>

	struct Vector3 {
	public:
		T x, y, z;

#pragma region constructors
		Vector3() : x(0), y(0), z(0) {}
		Vector3(const Vector3&) = default;
		Vector3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
		Vector3(T _x, T _y) : x(_x), y(_y), z(0) {}

		template<typename U> requires arithmatic<U>
		explicit Vector3(const Vector3<U>& in) :
			x(static_cast<T>(in.x)), y(static_cast<T>(in.y)), z(static_cast<T>(in.z)) {}

		template<typename U> requires arithmatic<U>
		explicit Vector3(const Vector2<U>& in) :
			x(static_cast<T>(in.x)), y(static_cast<T>(in.y)), z(0) {}

#pragma endregion

		float GetSqrMagnitude() { return x * x + y * y + z * z; }
		float GetMagnitude() { return sqrt(GetSqrMagnitude()); }
		Vector3<T>& Normalise() {
			*this /= GetMagnitude(); return *this;
		}
		Vector3<T> Normalised() {
			return *this / GetMagnitude(); return*this;
		}
		static float Dot(const Vector3<T>& lhs, const Vector3<T>& rhs)
		{
			return (float)(lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z);
		}
		static float Angle(Vector3<T>& lhs, Vector3<T>& rhs)
		{
			return acos(Dot(lhs.Normalised(), rhs.Normalised()));
		}

		static const Vector3 zero;
		static const Vector3 one;
		static const Vector3 up;
		static const Vector3 down;
		static const Vector3 left;
		static const Vector3 right;
		static const Vector3 forward;
		static const Vector3 backward;

	};

	// Setter Operators

	template<typename T> requires arithmatic<T>
	Vector3<T>& operator+=(Vector3<T>& lhs, const Vector3<T> rhs)
	{
		lhs.x += rhs.x; lhs.y += rhs.y; lhs.z += rhs.z; return lhs;
	}

	template<typename T, typename U> requires arithmatic<T> and arithmatic<U>
	Vector3<T>& operator+=(Vector3<T>& lhs, const Vector2<U> rhs)
	{
		lhs.x += rhs.x; lhs.y += rhs.y; return lhs;
	}

	template<typename T> requires arithmatic<T>
	Vector3<T>& operator-=(Vector3<T>& lhs, Vector3<T> rhs)
	{
		lhs.x -= rhs.x; lhs.y -= rhs.y; lhs.z -= rhs.z; return lhs;
	}

	template<typename T, typename U> requires arithmatic<T> and arithmatic<U>
	Vector3<T>& operator*=(Vector3<T>& v, const U a)
	{
		v.y *= a; v.x *= a; v.z *= a; return v;
	}

	template<typename T, typename U> requires arithmatic<T> and arithmatic<U>
	Vector3<T>& operator/=(Vector3<T>& v, const U a)
	{
		v.y /= a; v.x /= a; v.z *= a; return v;
	}

	// Calculation Operators

	template<typename T> requires arithmatic<T>
	Vector3<T> operator-(const Vector3<T> v)
	{
		return Vector3<T>(-v.x, -v.y, -v.z);
	}

	template<typename T> requires arithmatic<T>
	Vector3<T> operator-(const Vector3<T> lhs, const Vector3<T>& rhs)
	{
		return lhs -= rhs;
	}

	template<typename T, typename U> requires arithmatic<T> and arithmatic<U>
	Vector3<T> operator-(const Vector3<T> lhs, const Vector3<U>& rhs)
	{
		return lhs -= rhs;
	}

	template<typename T> requires arithmatic<T>
	Vector3<T> operator+(Vector3<T> lhs, const Vector3<T>& rhs)
	{
		return lhs += rhs;
	}

	template<typename T, typename U> requires arithmatic<T> and arithmatic<U>
	Vector3<T> operator/(Vector3<T> v, const U a)
	{
		return v /= a;
	}

	template<typename T, typename U> requires arithmatic<T> and arithmatic<U>
	Vector3<T> operator/(const U a, Vector3<T> v)
	{
		return v /= a;
	}

	template<typename T, typename U> requires arithmatic<T> and arithmatic<U>
	Vector3<T> operator*(Vector3<T> v, const U a)
	{
		return v *= a;
	}

	template<typename T, typename U> requires arithmatic<T> and arithmatic<U>
	Vector3<T> operator*(const U a, Vector3<T> v)
	{
		return v *= a;
	}

	// Comparison Operators

	template<typename T> requires arithmatic<T>
	inline bool operator==(Vector3<T>& lhs, const Vector3<T> rhs)
	{
		Vector3<T> dist = lhs - rhs;
		float mag = dist.x * dist.x + dist.y * dist.y + dist.z * dist.z;
		return mag < 9.99999944E-11f;
	}

	template<typename T> requires arithmatic<T>
	inline bool operator!=(Vector3<T>& lhs, const Vector3<T> rhs)
	{
		return !(lhs == rhs);
	}

	// Static References
	template<typename T> requires arithmatic<T>
	const Vector3<T> Vector3<T>::zero(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0));

	template<typename T> requires arithmatic<T>
	const Vector3<T> Vector3<T>::one(static_cast<T>(1), static_cast<T>(1), static_cast<T>(0));

	template<typename T> requires arithmatic<T>
	const Vector3<T> Vector3<T>::left(static_cast<T>(-1), static_cast<T>(0), static_cast<T>(0));

	template<typename T> requires arithmatic<T>
	const Vector3<T> Vector3<T>::right(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0));

	template<typename T> requires arithmatic<T>
	const Vector3<T> Vector3<T>::up(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0));

	template<typename T> requires arithmatic<T>
	const Vector3<T> Vector3<T>::down(static_cast<T>(0), static_cast<T>(-1), static_cast<T>(0));

	template<typename T> requires arithmatic<T>
	const Vector3<T> Vector3<T>::forward(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));

	template<typename T> requires arithmatic<T>
	const Vector3<T> Vector3<T>::backward(static_cast<T>(0), static_cast<T>(0), static_cast<T>(-1));

	// Type definitions
	typedef Vector3<int> Vector3i;
	typedef Vector3<unsigned int> Vector3u;
	typedef Vector3<double> Vector3d;
	typedef Vector3<float> Vector3f;
}