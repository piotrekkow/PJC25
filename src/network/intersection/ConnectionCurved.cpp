#include "ConnectionCurved.h"
#include "utils.h"
#include <iostream>

ConnectionCurved::ConnectionCurved(Lane* inletLane, Lane* outletLane, Vector2 controlPoint)
	: Connection(inletLane, outletLane)
	, controlPoint_{ controlPoint }
	, totalLength_{ 0.0f }
{
}

const float ConnectionCurved::length() const
{
	return totalLength_;
}

Vector2 ConnectionCurved::positionAtDistance(float distance) const
{
	if (totalLength_ < 0.01f) return startPosition();
	float clampedDistance = std::max(0.0f, std::min(distance, totalLength_));

	auto it{ std::lower_bound(cumulativeLengths_.begin(), cumulativeLengths_.end(), clampedDistance) };
	if (it == cumulativeLengths_.begin() && clampedDistance == 0.0f) return pathPoints_.front();
	if (it == cumulativeLengths_.end()) return pathPoints_.back();

	int index{ static_cast<int>(std::distance(cumulativeLengths_.begin(), it)) };
	float lengthIntoSegment{ clampedDistance - cumulativeLengths_[index - 1] };

	Vector2 segmentStartPoint{ pathPoints_[index - 1] };
	Vector2 segmentEndPoint{ pathPoints_[index] };
	Vector2 currentSegmentTangent{ normalizedTangent(segmentStartPoint, segmentEndPoint) };

	return segmentStartPoint + lengthIntoSegment * currentSegmentTangent;
}

Vector2 ConnectionCurved::tangentAtDistance(float distance) const
{
	float clampedDistance = std::max(0.0f, std::min(distance, totalLength_));

	auto it{ std::lower_bound(cumulativeLengths_.begin(), cumulativeLengths_.end(), clampedDistance) };
	if (it == cumulativeLengths_.begin() && clampedDistance == 0.0f) return pathPoints_.front();
	if (it == cumulativeLengths_.end()) return nextLane_->tangentAtDistance(0.0f);

	int index{ static_cast<int>(std::distance(cumulativeLengths_.begin(), it)) };

	Vector2 segmentStartPoint{ pathPoints_[index - 1] };
	Vector2 segmentEndPoint{ pathPoints_[index] };

	return normalizedTangent(segmentStartPoint, segmentEndPoint);
}

const std::vector<Vector2> ConnectionCurved::geometry() const
{
	return pathPoints_;
}

void ConnectionCurved::calculatePath(int numberOfSegments)
{
	pathPoints_.clear();
	cumulativeLengths_.clear();

	pathPoints_.reserve(numberOfSegments + 1);
	cumulativeLengths_.reserve(numberOfSegments + 1);

	cumulativeLengths_.push_back(0.0f);

	for (int i = 0; i <= numberOfSegments; i++)
	{
		float t{ static_cast<float>(i) / numberOfSegments };
		pathPoints_.push_back(quadBezierPoint(startPosition(), controlPoint_, endPosition(), t));

		if (i > 0)
		{
			totalLength_ += vector2Distance(pathPoints_[i - 1], pathPoints_[i]);
			cumulativeLengths_.push_back(totalLength_);
		}
	}
}
