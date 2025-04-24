#include "Network.h"

Network::Network()
{
}

Link* Network::addLink(Vector2 startPosition, Vector2 targetPosition)
{
	m_links.emplace_back(std::make_unique<Link>(startPosition, targetPosition));
	return m_links.back().get();
}

const std::vector<Link*> Network::getLinks() const
{
	std::vector<Link*> links;
	for (auto& link : m_links)
	{
		links.emplace_back(link.get());
	}
	return links;
}
