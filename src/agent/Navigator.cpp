#include "Navigator.h"
#include "Vehicle.h"
#include "CollisionArea.h"

Navigator::Navigator(Vehicle* vehicle, std::deque<Segment*> path)
    : vehicle_{ vehicle }
    , path_{ path }
{
	initializeCollisions();
}

Navigator::Navigator(Vehicle* vehicle, Segment* initialSegment)
	: Navigator(vehicle, buildPathFromSegment(initialSegment))
{
}

void Navigator::update(float deltaTime)
{
    if (isPathComplete_) return;
	updatePosition(deltaTime);
}

Vector2 Navigator::getVehiclePosition() const
{
    if (path_.empty()) return {0, 0}; // Default position if no segment
    return path_.front()->position(distanceOnCurrentSegment_);
}

Vector2 Navigator::getVehicleDirection() const
{
    if (path_.empty()) return { 1, 0 }; // Default direction if no segment
    return path_.front()->tangent(distanceOnCurrentSegment_);
}

float Navigator::updatePosition(float deltaTime)
{
    if (path_.empty())
    {
        isPathComplete_ = true;
        return 0;
    }

	float changeInPosition{ vehicle_->changeInPosition(deltaTime) };
	distanceOnCurrentSegment_ += changeInPosition;
    updateCollisionsCurrentSegment();

    float segmentLength = path_.front()->length();

    // if move to next segment
    if (distanceOnCurrentSegment_ >= segmentLength)
    {
        float overshootDistance = distanceOnCurrentSegment_ - segmentLength;
		path_.pop_front();
        if (path_.empty())
        {
			isPathComplete_ = true;
		}
		distanceOnCurrentSegment_ = overshootDistance;
        updateCollisionsCurrentSegment();
    }
	return changeInPosition;
}

void Navigator::initializeCollisions()
{
	collisions_.clear();
    for (auto& segment : path_)
    {
        for (auto& collision : segment->collisionAreas())
        {
            collisions_.push_back(collision);
		}
	}
}

void Navigator::updateCollisionsCurrentSegment()
{
    while (!collisions_.empty() && path_.front() == collisions_.front()->getConnection()) 
    {
        if (distanceOnCurrentSegment_ >= collisions_.front()->getCollisionDistance()) 
        {
            collisions_.pop_front();
        } else 
        {
            break; // No more collisions to check on this segment
        }
	}
}

std::deque<Segment*> Navigator::buildPathFromSegment(Segment* initialSegment)
{
    std::deque<Segment*> path;
    Segment* segment = initialSegment;
    path.push_back(segment);

    while (!segment->getNextSegments().empty()) {
        segment = segment->getNextSegments().front();
        path.push_back(segment);
    }

    return path;
}
