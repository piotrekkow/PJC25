#include "Vehicle.h"
#include "Driver.h"
#include "Navigator.h"
#include "utils.h"
#include <iostream>
#include <algorithm>

Vehicle::Vehicle(Segment* initialSegment, float initialSpeed, Color color)
    : currentSpeed_{ initialSpeed }
    , maxAcceleration_{ 2.0f }
	, maxDeceleration_{ 4.0f }
    , length_{ 4.5f }
    , width_{ 1.8f }
    , color_{ color }
{
    navigator_ = std::make_unique<Navigator>(this, initialSegment);
    driver_ = std::make_unique<Driver>(this, navigator_.get());
}

Vehicle::~Vehicle() = default;

void Vehicle::update(float deltaTime) 
{
    navigator_->update(deltaTime);
    driver_->update(deltaTime);
    if (navigator_->isPathComplete())
    {
        markedForDestruction_ = true;
    }
}

Vector2 Vehicle::getPosition() const
{
    return navigator_->getVehiclePosition();
}

Vector2 Vehicle::getDirection() const
{
	return navigator_->getVehicleDirection();
}