#include "Edge.h"
#include "utils.h" //vector2Distance()
#include "config.h" //EDGE_COLOR

Edge::Edge(Vertex* source, Vertex* destination)
	: m_source{ source }
	, m_destination{ destination }
	, m_length{ vector2Distance(m_source->getPosition(), m_destination->getPosition()) }
{
	m_source->addOut(this);
	m_destination->addIn(this);
}

Vertex* Edge::getSource() const
{
	return m_source;
}

Vertex* Edge::getDestination() const
{
	return m_destination;
}
