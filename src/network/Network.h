#pragma once
#include "Intersection.h"
#include "Link.h"

class Network
{
	std::vector<std::unique_ptr<Intersection>> intersections_;
	std::vector<std::unique_ptr<Link>> links_;

public:
	Network();
	Intersection* addIntersection();
	Link* addLink(Vector2 sourcePosition, Vector2 targetPosition, Intersection* sourceIntersection, Intersection* targetIntersection);
	const std::vector<Link*> getLinks() const;
	const std::vector<Intersection*> getIntersections() const;
};


