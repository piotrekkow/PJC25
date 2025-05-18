#include "Connection.h"
#include "utils.h"
#include <iostream>

Connection::Connection(Lane* inletLane, Lane* outletLane)
	: previousLane_{ inletLane }
	, nextLane_{ outletLane }
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

const Lane* Connection::previousLane() const
{
	return previousLane_;
}

const Lane* Connection::nextLane() const
{
	return nextLane_;
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

const std::vector<CollisionArea*> Connection::getCollisionAreas() const
{
	std::vector<CollisionArea*> collisionAreas;
	for (auto& collisionArea : collisionAreas_)
	{
		collisionAreas.emplace_back(collisionArea.get());
	}
	return collisionAreas;
}

TrafficPriority Connection::priority() const
{
	return priority_;
}
