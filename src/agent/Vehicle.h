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
    Segment* initialSegment_;
    float distanceOnSegment_;   // m
    float currentSpeed_;        // m/s
    float targetSpeed_;         // m/s
    float acceleration_;        // m/s^2
    float length_;              // m
    float width_;               // m
    Color color_;

public:
    Vehicle(Segment* initialSegment, float initialSpeed = 10.0f, Color color = GREEN);

    void update(float deltaTime, const Network* network);

    Vector2 getPosition() const;
    Vector2 getDirection() const;
    float getLength() const { return length_; }
    float getWidth() const { return width_; }
    Color getColor() const { return color_; }

private:
    void chooseNextSegment(const Network* network);
    void updateSpeed(float deltaTime);
	void updatePosition(float deltaTime, const Network* network);
};