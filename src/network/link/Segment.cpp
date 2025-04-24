#include "Segment.h"
#include <iostream>

Segment::Segment()
{
	addLane();
}

Segment::Segment(size_t geometrySource, size_t geometryTarget)
	: m_geometrySource{ geometrySource }
	, m_geometryTarget{ geometryTarget }
{
	addLane();
}

void Segment::addLane()
{
	m_lanes.emplace_back(std::make_unique<Lane>());
	std::cout << "added lane\n";
}

void Segment::setCenterlineOffset(int newOffset)
{
	if (m_lanes.size() > newOffset)
	{
		m_centerlineOffset = newOffset;
	}
	else
	{
		std::cerr << "Failed to set new centerline offset. There has to be at least one lane to the right of the centerline.\n";
	}
}

void Segment::setGeometrySource(size_t newSource)
{
	m_geometrySource = newSource;
}

void Segment::setGeometryTarget(size_t newTarget)
{
	m_geometryTarget = newTarget;
}

const int Segment::getCenterlineOffset() const
{
	return m_centerlineOffset;
}

const int Segment::getGeometrySource() const
{
	return static_cast<int>(m_geometrySource);
}

const int Segment::getGeometryTarget() const
{
	return static_cast<int>(m_geometryTarget);
}

const std::vector<Lane*> Segment::getLanes() const
{
	std::vector<Lane*> lanes;
	for (auto& lane : m_lanes)
	{
		lanes.emplace_back(lane.get());
	}
	return lanes;
}
