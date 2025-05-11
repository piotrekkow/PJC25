#include "Segment.h"

const Vector2 Segment::startPosition() const
{
	return positionAtDistance(0.0f);
}

const Vector2 Segment::endPosition() const
{
	return positionAtDistance(length());
}
