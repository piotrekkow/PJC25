#pragma once
#include "Intersection.h"

class Network
{
	std::vector<std::unique_ptr<Intersection>> m_intersections;
	std::vector<std::unique_ptr<Link>> m_links;

public:
	Network();
	
	Link* addLink(Vector2 startPosition, Vector2 targetPosition);
	const std::vector<Link*> getLinks() const;
};


