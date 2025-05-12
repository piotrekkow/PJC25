#pragma once

#include "Link.h"
#include "Connection.h"
#include <vector>
#include <memory>
#include <cmath>


class Link;
class Connection;
class Lane;

/**
* @brief Road intersection between links
*/
class Intersection
{
	std::vector<Link*> incomingLinks_;
	std::vector<Link*> outgoingLinks_;
	std::vector<std::unique_ptr<Connection>> connections_;
	// std::unique_ptr<trafficLightController> trafficLightController_;

public:
	Intersection() = default;
	~Intersection();
	void addIncomingLink(Link* link);
	void addOutgoingLink(Link* link);
	Connection* addConnection(Lane* inlet, Lane* outlet, float angleThreshold = 30.0f * 3.1415f / 180/*DEG2RAD*/);
	const std::vector<Connection*> getConnections() const;
	void updateCollisionPoints();

private:
	std::vector<float> checkCollisionPoints(Connection* connection, Connection* collisionConnection);
};

