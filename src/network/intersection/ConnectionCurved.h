#pragma once
#include "Connection.h"
#include <vector>
#include <raylib.h>

class Lane;

class ConnectionCurved :
    public Connection
{
    std::vector<Vector2> pathPoints_;
    std::vector<float> cumulativeLengths_;

    Vector2 controlPoint_;
    float totalLength_;

public:
    ConnectionCurved(Lane* inletLane, Lane* outletLane, TrafficPriority priority, Vector2 controlPoint);
    ~ConnectionCurved() override = default;
    
    Vector2 positionAtDistance(float distance) const override;
    Vector2 tangentAtDistance(float distance) const override;

    const float length() const override { return totalLength_; }
    const std::vector<Vector2> geometry() const { return pathPoints_; }

private:
    void calculatePath(int numberOfSegments);
};

