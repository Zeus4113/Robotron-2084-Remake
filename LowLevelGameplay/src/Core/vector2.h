#pragma once
#include <Core/arithmetic_concept.h>
#include <SFML/Graphics.hpp>

namespace LLGP {
	
	template<typename T> requires arithmatic<T>

	struct Vector2 {
	public:
		T x, y;

#pragma region constructors
		Vector2() : x(0), y(0) {}
		Vector2(const Vector2&) = default;
		Vector2(T _x, T _y) : x(_x), y(_y) {}

		template<typename U> requires arithmatic<U>
		explicit Vector2(const Vector2<U>& in) :
			x(static_cast<T>(in.x)), y(static_cast<T>(in.y)) {}
		
		template<typename U> requires arithmatic<U>
		explicit Vector2(const sf::Vector2<U>& in) :
			x(static_cast<T>(in.x)), y(static_cast<T>(in.y)) {}

		template<typename U> requires arithmatic<U>
		operator sf::Vector2<U>() { return sf::Vector2<U>(static_cast<U>(x), static_cast<U>(y)); }

#pragma endregion

		float GetSqrMagnitude() { return x * x + y * y; }
		float GetMagnitude() { return sqrt(GetSqrMagnitude()); }
		Vector2<T>& Normalise() {
			*this /= GetMagnitude(); return *this;
		}
		Vector2<T> Normalised() {
			return *this / GetMagnitude(); return*this;
		}
		static float Dot(const Vector2<T>& lhs, const Vector2<T>& rhs)
		{
			return (float)(lhs.x * rhs.x + lhs.y * rhs.y);
		}
		static float Angle(Vector2<T>& lhs, Vector2<T>& rhs)
		{
			return acos(Dot(lhs.Normalised(), rhs.Normalised()));
		}

		static const Vector2 zero;
		static const Vector2 one;
		static const Vector2 up;
		static const Vector2 down;
		static const Vector2 left;
		static const Vector2 right;

	};

	// Setter Operators

	template<typename T> requires arithmatic<T>
	Vector2<T>& operator+=(Vector2<T>& lhs, const Vector2<T> rhs)
	{
		lhs.x += rhs.x; lhs.y += rhs.y; return lhs;
	}

	template<typename T> requires arithmatic<T>
	Vector2<T>& operator-=(Vector2<T>& lhs, Vector2<T> rhs) 
	{
		lhs.x -= rhs.x; lhs.y -= rhs.y; return lhs;
	}

	template<typename T, typename U> requires arithmatic<T> and arithmatic<U>
	Vector2<T>& operator-=(Vector2<T>& lhs, Vector2<U> rhs)
	{
		lhs.x -= rhs.x; lhs.y -= rhs.y; return lhs;
	}

	template<typename T, typename U> requires arithmatic<T> and arithmatic<U>
	Vector2<T>& operator-=(Vector2<T> lhs, Vector2<U> rhs)
	{
		lhs.x -= rhs.x; lhs.y -= rhs.y; return lhs;
	}

	template<typename T, typename U> requires arithmatic<T> and arithmatic<U>
	Vector2<T>& operator*=(Vector2<T>& v, const U a)
	{
		v.y *= a; v.x *= a; return v;
	}

	template<typename T, typename U> requires arithmatic<T> and arithmatic<U>
	Vector2<T>& operator/=(Vector2<T>& v, const U a)
	{
		v.y /= a; v.x /= a; return v;
	}

	// Calculation Operators

	template<typename T> requires arithmatic<T>
	Vector2<T> operator-(const Vector2<T> v)
	{
		return Vector2<T>(-v.x, -v.y);
	}

	template<typename T> requires arithmatic<T>
	Vector2<T> operator-(const Vector2<T> lhs, const Vector2<T>& rhs)
	{
		return lhs -= rhs;
	}

	template<typename T, typename U> requires arithmatic<T> and arithmatic<U>
	Vector2<T> operator-(const Vector2<T> lhs, const Vector2<U>& rhs)
	{
		return lhs -= rhs;
	}

	template<typename T> requires arithmatic<T>
	Vector2<T> operator+(Vector2<T> lhs, const Vector2<T>& rhs)
	{
		return lhs += rhs;
	}

	template<typename T, typename U> requires arithmatic<T> and arithmatic<U>
	Vector2<T> operator/(Vector2<T> v, const U a)
	{
		return v /= a;
	}

	template<typename T, typename U> requires arithmatic<T> and arithmatic<U>
	Vector2<T> operator/(const U a, Vector2<T> v)
	{
		return v /= a;
	}

	template<typename T, typename U> requires arithmatic<T> and arithmatic<U>
	Vector2<T> operator*(Vector2<T> v, const U a)
	{
		return v *= a;
	}

	template<typename T, typename U> requires arithmatic<T> and arithmatic<U>
	Vector2<T> operator*(const U a, Vector2<T> v)
	{
		return v *= a;
	}

	// Comparison Operators

	//template<typename T> requires arithmatic<T>
	//inline bool operator==(Vector2<T>& lhs, const Vector2<T> rhs)
	//{
	//	Vector2<T> dist = lhs - rhs;
	//	float mag = dist.x * dist.x + dist.y * dist.y;
	//	return mag < 9.99999944E-11f;
	//}

	template<typename T> requires arithmatic<T>
	inline bool operator==(Vector2<T> lhs, Vector2<T> rhs)
	{
		Vector2<T> dist = lhs - rhs;
		float mag = dist.x * dist.x + dist.y * dist.y;
		return mag < 9.99999944E-11f;
	}

	template<typename T> requires arithmatic<T>
	inline bool operator!=(Vector2<T>& lhs, const Vector2<T> rhs)
	{
		return !(lhs == rhs);
	}


	// Static References
	template<typename T> requires arithmatic<T>
	const Vector2<T> Vector2<T>::zero(static_cast<T>(0), static_cast<T>(0));

	template<typename T> requires arithmatic<T>
	const Vector2<T> Vector2<T>::one(static_cast<T>(1), static_cast<T>(1));

	template<typename T> requires arithmatic<T>
	const Vector2<T> Vector2<T>::left(static_cast<T>(-1), static_cast<T>(0));

	template<typename T> requires arithmatic<T>
	const Vector2<T> Vector2<T>::right(static_cast<T>(1), static_cast<T>(0));

	template<typename T> requires arithmatic<T>
	const Vector2<T> Vector2<T>::up(static_cast<T>(0), static_cast<T>(1));

	template<typename T> requires arithmatic<T>
	const Vector2<T> Vector2<T>::down(static_cast<T>(0), static_cast<T>(-1));


	// Type definitions
	typedef Vector2<int> Vector2i;
	typedef Vector2<unsigned int> Vector2u;
	typedef Vector2<double> Vector2d;
	typedef Vector2<float> Vector2f;
}