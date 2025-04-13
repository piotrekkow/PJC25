#pragma once
#include <memory>
#include <vector>
#include "Segment.h"
#include "Vertex.h"
#include "utils.h"

class Segment;

class Node
{
	/** Vertices represent points to whcih lanes (edges) are attached to in a node */
	std::vector<std::unique_ptr<Vertex>> m_vertices;

	/** Segment outgoing from this node. This node owns this segment. There can only be one such segment. Doesn't have to exist. */
	std::unique_ptr<Segment> m_out{ nullptr };

	/** Segment incoming into this node. This node does not own this segment. There can only be one such segment. Doesn't have to exist. */
	Segment* m_in{ nullptr };

	/** Center point of the node */
	Vector2 m_position;

	/** Direction the node is facing, tangent to the incoming and outgoing edges */
	Vector2 m_tangent;

public:
	/**
	 * @brief Node constructor
	 * @param position Position of the node
	 * @param tangent Tangent of the node, eg the direction it's facing: useful for node connection logic (curved segments, are nodes colinnear, etc)
	 * @param size Number of lanes (vertices in a node)
	 */
	Node(Vector2 position, Vector2 tangent, int size);

	Segment* addOutSegment(Node* destination);
	void setInSegment(Segment* segment);
	size_t getSize() const;

	// otherwise cannot deduce return type
	auto getVertices() const
	{
		return pointerView(m_vertices);
	}

	Segment* getOutSegment() const;
	Vector2 getPosition() const;

private:
	template<typename T>
	Vertex* addVertex(Vector2 position)
	{
		std::unique_ptr<T> vertex = std::make_unique<T>(position);
		m_vertices.emplace_back(std::move(vertex));
		return m_vertices.back().get();
	}

	void fillNode(int size);
	Vector2 normal(); // perpendicular to tangent
};

