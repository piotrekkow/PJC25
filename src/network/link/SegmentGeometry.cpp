#include "SegmentGeometry.h"

void SegmentGeometry::setPoints(std::vector<Vector2> newGeometry)
{
	m_points.clear();
	m_points.emplace_back(std::make_unique<SegmentPoint>(newGeometry[0]));

	for (int i = 1; i < newGeometry.size() - 1; i++)
	{
		m_points.emplace_back(std::make_unique<SegmentPoint>(newGeometry[i-1], newGeometry[i], newGeometry[i+1]));
	}

	m_points.emplace_back(std::make_unique<SegmentPoint>(newGeometry[newGeometry.size() - 1]));

	for (const auto& point : newGeometry)
	{
		m_points.emplace_back(std::make_unique<SegmentPoint>(point));
	}

}
