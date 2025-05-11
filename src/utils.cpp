#include "utils.h"
#include <cmath> // sqrt
#include <algorithm> // max

Vector2 operator+(const Vector2& v1, const Vector2& v2)
{
    return { v1.x + v2.x, v1.y + v2.y };
}

Vector2 operator-(const Vector2& v1, const Vector2& v2)
{
    return { v1.x - v2.x, v1.y - v2.y };
}

Vector2 operator*(const Vector2& v, float scalar)
{
    return { v.x * scalar, v.y * scalar };
}

Vector2 operator*(float scalar, const Vector2& v)
{
    return { v.x * scalar, v.y * scalar };
}

Vector2 operator/(const Vector2& v, float scalar)
{
    if (scalar != 0.0f)
        return { v.x / scalar, v.y / scalar };
    return v;
}

Vector2& operator+=(Vector2& v1, const Vector2& v2)
{
    v1.x += v2.x;
    v1.y += v2.y;
    return v1;
}

Vector2& operator-=(Vector2& v1, const Vector2& v2)
{
    v1.x -= v2.x;
    v1.y -= v2.y;
    return v1;
}

Vector2 operator-(const Vector2& v)
{
    return { -v.x, -v.y };
}

bool operator==(const Vector2& v1, const Vector2& v2)
{
    const float precision = 0.00001f; // e-5 precision

    // near zero comparison
    if (std::abs(v1.x) < precision && std::abs(v2.x) < precision &&
        std::abs(v1.y) < precision && std::abs(v2.y) < precision) {
        return true;
    }

    // remaining cases
    float xEpsilon = std::abs(std::max(std::abs(v1.x), std::abs(v2.x)) * precision);
    float yEpsilon = std::abs(std::max(std::abs(v1.y), std::abs(v2.y)) * precision);

    return (std::abs(v1.x - v2.x) < xEpsilon) &&
        (std::abs(v1.y - v2.y) < yEpsilon);
}

bool operator!=(const Vector2& v1, const Vector2& v2)
{
    return !(v1 == v2);
}

float vector2Length(Vector2 v)
{
    return std::sqrt(v.x * v.x + v.y * v.y);
}

float vector2Distance(Vector2 v1, Vector2 v2)
{
    return std::sqrt((v2.x - v1.x) * (v2.x - v1.x) + (v2.y - v1.y) * (v2.y - v1.y));
}

Vector2 vector2Normalize(Vector2 v)
{
    float length = vector2Length(v);
    if (length != 0.0f)
        return { v.x / length, v.y / length };
    return v;
}

Vector2 normalizedTangent(Vector2 v1, Vector2 v2)
{
    return vector2Normalize(v2 - v1);
}

Vector2 tangent2Normal(Vector2 tangent)
{
    return { tangent.y, -tangent.x }; // instead of return { -tangent.y, tangent.x }; - consistant with Screen coordinate system where x right, y is down.
}

float vector2Dot(Vector2 v1, Vector2 v2)
{
    return { v1.x * v2.x + v1.y * v2.y };
}

float vector2Angle(Vector2 v1, Vector2 v2)
{
    if (vector2Length(v1) < 1e-3f || vector2Length(v2) < 1e-3f) return 0.0f;
    float cosTheta{ vector2Dot(v1, v2) / (std::sqrt(vector2Length(v1)) * std::sqrt(vector2Length(v2))) };
    cosTheta = std::max(-1.0f, std::min(1.0f, cosTheta));
    return std::acos(cosTheta);
}

Vector2 quadBezierPoint(Vector2 start, Vector2 control, Vector2 end, float t)
{
    t = std::max(0.0f, std::min(t, 1.0f));
    float u{ 1.0f - t };
    float tt{ t * t };
    float uu{ u * u };

    return {
        uu * start.x + 2 * t * u * control.x + tt * end.x,
        uu * start.y + 2 * t * u * control.y + tt * end.y
    };
}

bool lineIntersection(Vector2 p1, Vector2 dir1, Vector2 p2, Vector2 dir2, Vector2& intersectionPoint)
{
    float det{ dir1.x * dir2.y - dir1.y * dir2.x };
    if (std::abs(det) < 1e-3f) return false; // lines parallel

    Vector2 diff{ p2 - p1 };
    float t{ (diff.x * dir2.y - diff.y * dir2.x) / det };
    intersectionPoint = p1 + dir1 * t;
    return true;
}
