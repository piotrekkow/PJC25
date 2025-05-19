#include "Vehicle.h"
#include "Network.h"
#include "Renderer.h"
#include "utils.h"
#include <iostream>

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
{
    if (!currentSegment_)
    {
        std::cerr << "Vehicle created with null initial segment!\n";
    }
}

void Vehicle::update(float deltaTime, [[maybe_unused]] const Network* network)
{
    if (!currentSegment_) return;

    updateSpeed(deltaTime);
    updatePosition(deltaTime, network);
}

void Vehicle::chooseNextSegment([[maybe_unused]] const Network* network)
{
	Connection* conn = dynamic_cast<Connection*>(currentSegment_);
	Lane* lane = dynamic_cast<Lane*>(currentSegment_);
    if (conn)
    {
        currentSegment_ = const_cast<Lane*>(conn->nextLane());
        distanceOnSegment_ = 0;
    }
    else if (lane)
    {
        if (!lane->getNextConnections().empty())
        {
            currentSegment_ = lane->getNextConnections()[0];
        }
        else
        {
            std::cerr << "Next lane has no connections.\n";
            currentSegment_ = initialSegment_;
        }
        distanceOnSegment_ = 0;
    }
    else
    {
        currentSegment_ = nullptr;
        std::cout << "Vehicle reached the end of it's path.\n";
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
        if (currentSpeed_ < 0)
        {
            currentSpeed_ = 0;
        }
    }
}

void Vehicle::updatePosition(float deltaTime, const Network* network)
{
    float distanceToTravel = currentSpeed_ * deltaTime;
    distanceOnSegment_ += distanceToTravel;

    float segmentLength = currentSegment_->length();

    if (distanceOnSegment_ >= segmentLength)
    {
        float overshootDistance = distanceOnSegment_ - segmentLength;
        chooseNextSegment(network);
		distanceOnSegment_ = overshootDistance;
    }
}

void Vehicle::evaluate()
{
    switch (state_)
    {
        case VehicleState::PROCEEDING:
            break;
        case VehicleState::APPROACHING_YIELD:
            auto conn{ dynamic_cast<const Connection*>(currentSegment_) };
            auto collisionAreas{ conn->getCollisionAreas() };
    }
}


Vector2 Vehicle::getPosition() const
{
    if (!currentSegment_) return { 0, 0 }; // Default position if no segment
    return currentSegment_->positionAtDistance(distanceOnSegment_);
}

Vector2 Vehicle::getDirection() const
{
    if (!currentSegment_) return { 1, 0 }; // Default direction
    return currentSegment_->tangentAtDistance(distanceOnSegment_);
}