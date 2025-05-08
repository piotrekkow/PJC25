#include "Link.h"
#include "utils.h"

Link::Link(Vector2 sourcePosition, Intersection* sourceIntersection, Vector2 targetPosition, Intersection* targetIntersection)
	: sourcePosition_{ sourcePosition }
	, targetPosition_{ targetPosition }
	, sourceIntersection_{ sourceIntersection }
	, targetIntersection_{ targetIntersection }
	, length_{ vector2Distance(sourcePosition, targetPosition) }
{
	addLane(13.8f);
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

Lane* Link::addLane(float speedLimit, float width)
{
	lanes_.emplace_back(std::make_unique<Lane>(this, speedLimit, width));
	return lanes_.back().get();
}
