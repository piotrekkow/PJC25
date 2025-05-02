#pragma once
#include "Segment.h"
#include "Intersection.h"

class Intersection;

class Link
{
	std::vector<std::unique_ptr<Segment>> m_segments;

	Intersection* m_startIntersection{ nullptr };
	Intersection* m_targetIntersection{ nullptr };

public:
	// Link(Intersection* startIntersection, Intersection* targetIntersection);
	Link(Vector2 centerlineStart, Vector2 centerlineEnd);
	const std::vector<Segment*> getSegments() const;
};

 