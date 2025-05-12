#include "CollisionArea.h"

CollisionArea::CollisionArea(Connection* thisConnection, Connection* collidingConnection, float collisionDistance, std::optional<TrafficPriority> priority)
	: thisConnection_{ thisConnection }
	, collidingConnection_{ collidingConnection }
	, collisionDistance_{ collisionDistance }
{
	if (priority.has_value())
	{
		priority_ = priority.value();
	}
	else
	{
		priority_ = TrafficPriority::STOP;
	}
}

const float CollisionArea::collisionDistance() const
{
	return collisionDistance_;
}
