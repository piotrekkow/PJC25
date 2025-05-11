#include "ConnectionStraight.h"
#include "utils.h"

ConnectionStraight::ConnectionStraight(Lane* inletLane, Lane* outletLane)
	: Connection(inletLane, outletLane)
{
}

const float ConnectionStraight::length() const
{
	return vector2Distance(startPosition(), endPosition());
}

Vector2 ConnectionStraight::positionAtDistance(float distance) const
{
	float clampedDistance{ std::max(0.0f, std::min(distance, length())) };
	return startPosition() + tangentAtDistance(distance) * clampedDistance;
}

Vector2 ConnectionStraight::tangentAtDistance(float distance) const
{
	return normalizedTangent(startPosition(), endPosition());
}

