#pragma once
#include "Connection.h"
#include <algorithm>

class Lane;

class ConnectionStraight :
    public Connection
{
public:
	ConnectionStraight(Lane* inletLane, Lane* outletLane);
	~ConnectionStraight() override = default;

	const float length() const override;
	Vector2 positionAtDistance(float distance) const override;
	Vector2 tangentAtDistance(float distance) const override;
};

