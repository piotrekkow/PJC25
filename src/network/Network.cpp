#include "Network.h"
#include "utils.h"

Road* Network::addRoad(Vector2 sourcePos, Vector2 destinationPos, int size)
{
	std::unique_ptr<Road> road = std::make_unique<Road>(sourcePos, destinationPos, size);
	m_roads.emplace_back(std::move(road));
	return m_roads.back().get();
}

void Network::connectRoad(Road* source, Road* destination)
{
	source->getDestination()->addOutSegment(destination->getSource());
}

//auto Network::getRoads() const
//{
//	return pointerView(m_roads);
//}

