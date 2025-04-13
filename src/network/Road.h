#pragma once
#include "Node.h"

/**
* Each road is made up from two nodes. Both nodes own their respective outgoing edges.
*/

class Road
{
	std::unique_ptr<Node> m_source;
	std::unique_ptr<Node> m_destination;

public:
	Road(Vector2 sourcePos, Vector2 destinationPos, int size);
	
	Node* getSource() const;
	Node* getDestination() const;
};

