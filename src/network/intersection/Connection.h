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
private:
	Lane* previousLane_;
	Lane* nextLane_;
	std::vector<std::unique_ptr<CollisionArea>> collisionAreas_;
	TrafficPriority priority_;
	std::vector<Vector2> geometry_;
	std::vector<float> cumulativeLengths_;
	float totalLength_;
	std::optional<Vector2> controlPoint_;

public:
	Connection(Lane* inletLane, Lane* outletLane, TrafficPriority priority);
	~Connection() override = default;

	const float length() const override { return totalLength_; }
	const std::vector<Vector2> geometry() const override { return geometry_; }

	Vector2 position(float distance) const override;
	Vector2 tangent(std::optional<float> distance = std::nullopt) const override;

	const Vector2 endPosition() const override;
	const Vector2 startPosition() const override;

	const std::vector<Segment*> getNextSegments() const;
	const std::vector<Segment*> getPreviousSegments() const;
	
	CollisionArea* addCollisionArea(Connection* collidingConnection, float collisionDistance);
	const std::vector<CollisionArea*> collisionAreas() const override;

	TrafficPriority getPriority() const { return priority_; }

private:
	void checkForControlPoint(float angleThreshold = DEG2RAD * 30.0f);
	void calculateGeometry(std::optional<int> numberOfSegmentsPtr = std::nullopt);
};

