#pragma once
#include "Lane.h"
#include "Intersection.h"
#include <vector>
#include <raylib.h>
#include <memory>

class Intersection;

class Link
{
	std::vector<std::unique_ptr<Lane>> lanes_;
	Vector2 sourcePosition_;
	Vector2 targetPosition_;
	Intersection* sourceIntersection_;
	Intersection* targetIntersection_;
	float length_;

public:
	Link(Vector2 sourcePosition, Intersection* sourceIntersection, Vector2 targetPosition, Intersection* targetIntersection);
	const std::vector<Lane*> getLanes() const;
	const Vector2& getSourcePosition() const;
	const Vector2& getTargetPosition() const;
	Lane* addLane(float speedLimit = 13.8f, float width = 3.5f);
};

 