// src/vehicle/Vehicle.cpp
#include "Vehicle.h"
#include "Network.h" // Required for chooseNextSegment (if complex)
#include "Renderer.h" // For drawing (if Vehicle::draw is used directly)
#include "utils.h" // For vector operations
#include <iostream> // For debugging

Vehicle::Vehicle(Segment* initialSegment, float initialSpeed, Color color)
    : currentSegment_{ initialSegment }
    , distanceOnSegment_{ 0.0f }
    , currentSpeed_{ initialSpeed }
    , targetSpeed_{ 13.8f }
    , acceleration_{ 2.0f }
    , length_{ 4.5f }
    , width_{ 1.8f }
    , color_{ color }
{
    if (!currentSegment_) {
        std::cerr << "Vehicle created with null initial segment!\n";
    }
}

void Vehicle::update(float deltaTime, [[maybe_unused]] const Network* network)
{
    if (!currentSegment_) return;

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

    float distanceToTravel = currentSpeed_ * deltaTime;
    distanceOnSegment_ += distanceToTravel;

    float segmentLength = currentSegment_->length();

    if (distanceOnSegment_ >= segmentLength) {
        // Reached the end of the segment
        float overshootDistance = distanceOnSegment_ - segmentLength;

        // Attempt to find the next segment
        // For now, let's try to get the next connected lane via an intersection or loop on the same lane

        // Simple placeholder: If it's a Lane, try to see if it connects to an Intersection
        // This is where more sophisticated pathfinding/decision logic is needed.
        const Lane* currentLane = dynamic_cast<const Lane*>(currentSegment_);
        const Connection* currentConnection = dynamic_cast<const Connection*>(currentSegment_);

        if (currentLane) {
            // Try to find a connection from this lane
            // This requires Network knowledge or better references within Lane/Intersection
            // For this example, we'll just reset the vehicle on the same lane or stop.
            // A real implementation would query the intersection this lane leads to.
            std::cout << "Vehicle reached end of Lane. Resetting for now." << std::endl;
            distanceOnSegment_ = 0; // Loop on the same lane
            // Or, ideally: chooseNextSegment(network); and handle overshootDistance
        }
        else if (currentConnection) {
            // If it's a connection, move to its nextLane
            currentSegment_ = const_cast<Lane*>(currentConnection->nextLane());
            if (currentSegment_) {
                distanceOnSegment_ = overshootDistance;
                // Adjust distance if it overshot into the new segment
                while (distanceOnSegment_ >= currentSegment_->length() && currentSegment_ != nullptr) {
                    float segLen = currentSegment_->length();
                    overshootDistance = distanceOnSegment_ - segLen;
                    // This part needs robust next segment selection
                    // For now, if it's still overshooting, it might get stuck or need better logic
                    const Lane* cLane = dynamic_cast<const Lane*>(currentSegment_);
                    if (cLane) { // If current is a lane, try to find a connection
                        // Placeholder: For now, let's assume we can't find a connection from here in this simple example
                        // A proper implementation would look up the intersection and connections
                        std::cout << "Vehicle at end of connection, on new lane, still overshooting. Needs better logic." << std::endl;
                        currentSegment_ = nullptr; // Stop the vehicle
                        break;
                    }
                    else { // If it's another connection, this logic is too simple
                        currentSegment_ = nullptr; // Stop the vehicle
                        break;
                    }
                }

            }
            else {
                std::cout << "Vehicle reached end of Connection, but no next lane. Stopping." << std::endl;
                currentSegment_ = nullptr; // Stop
            }
        }
        else {
            std::cout << "Vehicle reached end of unknown segment type. Stopping." << std::endl;
            currentSegment_ = nullptr; // Stop
        }
        if (currentSegment_ == nullptr) distanceOnSegment_ = 0;

    }
}

// This is a placeholder for choosing the next segment.
// Realistic behavior requires access to Network, Intersection connections,
// and possibly a destination or route for the vehicle.
void Vehicle::chooseNextSegment([[maybe_unused]] const Network* network)
{
    // Logic:
    // 1. If currentSegment_ is a Lane, find the Intersection it leads to.
    // 2. At the Intersection, list available Connections.
    // 3. Based on routing logic (e.g., random, shortest path, turn intention), select a Connection.
    // 4. Set currentSegment_ to the chosen Connection.
    //
    // 5. If currentSegment_ is a Connection, its nextLane_ is the next segment.
    //    Set currentSegment_ to nextLane_.

    // For now, just as an example, if it's a Lane, it stops.
    // If it's a connection, it takes the next lane.
    const Connection* conn = dynamic_cast<const Connection*>(currentSegment_);
    if (conn) {
        currentSegment_ = const_cast<Lane*>(conn->nextLane());
        distanceOnSegment_ = 0; // Reset distance for the new segment
        if (!currentSegment_) {
            std::cerr << "Vehicle tried to move to a null next lane from a connection." << std::endl;
        }
    }
    else {
        // If it's a Lane, or any other segment type, it stops for this simple example.
        std::cout << "Vehicle reached end of segment and no connection logic implemented for this segment type yet. Stopping." << std::endl;
        currentSegment_ = nullptr;
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