#include "Link.h"
#include "utils.h"

Link::Link(Vector2 sourcePosition, Intersection* sourceIntersection, Vector2 targetPosition, Intersection* targetIntersection)
	: sourcePosition_{ sourcePosition }
	, targetPosition_{ targetPosition }
	, sourceIntersection_{ sourceIntersection }
	, targetIntersection_{ targetIntersection }
{
	addLane();
}

const std::vector<Lane*> Link::getLanes() const
{
	std::vector<Lane*> lanes;
	for (auto& lane : lanes_)
	{
		lanes.emplace_back(lane.get());
	}
	return lanes;
}

const Vector2& Link::getSourcePosition() const
{
	return sourcePosition_;
}

const Vector2& Link::getTargetPosition() const
{
	return targetPosition_;
}

const float Link::getLaneWidth() const
{
	return laneWidth_;
}

Lane* Link::addLane()
{
	int id;
	if (lanes_.empty())
	{
		id = 0;
	}
	else
	{
		id = static_cast<int>(lanes_.size());
	}

	lanes_.emplace_back(std::make_unique<Lane>(id, this));
	return lanes_.back().get();
}

const Vector2 Link::getNormal() const
{
	Vector2 tangent{ normalizedTangent(sourcePosition_, targetPosition_) };
	return -tangent2Normal(tangent);
}

float Link::length()
{
	return vector2Distance(sourcePosition_, targetPosition_);
}
