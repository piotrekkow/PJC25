#include "Road.h"
#include "utils.h"

Road::Road(Vector2 sourcePos, Vector2 destinationPos, int size)
{
	Vector2 roadTangent{ normalizedTangent(sourcePos, destinationPos) };

	// create nodes that define the road
	m_source = std::make_unique<Node>(sourcePos, roadTangent, size);
	m_destination = std::make_unique<Node>(destinationPos, roadTangent, size);

	// connect the nodes with a segment
	m_source->addOutSegment(m_destination.get());
}

Node* Road::getSource() const
{
	return m_source.get();
}

Node* Road::getDestination() const
{
	return m_destination.get();
}

