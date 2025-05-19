#include "Connection.h"
#include "utils.h"
#include <iostream>

Connection::Connection(Lane* inletLane, Lane* outletLane, TrafficPriority priority)
	: previousLane_{ inletLane }
	, nextLane_{ outletLane }
	, priority_{ priority }
{
	if (!previousLane_)
	{
		std::cerr << "Connection pointing to a null previous lane\n";
	}
	if (!nextLane_)
	{
		std::cerr << "Connection pointing to a null next lane\n";
	}
}

const Vector2 Connection::startPosition() const
{
	return previousLane()->endPosition();
}

const Vector2 Connection::endPosition() const
{
	return nextLane()->startPosition();
}

CollisionArea* Connection::addCollisionArea(Connection* collidingConnection, float collisionDistance)
{
	auto collisionArea = std::make_unique<CollisionArea>(this, collidingConnection, collisionDistance);
	collisionAreas_.emplace_back(std::move(collisionArea));
	return collisionAreas_.back().get();
}

const std::vector<const CollisionArea*> Connection::getCollisionAreas() const
{
	std::vector<const CollisionArea*> collisionAreas;
	for (auto& collisionArea : collisionAreas_)
	{
		collisionAreas.emplace_back(collisionArea.get());
	}
	return collisionAreas;
}

const std::vector<const CollisionArea*> Connection::getCollisionAreas(float distanceThreshold) const
{
	std::vector<const CollisionArea*> collisionAreas;
	for (auto& collisionArea : collisionAreas_)
	{
		auto ca{ collisionArea.get() };
		if (ca->getCollisionDistance() >= distanceThreshold)
		{
			collisionAreas.emplace_back(ca);
		}
	}
	return collisionAreas;
}
