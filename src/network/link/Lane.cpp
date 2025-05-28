#include "Lane.h"
#include "utils.h"
#include <algorithm> // For std::max, std::min

Lane::Lane(int id, Link* parent)
	: id_ { id }
	, parent_ { parent }
{
}

const std::vector<Vector2> Lane::geometry() const
{
    std::vector<Vector2> points;
    points.reserve(2);
    points.push_back(startPosition());
    points.push_back(endPosition());
	return points;
}

const float Lane::length() const
{ 
    return parent_->length();
}

const Vector2 Lane::endPosition() const
{
	return parent_->getTargetPosition() + parent_->normal() * (id_ + 0.5f) * parent_->getLaneWidth();
}

const Vector2 Lane::startPosition() const
{
	return parent_->getSourcePosition() + parent_->normal() * (id_ + 0.5f) * parent_->getLaneWidth();
}

Vector2 Lane::tangent([[maybe_unused]] std::optional<float> distance) const {
    Vector2 tangent = endPosition() - startPosition();
    if (vector2Length(tangent) < 1e-3f) {
        if (parent_ && parent_->length() > 0.0001f) {
            return vector2Normalize(parent_->getTargetPosition() - parent_->getSourcePosition());
        }
        return { 1.0f, 0.0f };
    }
    return vector2Normalize(tangent);
}

Vector2 Lane::position(float distance) const {
    float clampedDistance = std::max(0.0f, std::min(distance, length()));
    if (length() < 1e-3f) 
    {
        return startPosition();
    }
    return startPosition() + tangent(0.0f) * clampedDistance;
}


const std::vector<Segment*> Lane::getNextSegments() const
{
    std::vector<Segment*> segments;
	segments.reserve(nextConnections_.size());
    for (const auto& connection : nextConnections_) {
        segments.push_back(connection);
    }
	return segments;
}

const std::vector<Segment*> Lane::getPreviousSegments() const
{
    std::vector<Segment*> segments;
    segments.reserve(previousConnections_.size());
    for (const auto& connection : previousConnections_) {
        segments.push_back(connection);
    }
    return segments;
}
