#include "Connection.h"
#include "utils.h"
#include <iostream>
#include <algorithm>

Connection::Connection(Lane* inletLane, Lane* outletLane, TrafficPriority priority)
	: previousLane_{ inletLane }
	, nextLane_{ outletLane }
	, priority_{ priority }
{
	inletLane->addNextConnection(this);
	outletLane->addPreviousConnection(this);

	if (!previousLane_) std::cerr << "Connection pointing to a null previous lane\n";
	if (!nextLane_) std::cerr << "Connection pointing to a null next lane\n";

	checkForControlPoint();
	calculateGeometry();
}

Vector2 Connection::position(float distance) const
{
	if (totalLength_ < 0.01f) return startPosition();
	float clampedDistance = std::max(0.0f, std::min(distance, totalLength_));

	auto it{ std::lower_bound(cumulativeLengths_.begin(), cumulativeLengths_.end(), clampedDistance) };
	if (it == cumulativeLengths_.begin() && clampedDistance == 0.0f) return geometry_.front();
	if (it == cumulativeLengths_.end()) return geometry_.back();

	int index{ static_cast<int>(std::distance(cumulativeLengths_.begin(), it)) };
	float lengthIntoSegment{ clampedDistance - cumulativeLengths_[index - 1] };

	Vector2 segmentStartPoint{ geometry_[index - 1] };
	Vector2 segmentEndPoint{ geometry_[index] };
	Vector2 currentSegmentTangent{ normalizedTangent(segmentStartPoint, segmentEndPoint) };

	return segmentStartPoint + lengthIntoSegment * currentSegmentTangent;
}

Vector2 Connection::tangent(std::optional<float> distance) const
{
	if (!distance) return normalizedTangent(geometry_.front(), geometry_.back());

	float clampedDistance = std::max(0.0f, std::min(distance.value(), totalLength_));
	auto it{ std::lower_bound(cumulativeLengths_.begin(), cumulativeLengths_.end(), clampedDistance) };
	if (it == cumulativeLengths_.begin() && clampedDistance == 0.0f) return geometry_.front();
	if (it == cumulativeLengths_.end()) return nextLane_->tangent(0.0f);

	int index{ static_cast<int>(std::distance(cumulativeLengths_.begin(), it)) };

	Vector2 segmentStartPoint{ geometry_[index - 1] };
	Vector2 segmentEndPoint{ geometry_[index] };

	return normalizedTangent(segmentStartPoint, segmentEndPoint);
}

const Vector2 Connection::startPosition() const
{
	return previousLane_->endPosition();
}

const Vector2 Connection::endPosition() const
{
	return nextLane_->startPosition();
}

CollisionArea* Connection::addCollisionArea(Connection* collidingConnection, float collisionDistance)
{
	auto collisionArea = std::make_unique<CollisionArea>(this, collidingConnection, collisionDistance);
	collisionAreas_.emplace_back(std::move(collisionArea));
	return collisionAreas_.back().get();
}

const std::vector<const CollisionArea*> Connection::getCollisionAreas() const
{
	std::vector<const CollisionArea*> collisionAreas;
	for (auto& collisionArea : collisionAreas_)
	{
		collisionAreas.emplace_back(collisionArea.get());
	}
	return collisionAreas;
}

const std::vector<const CollisionArea*> Connection::getCollisionAreas(float distanceThreshold) const
{
	std::vector<const CollisionArea*> collisionAreas;
	for (auto& collisionArea : collisionAreas_)
	{
		auto ca{ collisionArea.get() };
		if (ca->getCollisionDistance() >= distanceThreshold)
		{
			collisionAreas.emplace_back(ca);
		}
	}
	return collisionAreas;
}

const std::vector<Segment*> Connection::getNextSegments() const
{
	std::vector<Segment*> nextSegments;
	nextSegments.push_back(nextLane_);
	return nextSegments;
}

const std::vector<Segment*> Connection::getPreviousSegments() const
{
	std::vector<Segment*> previousSegments;
	previousSegments.push_back(previousLane_);
	return previousSegments;
}

void Connection::checkForControlPoint(float angleThreshold)
{
	float turnAngle{ vector2Angle(previousLane_->tangent(), nextLane_->tangent()) };
	if (std::abs(turnAngle) > angleThreshold && vector2Distance(startPosition(), endPosition()) > 1.0f)
	{
		Vector2 controlPoint;
		bool tangentsIntersect{ lineIntersection(startPosition(), previousLane_->tangent(), endPosition(), nextLane_->tangent(), controlPoint)};
		if (tangentsIntersect) controlPoint_ = controlPoint;
	}
}

void Connection::calculateGeometry(std::optional<int> numberOfSegmentsPtr)
{
	geometry_.clear();
	cumulativeLengths_.clear();

	if (controlPoint_)
	{
		int numberOfSegments{ numberOfSegmentsPtr.value_or(10) };

		geometry_.reserve(numberOfSegments + 1);
		cumulativeLengths_.reserve(numberOfSegments + 1);

		cumulativeLengths_.push_back(0.0f);

		for (int i = 0; i <= numberOfSegments; i++)
		{
			float t{ static_cast<float>(i) / numberOfSegments };
			geometry_.push_back(quadBezierPoint(startPosition(), controlPoint_.value(), endPosition(), t));

			if (i > 0)
			{
				totalLength_ += vector2Distance(geometry_[i - 1], geometry_[i]);
				cumulativeLengths_.push_back(totalLength_);
			}
		}
	}
	else
	{
		if (numberOfSegmentsPtr) std::cerr << "Warning: Creating straight Connection. Number of segments is not null, but no control point is set\n";
		geometry_.push_back(startPosition());
		geometry_.push_back(endPosition());
		totalLength_ = vector2Distance(geometry_[0], geometry_[1]);
		cumulativeLengths_.push_back(0.0f);
		cumulativeLengths_.push_back(totalLength_);
	}
}
