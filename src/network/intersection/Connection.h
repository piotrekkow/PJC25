#pragma once
#include "Lane.h"
#include "Segment.h"
#include "CollisionArea.h"
#include <vector>
#include <memory>

class Lane;
class CollisionArea;

enum class TrafficPriority
{
	STOP,
	YIELD,
	PRIORITY
};

class Connection :
	public Segment
{
protected:
	Lane* previousLane_;
	Lane* nextLane_;
	std::vector<std::unique_ptr<CollisionArea>> collisionAreas_;
	TrafficPriority priority_;

public:
	Connection(Lane* inletLane, Lane* outletLane);
	~Connection() override = default;

	const Lane* previousLane() const;
	const Lane* nextLane() const;

	virtual Vector2 positionAtDistance(float distance) const = 0;
	virtual Vector2 tangentAtDistance(float distance) const = 0;
	virtual const std::vector<Vector2> geometry() const = 0;

	const Vector2 startPosition() const override;
	const Vector2 endPosition() const override;
	
	CollisionArea* addCollisionArea(Connection* collidingConnection, float collisionDistance);
	const std::vector<CollisionArea*> getCollisionAreas() const;

	TrafficPriority priority() const;
};

