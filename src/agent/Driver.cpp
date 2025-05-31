#include "Driver.h"
#include "Vehicle.h" // Include Vehicle for accessing its state
#include "Segment.h" // For route decisions
#include "utils.h"   // For math functions if needed
#include <algorithm> // For std::min, std::max
#include <iostream>  // For debugging

// Constants for driver behavior (can be tuned or moved to config)
constexpr float BASE_REACTION_TIME = 0.5f; // seconds
constexpr float BASE_DESIRED_HEADWAY = 2.0f; // seconds
constexpr float MIN_TARGET_SPEED = 1.0f; // m/s, to avoid complete stop unless intended

Driver::Driver(Vehicle* vehicle, Navigator* navigator, DriverBehavior profile)
	: navigator_{ navigator }
	, vehicle_{ vehicle }
    , reactionTime_{ 0.5f }
	, desiredHeadwayTime_{ 2.0f }
	, timeSinceLastDecision_{ 0.0f }
	, currentTargetSpeed_{ 0.0f }
	, behavior_{ profile }
{
    if (!vehicle_) 
    {
        std::cerr << "Driver created without a vehicle to control!" << std::endl;
    }
    if (!navigator_) 
    {
        std::cerr << "Driver created without a navigator!" << std::endl;
	}
    
    // set_profile_parameters(profile);
}
/*
void Driver::set_profile_parameters(DriverBehavior profile) {
    profile_ = profile;
    switch (profile) {
    case DriverBehavior::CAUTIOUS:
        reaction_time_ = BASE_REACTION_TIME * 1.5f;
        desired_headway_time_ = BASE_DESIRED_HEADWAY * 1.2f;
        aggressiveness_factor_ = 0.2f;
        patience_threshold_ = 10.0f; // seconds
        break;
    case DriverBehavior::NORMAL:
        reaction_time_ = BASE_REACTION_TIME;
        desired_headway_time_ = BASE_DESIRED_HEADWAY;
        aggressiveness_factor_ = 0.5f;
        patience_threshold_ = 5.0f;
        break;
    case DriverBehavior::AGGRESSIVE:
        reaction_time_ = BASE_REACTION_TIME * 0.7f;
        desired_headway_time_ = BASE_DESIRED_HEADWAY * 0.8f;
        aggressiveness_factor_ = 0.8f;
        patience_threshold_ = 2.0f;
        break;
    }
}
*/

void Driver::update(float deltaTime) 
{
    timeSinceLastDecision_ += deltaTime;

    // Simplified: make decisions every reaction_time interval
    if (timeSinceLastDecision_ >= reactionTime_) {
        // perceive_and_interpret(environment);
        // make_longitudinal_decision(environment);
        // make_lateral_decision(environment);
        // make_route_decision(environment); // TODO
        timeSinceLastDecision_ = 0.0f;
    }

    // The Vehicle class will then use get_desired_acceleration(), etc.
    // to adjust its actual acceleration and speed based on its physics.
}
/*
void Driver::perceive_and_interpret([[maybe_unused]] const PerceivedEnvironment& environment) {
    // For now, perception is directly passed.
    // This function could involve more complex interpretation in the future,
    // e.g., predicting other vehicles' actions, assessing risk.
}

void Driver::make_longitudinal_decision(const PerceivedEnvironment& environment) {
    if (!controlled_vehicle_) return;

    float safe_following_distance = desired_headway_time_ * controlled_vehicle_->getCurrentSpeed(); // getCurrentSpeed() needed in Vehicle
    float new_target_speed = environment.current_segment_speed_limit * (1.0f + (aggressiveness_factor_ - 0.5f) * 0.2f); // Aggressive drivers might speed a bit

    if (environment.leadingVehicle.has_value() && environment.distanceToLeadingVehicle.has_value()) {
        float distance_to_leader = environment.distanceToLeadingVehicle.value();
        float leader_speed = environment.speedOfLeadingVehicle.value_or(0.0f);

        // Simple IDM (Intelligent Driver Model) like logic concept:
        // Adjust speed to maintain headway and match leader's speed if closer than desired headway.
        if (distance_to_leader < safe_following_distance + controlled_vehicle_->getLength()) {
            // Too close, try to match leader's speed or decelerate.
            // This is a simplified target speed adjustment. A proper IDM calculates acceleration directly.
            new_target_speed = std::min(new_target_speed, leader_speed);
        }

        // More advanced: Calculate desired acceleration based on IDM or other car-following models.
        // For now, we just set a target speed and let vehicle handle acceleration.
        // Example placeholder for direct acceleration calculation:
        // desired_acceleration_ = calculate_idm_acceleration(controlled_vehicle_->getCurrentSpeed(), new_target_speed, distance_to_leader, leader_speed);
    }

    current_target_speed_ = std::max(MIN_TARGET_SPEED, new_target_speed); // Don't go below a minimum speed unless stopping

    // Based on the difference between current_target_speed_ and vehicle's current speed,
    // the Vehicle will determine its acceleration.
    // Or, this function could directly calculate desired_acceleration_.
    // Let's try to set desired_acceleration_ more directly for now.

    float speed_diff = current_target_speed_ - controlled_vehicle_->getCurrentSpeed();
    float accel_limit = controlled_vehicle_->getAcceleration(); // Assuming Vehicle has getAcceleration() for its max capability

    if (speed_diff > 0) { // Need to accelerate
        desired_acceleration_ = std::min(speed_diff / reaction_time_, accel_limit); // Simple proportional control, capped by vehicle max
    }
    else { // Need to decelerate or maintain speed
        // Simplified deceleration. More sophisticated models needed for realistic braking.
        // This should consider safe stopping distances, especially if a leader is present.
        desired_acceleration_ = std::max(speed_diff / reaction_time_, -accel_limit); // Use vehicle's max accel as braking limit for simplicity
    }

    // Safety stop / collision avoidance (very basic)
   // if (environment.potential_collision_ahead && environment.distance_to_potential_collision.value_or(FLT_MAX) < critical_distance) {
   //    desired_acceleration_ = -controlled_vehicle_->getStrongDeceleration(); // Need such method in Vehicle
   // }

}

void Driver::make_lateral_decision([[maybe_unused]] const PerceivedEnvironment& environment) {
    // Placeholder for lane change logic
    // This would check:
    // 1. Motivation (e.g., current lane too slow, need to turn soon, overtake)
    // 2. Safety (gap acceptance in target lane based on aggressiveness_factor_)
    // 3. Opportunity (is there a vehicle blocking?)
    lane_change_intention_ = 0; // No change for now
}
*/