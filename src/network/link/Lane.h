#pragma once
#include "Link.h"
#include <raylib.h>
// #include "Connection.h"

class Link;
// class Connection;

class Lane
{
	// std::vector<Connection*> nextConnections_;
	Link* parent_;
	int id_;

public:
	Lane(int id, Link* parent);
	const Link* getParent() const;
	const Vector2 getOutletPosition() const;
	const Vector2 getInletPosition() const;
};

