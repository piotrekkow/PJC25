#pragma once
#include "Segment.h"
#include "Intersection.h"

class Intersection;

class Link
{
	std::vector<std::unique_ptr<Segment>> m_segments;
	std::vector<Vector2> m_geometry; // centerline geometry

	Intersection* m_startIntersection{ nullptr };
	Intersection* m_targetIntersection{ nullptr };

public:
	// Link(Intersection* startIntersection, Intersection* targetIntersection);
	Link(Vector2 centerlineStart, Vector2 centerlineEnd);
	const std::vector<Segment*> getSegments() const;

	/**
	* @brief Adds a new point along the link
	* @param geometryId at which id in m_geometry new geometry will be added
	*/
	void addGeometry(int geometryId, Vector2 position);
	const std::vector<Vector2>& getGeometry() const;
};

 