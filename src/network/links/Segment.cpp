#include "Segment.h"
#include <iostream>
#include "utils.h"

Segment::Segment(Node* source, Node* destination)
	: m_source{ source }
	, m_destination{ destination }
{
	if (nodeSizeDifference() != 0)
	{
		std::cout << "invalid constructor used, destroying created segment.\n";
	}
	for (size_t i = 0; i < m_source->getSize(); ++i) {
		addEdge(getNth(m_source->getVertices(), i), getNth(m_destination->getVertices(), i));
		std::cout << "added edge\n";
	}
}

Node* Segment::getDestination() const
{
	return m_destination;
}

//auto Segment::getEdges() const
//{
//	return pointerView(m_edges);
//}

Edge* Segment::addEdge(Vertex* source, Vertex* destination)
{
	std::unique_ptr<Edge> edge = std::make_unique<Edge>(source, destination);
	m_edges.emplace_back(std::move(edge));
	return m_edges.back().get();
}

int Segment::nodeSizeDifference() const
{
	return static_cast<int>(m_source->getSize()) - static_cast<int>(m_destination->getSize());
}
