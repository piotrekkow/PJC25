#include "Node.h"
#include "config.h"
#include "Waypoint.h"

Node::Node(Vector2 position, Vector2 tangent, int size)
	: m_position { position }
	, m_tangent { tangent }
{
	fillNode(size);
}

Segment* Node::addOutSegment(Node* destination)
{
	m_out = std::make_unique<Segment>(this, destination);
	destination->setInSegment(m_out.get());
	return m_out.get();
}

void Node::setInSegment(Segment* segment)
{
	m_in = segment;
}

size_t Node::getSize() const
{
	return m_vertices.size();
}

//auto Node::getVertices() const
//{
//	return pointerView(m_vertices);
//}

Segment* Node::getOutSegment() const
{
	return m_out.get();
}

Vector2 Node::getPosition() const
{
	return m_position;
}

void Node::fillNode(int size)
{
	Vector2 step{ normal() * LANE_WIDTH };
	Vector2 cursor{ m_position };
	for (int i = 0; i < size; ++i)
	{
		addVertex<Waypoint>(cursor);
		cursor += step;
	}
}

Vector2 Node::normal()
{
	return { -m_tangent.y, m_tangent.x };
}
