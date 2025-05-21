#pragma once

#include "Segment.h"
#include "Lane.h"
#include "Connection.h"
#include <raylib.h>
#include <deque>

class Renderer;
class Network;
class AgentManager;

enum class TrafficRuleState
{
	HAS_PRIORITY,
    APPROACHING_YIELD,
	APPROACHING_STOP
};

enum class VehicleBehaviorState
{
    LEADING,
    FOLLOWING
};

class Vehicle
{
    Segment* currentSegment_;
    Segment* initialSegment_;
    float distanceOnSegment_;       // m
    float currentSpeed_;            // m/s
    float targetSpeed_;             // m/s
    const float acceleration_;      // m/s^2
    const float length_;            // m
    const float width_;             // m
    const Color color_;

public:
    Vehicle(Segment* initialSegment, float initialSpeed = 10.0f, Color color = GREEN);

    void update(float deltaTime, const Network* network, const AgentManager* agentManager);

    Vector2 getPosition() const;
    Vector2 getDirection() const;
    const float getLength() const { return length_; }
    const float getWidth() const { return width_; }
    const Color getColor() const { return color_; }

    bool isWaitingAtJunction_;      // Simplified flag, might be redundant with ruleState_
    float designatedStoppingPoint_; // Distance on currentSegment_ to stop at
    float defaultTargetSpeed_;      // Target speed when not affected by rules


private:
    void chooseNextSegment();
    void updateSpeed(float deltaTime);
	void updatePosition(float deltaTime);
    
};