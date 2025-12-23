#include "Collision.h"

bool Collision::checkCollisionRecs(
    const Vec2f& rec1Min,
    const Vec2f& rec1Max,
    const Vec2f& rec2Min,
    const Vec2f& rec2Max
)
{
    if (rec1Max.x < rec2Min.x || rec1Min.x > rec2Max.x)
        return false;

    if (rec1Max.y < rec2Min.y || rec1Min.y > rec2Max.y)
        return false;

    return true;
}

bool Collision::checkCollisionPointRect(
    const Vec2f& point,
    const Vec2f& recMin,
    const Vec2f& recMax
)
{
    if (point.x < recMin.x || point.x > recMax.x)
        return false;

    if (point.y < recMin.y || point.y > recMax.y)
        return false;

    return true;
}
