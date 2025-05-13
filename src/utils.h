#pragma once
#include <raylib.h>

// Vector2 utilities - operator overloading
Vector2 operator+(const Vector2& v1, const Vector2& v2);
Vector2 operator-(const Vector2& v1, const Vector2& v2);
Vector2 operator*(const Vector2& v, float scalar);
Vector2 operator*(float scalar, const Vector2& v);
Vector2 operator/(const Vector2& v, float scalar);
Vector2& operator+=(Vector2& v1, const Vector2& v2);
Vector2& operator-=(Vector2& v1, const Vector2& v2);
Vector2 operator-(const Vector2& v);
bool operator==(const Vector2& v1, const Vector2& v2);
bool operator!=(const Vector2& v1, const Vector2& v2);

// Vector2 utilities - functions
float vector2Length(Vector2 v);
float vector2Distance(Vector2 v1, Vector2 v2);
Vector2 vector2Normalize(Vector2 v);
Vector2 normalizedTangent(Vector2 v1, Vector2 v2);
Vector2 tangent2Normal(Vector2 tangent);
float det(Vector2 v1, Vector2 v2);
float dot(Vector2 v1, Vector2 v2);
float vector2Angle(Vector2 v1, Vector2 v2);

// Quad Bezier utilities
Vector2 quadBezierPoint(Vector2 start, Vector2 control, Vector2 end, float t);

bool lineIntersection(Vector2 p1, Vector2 dir1, Vector2 p2, Vector2 dir2, Vector2& intersectionPoint);
float lineIntersectionCap(Vector2 p1, Vector2 p2, Vector2 q1, Vector2 q2);