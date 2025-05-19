#pragma once

#include "Segment.h"
#include "Lane.h"
#include "Connection.h"
#include <raylib.h>

class Renderer;
class Network;

enum class VehicleState
{
    PROCEEDING,
    APPROACHING_STOP,
    APPROACHING_YIELD,
    WAITING_FOR_CLEARANCE
};

class Vehicle
{
    VehicleState state_{ VehicleState::PROCEEDING };
    Segment* currentSegment_;
    Segment* initialSegment_;
    float distanceOnSegment_;   // m
    float currentSpeed_;        // m/s
    float targetSpeed_;         // m/s
    const float acceleration_;        // m/s^2
    const float length_;              // m
    const float width_;               // m
    const Color color_;

public:
    Vehicle(Segment* initialSegment, float initialSpeed = 10.0f, Color color = GREEN);

    void update(float deltaTime, const Network* network);

    Vector2 getPosition() const;
    Vector2 getDirection() const;
    const float getLength() const { return length_; }
    const float getWidth() const { return width_; }
    const Color getColor() const { return color_; }

private:
    void chooseNextSegment(const Network* network);
    void updateSpeed(float deltaTime);
	void updatePosition(float deltaTime, const Network* network);
    void evaluate();
};