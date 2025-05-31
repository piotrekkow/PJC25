#pragma once
#include <vector>
#include <deque>
#include "Segment.h"

class Segment;
class Vehicle;
class CollisionArea;

class Navigator
{
	std::deque<Segment*> path_;
	std::deque<CollisionArea*> collisions_;
	float distanceOnCurrentSegment_{ 0.0f };
	Vehicle* vehicle_;

public:
	Navigator(Vehicle* vehicle, std::deque<Segment*> path);
	Navigator(Vehicle* vehicle, Segment* initialSegment);
	void update(float deltaTime);

	Vector2 getVehiclePosition() const;
	Vector2 getVehicleDirection() const;

private:
	float updatePosition(float deltaTime);
	void initializeCollisions();
	void updateCollisions();
	std::deque<Segment*> buildPathFromSegment(Segment* initialSegment);
};

/*
Navigator will be updated in the future to consider alternative paths during navigation.
*/
