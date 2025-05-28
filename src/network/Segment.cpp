#include "Segment.h"

const Vector2 Segment::startPosition() const
{
	return position(0.0f);
}

const Vector2 Segment::endPosition() const
{
	return position(length());
}
