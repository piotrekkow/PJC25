#pragma once
#include "Lane.h"
#include "Segment.h"
#include <vector>

class Lane;

class Connection :
	public Segment
{
protected:
	Lane* previousLane_;
	Lane* nextLane_;

public:
	Connection(Lane* inletLane, Lane* outletLane);
	~Connection() override = default;

	const Lane* previousLane() const;
	const Lane* nextLane() const;

	virtual Vector2 positionAtDistance(float distance) const = 0;
	virtual Vector2 tangentAtDistance(float distance) const = 0;
	const Vector2 startPosition() const override;
	const Vector2 endPosition() const override;
	virtual const std::vector<Vector2> geometry() const = 0;
};

