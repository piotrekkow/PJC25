#pragma once
#include <memory>
#include <vector>
#include "SegmentPoint.h"

class SegmentGeometry
{
	std::vector<std::unique_ptr<SegmentPoint>> m_points;

public:
	void setPoints(std::vector<Vector2> newGeometry);
	const std::vector<SegmentPoint*> getPoints() const;
	const std::vector<Vector2> getCoordinates() const;
	void removePoint();

private:
	void updatePoints();
};

