#include "Vehicle.h"
#include "Network.h"
#include "Renderer.h"
#include "AgentManager.h"
#include "utils.h"
#include <iostream>
#include <algorithm>

Vehicle::Vehicle(Segment* initialSegment, float initialSpeed, Color color)
    : currentSegment_{ initialSegment }
	, initialSegment_{ initialSegment }
    , distanceOnSegment_{ 0.0f }
    , currentSpeed_{ initialSpeed }
    , targetSpeed_{ 13.8f }
    , acceleration_{ 2.0f }
    , length_{ 4.5f }
    , width_{ 1.8f }
    , color_{ color }
	, isWaitingAtJunction_{ false }
{
    if (!currentSegment_)
    {
        std::cerr << "Vehicle created with null initial segment!\n";
    }
}


/*
* 1. Check if the vehicle is on a connection or lane
* 2. Check ahead set distance based on speed
* 3. Gather the set of next lanes and connections within the distance calculated earlier
* 4. Based on the above gather the set of collision areas
* 5. Check collision areas upstream a set distance which would be enough for the vehicle to leave the collision area in time
* 6. If the next collision areas are close to each other and there is not enough space to stop if needed stop before the first one
*/

void Vehicle::update(float deltaTime, [[maybe_unused]] const Network* network, [[maybe_unused]] const AgentManager* agentManager)
{
    updateSpeed(deltaTime);
    updatePosition(deltaTime);
}

void Vehicle::chooseNextSegment()
{
    std::vector<Segment*> nextSegmentOptions{ currentSegment_->getNextSegments() };
    if (!nextSegmentOptions.empty())
    {
		currentSegment_ = nextSegmentOptions[0]; // For now, just choose the first available segment
        distanceOnSegment_ = 0;
	}
    else
    {
        std::cerr << "No next segments available for the current segment.\n";
        currentSegment_ = initialSegment_;
        distanceOnSegment_ = 0;
    }
}

void Vehicle::updateSpeed(float deltaTime)
{
    if (currentSpeed_ < targetSpeed_)
    {
        currentSpeed_ += acceleration_ * deltaTime;
        if (currentSpeed_ > targetSpeed_)
        {
            currentSpeed_ = targetSpeed_;
        }
    }
    else if (currentSpeed_ > targetSpeed_)
    {
        currentSpeed_ -= acceleration_ * deltaTime;
        if (currentSpeed_ < targetSpeed_)
        {
            currentSpeed_ = targetSpeed_;
        }
        if (currentSpeed_ < 0) currentSpeed_ = 0;
    }
}

void Vehicle::updatePosition(float deltaTime)
{
    float distanceToTravel = currentSpeed_ * deltaTime;
    distanceOnSegment_ += distanceToTravel;

    float segmentLength = currentSegment_->length();

    if (distanceOnSegment_ >= segmentLength)
    {
        float overshootDistance = distanceOnSegment_ - segmentLength;
        chooseNextSegment();
		distanceOnSegment_ = overshootDistance;
    }
}

Vector2 Vehicle::getPosition() const
{
    if (!currentSegment_) return { 0, 0 }; // Default position if no segment
    return currentSegment_->position(distanceOnSegment_);
}

Vector2 Vehicle::getDirection() const
{
    if (!currentSegment_) return { 1, 0 }; // Default direction
    return currentSegment_->tangent(distanceOnSegment_);
}