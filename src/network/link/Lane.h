#pragma once
#include "Link.h"
// #include "Connection.h"
#include "Segment.h"

class Link;
// class Connection;

class Lane :
	public Segment
{
	/// Parent link
	Link* parent_;
	/// Used to determine position within the parent
	int id_;

public:
	Lane(int id, Link* parent);
	const Link* parent() const;
	const Vector2 endPosition() const override;
	const Vector2 startPosition() const override;

	const float length() const override;
	Vector2 positionAtDistance(float distance) const override;
	Vector2 tangentAtDistance([[maybe_unused]] float distance) const override;
};

