#include "Vertex.h"

Vertex::Vertex(Vector2 position) : m_position{ position } {}

Vector2 Vertex::getPosition() const
{
	return m_position;
}