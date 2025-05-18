#pragma once
#include "Connection.h"

class Connection;

class CollisionArea
{
	Connection* thisConnection_;
	Connection* collidingConnection_;
	/// distance to collision point from the start of thisConnection
	float collisionDistance_;

public:
	CollisionArea(Connection* thisConnection, Connection* collidingConnection, float collisionDistance);
	const float collisionDistance() const;
private:
	int priorityDifference() const;
};

