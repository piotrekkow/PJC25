#pragma once
#include "Link.h"
#include "Connection.h"
#include "Segment.h"
#include <vector>

class Link;
// class Connection;

class Lane :
	public Segment
{
	/// Parent link
	Link* parent_;
	/// Used to determine position within the parent
	int id_;

	std::vector<Connection*> nextConnections_;

public:
	Lane(int id, Link* parent);
	const Link* parent() const;
	const Vector2 endPosition() const override;
	const Vector2 startPosition() const override;

	const float length() const override;
	Vector2 positionAtDistance(float distance) const override;
	Vector2 tangentAtDistance([[maybe_unused]] float distance) const override;
	void addNextConnection(Connection* connection);
	const std::vector<Connection*> getNextConnections() const { return nextConnections_; }
};

