#include "Segment.h"
#include <iostream>
#include "utils.h"

Segment::Segment(Node* source, Node* destination, int sourceOffset, int destinationOffset, int size)
	: m_source{ source }
	, m_destination{ destination }
	, m_sourceOffset{ sourceOffset }
	, m_destinationOffset{ destinationOffset }
{
	if (isProposedSegmentValid(size))
	{
		for (size_t i = 0; i < size; ++i) {
			addEdge(getNth(m_source->getVertices(), i+sourceOffset), getNth(m_destination->getVertices(), i+destinationOffset));
		}
		std::cout << "added segment\n";
	}
	else
	{
		std::cout << "invalid connection\n";
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

bool Segment::isProposedSegmentValid(int segmentSize)
{
	size_t srcSize{ m_source->getSize() };
	size_t dstSize{ m_destination->getSize() };
	
	if (srcSize - segmentSize >= 0 && dstSize - segmentSize >= 0) return true;
	else
	{
		std::cout << srcSize - segmentSize << ", " << dstSize - segmentSize << '\n';
		return false;
	}
		
}
