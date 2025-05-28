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
	std::vector<Connection*> previousConnections_;

public:
	Lane(int id, Link* parent);
	const Link* parent() const { return parent_; }


	const float length() const override;
	const std::vector<Vector2> geometry() const override;

	Vector2 position(float distance) const override;
	Vector2 tangent(std::optional<float> distance = std::nullopt) const override;

	const Vector2 endPosition() const override;
	const Vector2 startPosition() const override;

	const std::vector<Segment*> getNextSegments() const;
	const std::vector<Segment*> getPreviousSegments() const;

	void addNextConnection(Connection* connection) { nextConnections_.push_back(connection); }
	void addPreviousConnection(Connection* connection) { previousConnections_.push_back(connection); }
};

