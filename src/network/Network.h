#pragma once
#include "Intersection.h"
#include "Link.h"

/**
* @brief Manages all the infrastructure - the road network
*/
class Network
{
	std::vector<std::unique_ptr<Intersection>> intersections_;
	std::vector<std::unique_ptr<Link>> links_;

public:
	Network();
	// make addIntersection and addLink private in the future and have some interface for adding roads
	Intersection* addIntersection();
	Link* addLink(Vector2 sourcePosition, Vector2 targetPosition, Intersection* sourceIntersection, Intersection* targetIntersection);
	const std::vector<const Link*> getLinks() const;
	const std::vector<const Intersection*> getIntersections() const;
};


