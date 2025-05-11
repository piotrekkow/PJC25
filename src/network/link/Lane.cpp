#include "Lane.h"
#include "utils.h"
#include <algorithm> // For std::max, std::min

Lane::Lane(int id, Link* parent)
	: id_ { id }
	, parent_ { parent }
{
}

const Link* Lane::parent() const
{
	return parent_;
}

const Vector2 Lane::endPosition() const
{
	return parent_->getTargetPosition() + parent_->normal() * static_cast<float>(id_) * parent_->getLaneWidth();
}

const Vector2 Lane::startPosition() const
{
	return parent_->getSourcePosition() + parent_->normal() * static_cast<float>(id_) * parent_->getLaneWidth();
}

const float Lane::length() const {
    return parent_->length();
}

Vector2 Lane::tangentAtDistance(float distance) const {
    Vector2 tangent = endPosition() - startPosition();
    if (vector2Length(tangent) < 1e-3f) {
        if (parent_ && parent_->length() > 0.0001f) {
            return vector2Normalize(parent_->getTargetPosition() - parent_->getSourcePosition());
        }
        return { 1.0f, 0.0f };
    }
    return vector2Normalize(tangent);
}

Vector2 Lane::positionAtDistance(float distance) const {
    float clampedDistance = std::max(0.0f, std::min(distance, length()));
    if (length() < 1e-3f) {
        return startPosition();
    }
    return startPosition() + tangentAtDistance(0.0f) * clampedDistance;
}