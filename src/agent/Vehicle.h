#pragma once

#include "Segment.h"
#include "Lane.h"
#include "Connection.h"
#include <raylib.h>

class Renderer;
class Network;

class Vehicle
{
    Segment* currentSegment_;
    float distanceOnSegment_;
    float currentSpeed_;      // m/s
    float targetSpeed_;       // m/s
    float acceleration_;      // m/s^2
    float length_;            // meters
    float width_;             // meters
    Color color_;

public:
    Vehicle(Segment* initialSegment, float initialSpeed = 10.0f, Color color = BLUE);

    void update(float deltaTime, const Network* network);

    Vector2 getPosition() const;
    Vector2 getDirection() const;
    float getLength() const { return length_; }
    float getWidth() const { return width_; }
    Color getColor() const { return color_; }

private:
    void chooseNextSegment(const Network* network);
};