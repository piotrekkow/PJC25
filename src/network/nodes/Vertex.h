#pragma once
#include "Edge.h"

class Edge;

class Vertex
{
protected:
	Vector2 m_position;

public:
	Vertex(Vector2 position);
	virtual ~Vertex() = default;

	Vector2 getPosition() const;

	virtual bool canAddIn() = 0;
	virtual bool canAddOut() = 0;
	virtual bool addIn(Edge* inEdge) = 0;
	virtual bool addOut(Edge* outEdge) = 0;
	virtual bool removeIn(Edge* inEdge) = 0;
	virtual bool removeOut(Edge* outEdge) = 0;
};

