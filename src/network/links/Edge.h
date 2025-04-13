#pragma once
#include <raylib.h>
#include "Vertex.h"

class Vertex;

class Edge
{
	Vertex* m_source;
	Vertex* m_destination;
	float m_length;

public:
	Edge(Vertex* source, Vertex* destination);

	Vertex* getSource() const;
	Vertex* getDestination() const;
};

