#pragma once
#include "Connection.h"
#include <algorithm>

class Lane;

class ConnectionStraight :
    public Connection
{
public:
	ConnectionStraight(Lane* inletLane, Lane* outletLane, TrafficPriority priority);
	~ConnectionStraight() override = default;

	const float length() const override;
	Vector2 positionAtDistance(float distance) const override;
	Vector2 tangentAtDistance([[maybe_unused]] float distance) const override;
	const std::vector<Vector2> geometry() const;
};

