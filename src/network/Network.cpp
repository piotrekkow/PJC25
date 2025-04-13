#include "Network.h"
#include "utils.h"

Road* Network::addRoad(Vector2 sourcePos, Vector2 destinationPos, int size)
{
	std::unique_ptr<Road> road = std::make_unique<Road>(sourcePos, destinationPos, size);
	m_roads.emplace_back(std::move(road));
	return m_roads.back().get();
}

void Network::connectRoad(Road* sourceRoad, Road* destinationRoad, int srcOffset, int dstOffset, std::optional<int> laneCount)
{
	Node* connectionSourceNode{ sourceRoad->getDestination() };
	Node* connectionDestinationNode{ destinationRoad->getSource() };
	
	if (laneCount) connectionSourceNode->addOutSegment(connectionDestinationNode, srcOffset, dstOffset, laneCount.value());
	else connectionSourceNode->addOutSegment(connectionDestinationNode, srcOffset, dstOffset);
}

//auto Network::getRoads() const
//{
//	return pointerView(m_roads);
//}

