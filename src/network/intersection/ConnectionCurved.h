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
    ConnectionCurved(Lane* inletLane, Lane* outletLane, Vector2 controlPoint);
    ~ConnectionCurved() override = default;

    const float length() const override;
    Vector2 positionAtDistance(float distance) const override;
    Vector2 tangentAtDistance(float distance) const override;

private:
    void calculatePath(int numberOfSegments);
};

