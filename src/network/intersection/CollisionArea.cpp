#include "CollisionArea.h"

CollisionArea::CollisionArea(Connection* thisConnection, Connection* collidingConnection, float collisionDistance)
	: thisConnection_{ thisConnection }
	, collidingConnection_{ collidingConnection }
	, collisionDistance_{ collisionDistance }
{
}

const float CollisionArea::collisionDistance() const
{
	return collisionDistance_;
}

int CollisionArea::priorityDifference() const
{
	return static_cast<int>(thisConnection_->priority()) - static_cast<int>(collidingConnection_->priority());
}
