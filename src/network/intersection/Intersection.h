#pragma once

#include "Link.h"
#include "Connection.h"
#include <vector>
#include <memory>

class Link;
class Connection;
class Lane;

class Intersection
{
	std::vector<Link*> incomingLinks_;
	std::vector<Link*> outgoingLinks_;
	std::vector<std::unique_ptr<Connection>> connections_;
	// std::unique_ptr<trafficLightController> trafficLightController_;

public:
	Intersection() = default;
	void addIncomingLink(Link* link);
	void addOutgoingLink(Link* link);
	Connection* addConnection(Lane* inlet, Lane* outlet);
	const std::vector<Connection*> getConnections() const;
};

