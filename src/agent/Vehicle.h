#pragma once

#include "Segment.h"
#include <raylib.h>
#include <deque>
#include <memory>

class Driver;
class Navigator;

enum class TrafficRuleState
{
	HAS_PRIORITY,
    APPROACHING_YIELD,
	APPROACHING_STOP
};

class Vehicle
{
    std::unique_ptr<Driver> driver_;
    std::unique_ptr<Navigator> navigator_;

    float currentSpeed_;                    // m/s
    const float maxAcceleration_;           // m/s^2
	const float maxDeceleration_;           // m/s^2
    const float length_;                    // m
    const float width_;                     // m
    const Color color_;

public:
    Vehicle(Segment* initialSegment, float initialSpeed = 10.0f, Color color = GREEN);

    void update(float deltaTime);

    Vector2 getPosition() const;
    Vector2 getDirection() const;
    const float getLength() const { return length_; }
    const float getWidth() const { return width_; }
    const Color getColor() const { return color_; }

    float getCurrentSpeed() const { return currentSpeed_; } // Add this getter
    float getAcceleration() const { return maxAcceleration_; } // Expose vehicle's max acceleration
	float getDeceleration() const { return maxDeceleration_; } // Expose vehicle's max deceleration

    float changeInPosition(float deltaTime) const { return currentSpeed_ * deltaTime; }

private:    
};