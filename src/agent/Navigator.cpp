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
	updatePosition(deltaTime);
	updateCollisions();
}

Vector2 Navigator::getVehiclePosition() const
{
    if (!path_.empty()) return {0, 0}; // Default position if no segment
    return path_.front()->position(distanceOnCurrentSegment_);
}

Vector2 Navigator::getVehicleDirection() const
{
    if (path_.empty()) return { 1, 0 }; // Default direction if no segment
    return path_.front()->tangent(distanceOnCurrentSegment_);
}

float Navigator::updatePosition(float deltaTime)
{
	float changeInPosition{ vehicle_->changeInPosition(deltaTime) };
	distanceOnCurrentSegment_ += changeInPosition;

    float segmentLength = path_.front()->length();

    if (distanceOnCurrentSegment_ >= segmentLength)
    {
        float overshootDistance = distanceOnCurrentSegment_ - segmentLength;
		path_.pop_front();
        if (path_.empty())
        {
            // ...
		}
		distanceOnCurrentSegment_ = overshootDistance;
    }
	return changeInPosition;
}

void Navigator::initializeCollisions()
{
    std::deque<CollisionArea*> collisions;
    for (auto& segment : path_)
    {
        for (auto& collision : segment->collisionAreas())
        {
            collisions.push_back(collision);
		}
	}
}

void Navigator::updateCollisions()
{
    if (distanceOnCurrentSegment_ >= collisions_.front()->getCollisionDistance())
    {
        collisions_.pop_front();
        // pop any past collisions
        while (collisions_.front()->getCollisionDistance() < distanceOnCurrentSegment_)
        {
            collisions_.pop_front();
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
