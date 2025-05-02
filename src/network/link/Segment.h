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

	/** How many lanes are to the left of the centerline */
	int m_centerlineOffset{ 0 };

public:
	/**
	* @brief constructor assumes segment spans the whole link - used when creating a new link
	*/
	Segment();

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

