#pragma once

#include <iostream>

template<typename T>

class Vec2
{
public:
	T x, y;

	Vec2() : x(0.f), y(0.f) {}
	Vec2(T x, T y) : x(x), y(y) {}

	Vec2& operator=(const Vec2& other)
	{
		if (this != &other)
		{
			x = other.x;
			y = other.y;
		}
		return *this;
	}

	Vec2 operator+(const Vec2& other) const
	{
		return Vec2(x + other.x, y + other.y);
	}

	Vec2 operator-(const Vec2& other) const
	{
		return Vec2(x - other.x, y - other.y);
	}

	Vec2 operator*(float scalar) const
	{
		return Vec2(x * scalar, y * scalar);
	}

	Vec2 operator/(float scalar) const
	{
		return Vec2(x / scalar, y / scalar);
	}

	Vec2& operator+=(const Vec2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Vec2& operator-=(const Vec2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const Vec2& vec)
	{
		os << "(" << vec.x << ", " << vec.y << ")";
		return os;
	}
};

using Vec2f = Vec2<float>;
using Vec2i = Vec2<int>;
