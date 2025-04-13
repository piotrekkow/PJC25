#include "Node.h"
#include "config.h"
#include "Waypoint.h"

Node::Node(Vector2 position, Vector2 tangent, int size)
	: m_position { position }
	, m_tangent { tangent }
{
	fillNode(size);
}

Segment* Node::addOutSegment(Node* destination, int sourceOffset, int destinationOffset, std::optional<int> laneCount)
{
	int size{};
	if (laneCount) { size = laneCount.value(); }
	else { size = static_cast<int>(getSize()); }

	std::unique_ptr<Segment> segment = std::make_unique<Segment>(this, destination, sourceOffset, destinationOffset, size);
	m_out.emplace_back(std::move(segment));
	destination->setInSegment(m_out.back().get());
	return m_out.back().get();
}

void Node::setInSegment(Segment* segment)
{
	m_in.emplace_back(segment);
}

size_t Node::getSize() const
{
	return m_vertices.size();
}

//auto Node::getVertices() const
//{
//	return pointerView(m_vertices);
//}


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
