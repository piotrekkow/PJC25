#pragma once

#include "Link.h"
#include "Connection.h"
#include <vector>
#include <memory>
#include <cmath>
#include <raylib.h>

class Link;
class Connection;
class Lane;
enum class TrafficPriority;

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
	Connection* addConnection(Lane* inlet, Lane* outlet, TrafficPriority priority, float angleThreshold = 30.0f * DEG2RAD);
	const std::vector<const Connection*> getConnections() const;
	void updateCollisionPoints();

private:
	std::vector<float> checkCollisionPoints(Connection* connection, Connection* collisionConnection);
};

