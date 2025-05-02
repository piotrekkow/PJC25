#include "Link.h"

Link::Link(Vector2 centerlineStart, Vector2 centerlineEnd)
{
	m_geometry.resize(2);
	m_geometry[0] = centerlineStart;
	m_geometry[1] = centerlineEnd;

	m_segments.emplace_back(std::make_unique<Segment>());
}

const std::vector<Segment*> Link::getSegments() const
{
	std::vector<Segment*> segments;
	for (auto& segment : m_segments)
	{
		segments.emplace_back(segment.get());
	}
	return segments;
}
