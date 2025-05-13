#pragma once
#include "Lane.h"
#include "Intersection.h"
#include <raylib.h>
#include <vector>
#include <memory>

class Intersection;

/**
* @brief A road with lanes linking two intersections
*/
class Link
{
	std::vector<std::unique_ptr<Lane>> lanes_;
	Vector2 sourcePosition_;
	Vector2 targetPosition_;
	Intersection* sourceIntersection_;
	Intersection* targetIntersection_;
	float speedLimit_{ 13.8f }; // meters per second
	float laneWidth_{ 3.5f }; // meters

public:
	Link(Vector2 sourcePosition, Intersection* sourceIntersection, Vector2 targetPosition, Intersection* targetIntersection);
	const std::vector<Lane*> getLanes() const;
	const Vector2& getSourcePosition() const;
	const Vector2& getTargetPosition() const;
	const float getLaneWidth() const;
	Lane* addLane();
	const Vector2 normal() const;
	const float length() const;
};

 