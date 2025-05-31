#pragma once
#include <raylib.h>
#include <optional>
#include <vector>

class CollisionArea;

/**
* @brief Base class for traversable objects one vehicle wide
*/
class Segment
{
public:
	virtual ~Segment() = default;

	virtual const float length() const = 0;
	virtual const std::vector<Vector2> geometry() const = 0;
	virtual const std::vector<CollisionArea*> collisionAreas() const { return std::vector<CollisionArea*>(); }

	/// Position along the segment at a given distance
	virtual Vector2 position(float distance) const = 0;
	/// Tangenta vector along the segment at a given distance (distance can be left out for straight segments)
	virtual Vector2 tangent(std::optional<float> distance = std::nullopt) const = 0;

	virtual const Vector2 startPosition() const;
	virtual const Vector2 endPosition() const;

	virtual const std::vector<Segment*> getNextSegments() const = 0;
	virtual const std::vector<Segment*> getPreviousSegments() const = 0;
};

