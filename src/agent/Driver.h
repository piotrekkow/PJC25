#pragma once

#include <raylib.h> // For Vector2, if needed for perception data directly
#include <memory>   // For std::unique_ptr if Driver owns complex sub-objects
#include <vector>   // If storing route information or lists of perceived objects
#include <optional> // For optional perception data

// Forward declarations to avoid circular dependencies
class Vehicle;
class Segment;
class Network; // If driver needs to query network-level info
class AgentManager; // If driver needs info about other agents
class Navigator;

enum class DriverBehavior {
    CAUTIOUS,
    NORMAL,
    AGGRESSIVE
};

class Driver {
    Navigator* navigator_;
	Vehicle* vehicle_;
	DriverBehavior behavior_;
     
    float reactionTime_; // could be modeled with a distribution in the future
	float desiredHeadwayTime_; // seconds (e.g., 2-second rule)
	// float patienceThreshold_; // How long to wait before attempting risky maneuvers (e.g. overtaking)
	float timeSinceLastDecision_; // Time since the last decision was made

    float currentTargetSpeed_;
	// int laneChangeIntention_; // -1 (left), 0 (none), 1 (right)


public:
    // Constructor: Takes the vehicle it controls and a profile
    Driver(Vehicle* controlled_vehicle, Navigator* navigator, DriverBehavior profile = DriverBehavior::NORMAL);

    void update(float deltaTime);


private:
    // void make_route_decision(const PerceivedEnvironment& environment); // For junctions

    // void set_profile_parameters(DriverBehavior profile);
};