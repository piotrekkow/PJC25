#pragma once
#include "Connection.h"
#include <optional>

class Connection;

enum class TrafficPriority
{
	STOP,
	YIELD,
	PRIORITY
};

class CollisionArea
{
	Connection* thisConnection_;
	Connection* collidingConnection_;
	TrafficPriority priority_;
	/// distance to collision point from the start of thisConnection
	float collisionDistance_;

public:
	CollisionArea(Connection* thisConnection, Connection* collidingConnection, float collisionDistance, std::optional<TrafficPriority> priority);
	const float collisionDistance() const;
};

