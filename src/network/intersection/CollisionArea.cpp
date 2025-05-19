#include "CollisionArea.h"

CollisionArea::CollisionArea(Connection* thisConnection, Connection* collidingConnection, float collisionDistance)
	: thisConnection_{ thisConnection }
	, collidingConnection_{ collidingConnection }
	, collisionDistance_{ collisionDistance }
{
}

int CollisionArea::priorityDifference() const
{
	return static_cast<int>(thisConnection_->getPriority()) - static_cast<int>(collidingConnection_->getPriority());
}
