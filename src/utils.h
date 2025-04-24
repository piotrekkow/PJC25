#pragma once
#include <raylib.h>

// Vector2 utilities
Vector2 operator+(const Vector2& v1, const Vector2& v2);
Vector2 operator-(const Vector2& v1, const Vector2& v2);
Vector2 operator*(const Vector2& v, float scalar);
Vector2 operator*(float scalar, const Vector2& v);
Vector2 operator/(const Vector2& v, float scalar);
Vector2& operator+=(Vector2& v1, const Vector2& v2);
Vector2& operator-=(Vector2& v1, const Vector2& v2);
float vector2Length(const Vector2& v);
float vector2Distance(const Vector2& v1, const Vector2& v2);
Vector2 vector2Normalize(const Vector2& v);
bool operator==(const Vector2& v1, const Vector2& v2);
bool operator!=(const Vector2& v1, const Vector2& v2);
Vector2 normalizedTangent(const Vector2& v1, const Vector2& v2);
Vector2 operator-(const Vector2& v);
Vector2 tangent2Normal(const Vector2& tangent);


//#include <ranges>
//#include <vector>
//#include <memory>
//#include <iterator>
//
//// Transform iterator for viewing pointers from smart pointer containers
//template<typename T>
//auto pointerView(const std::vector<std::unique_ptr<T>>& container) {
//    return std::views::transform(container, [](const auto& ptr) { return ptr.get(); });
//}
//
//// Random access indexing for view
//template<typename Range>
//auto getNth(Range&& range, size_t n) {
//    auto it = std::begin(range);
//    std::advance(it, n);
//    return *it;
//}