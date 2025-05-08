#include "Network.h"

Network::Network()
{
}

Intersection* Network::addIntersection()
{
	intersections_.emplace_back(std::make_unique<Intersection>());
	return intersections_.back().get();
}

Link* Network::addLink(Vector2 sourcePosition, Vector2 targetPosition, Intersection* sourceIntersection, Intersection* targetIntersection)
{
	links_.emplace_back(std::make_unique<Link>(sourcePosition, sourceIntersection, targetPosition, targetIntersection));
	return links_.back().get();
}

const std::vector<Link*> Network::getLinks() const
{
	std::vector<Link*> links;
	for (auto& link : links_)
	{
		links.emplace_back(link.get());
	}
	return links;
}

const std::vector<Intersection*> Network::getIntersections() const
{
	std::vector<Intersection*> intersections;
	for (auto& intersection : intersections_)
	{
		intersections.emplace_back(intersection.get());
	}
	return intersections;
}
