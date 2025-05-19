#pragma once
#include <raylib.h>

/**
* @brief Base class for traversable objects one vehicle wide
*/
class Segment
{
public:
	virtual ~Segment() = default;
	virtual const float length() const = 0;
	virtual Vector2 positionAtDistance(float distance) const = 0;
	virtual Vector2 tangentAtDistance(float distance) const = 0;
	virtual const Vector2 startPosition() const;
	virtual const Vector2 endPosition() const;
};

