#pragma once

#include <iostream>
#include "Vec2.h"

class Collision
{
public:
	static bool checkCollisionRecs(const Vec2f& rec1Min, const Vec2f& rec1Max, const Vec2f& rec2Min, const Vec2f& rec2Max);
	static bool checkCollisionPointRect(const Vec2f& point, const Vec2f& recMin, const Vec2f& recMax);
};

