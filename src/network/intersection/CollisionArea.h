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

	const float getCollisionDistance() const { return collisionDistance_; }

private:
	int priorityDifference() const;
};

