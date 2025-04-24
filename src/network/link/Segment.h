#pragma once
#include <vector>
#include <memory>
#include <raylib.h>
#include "Lane.h"
#include "SegmentGeometry.h"

class Segment
{
	std::vector<std::unique_ptr<Lane>> m_lanes;
	std::unique_ptr<SegmentGeometry> m_geometry;

	/** Which indices of the m_geometry vector in Link does this Segment span */
	size_t m_geometrySource{ 0 };
	size_t m_geometryTarget{ 1 };

	/** How many lanes are to the left of the centerline */
	int m_centerlineOffset{ 0 };

public:
	/**
	* @brief constructor assumes segment spans the whole link - used when creating a new link
	*/
	Segment();

	/**
	* @brief constructor explicitly stating it's position in link
	*/
	Segment(size_t geometrySource, size_t geometryTarget);

	void addLane();
	// void removeGeometry();
	void setCenterlineOffset(int newOffset);
	void setGeometrySource(size_t newSource);
	void setGeometryTarget(size_t newTarget);

	const int getCenterlineOffset() const;
	const int getGeometrySource() const;
	const int getGeometryTarget() const;
	const std::vector<Lane*> getLanes() const;
};

