#pragma once
#include "Edge.h"
#include "Node.h"
#include "utils.h"

class Node;

class Segment
{
	/** Edges going from source to destination */
	std::vector<std::unique_ptr<Edge>> m_edges;
	Node* m_source;
	Node* m_destination;
	int m_sourceOffset;
	int m_destinationOffset;

public:
	/**
	 * @brief Simple segment constructor for when both nodes have equal sizes
	 * @param source Source node
	 * @param destination Destination node
	 */
	Segment(Node* source, Node* destination, int sourceOffset, int destinationOffset, int size);
	Node* getDestination() const;
	auto getEdges() const { return pointerView(m_edges); }

private:
	Edge* addEdge(Vertex* source, Vertex* destination);
	int nodeSizeDifference() const;
	bool isProposedSegmentValid(int segmentSize);
};

