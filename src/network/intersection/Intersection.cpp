#include "Intersection.h"
#include "utils.h"
#include "ConnectionStraight.h"
#include "ConnectionCurved.h"
#include "Connection.h"
#include <cmath>

void Intersection::addIncomingLink(Link* link)
{
	incomingLinks_.emplace_back(link);
}

void Intersection::addOutgoingLink(Link* link)
{
	outgoingLinks_.emplace_back(link);
}

Connection* Intersection::addConnection(Lane* inlet, Lane* outlet, float angleThreshold)
{
	float turnAngle{ vector2Angle(inlet->tangentAtDistance(0.0f), outlet->tangentAtDistance(0.0f)) };
	if (std::abs(turnAngle) > angleThreshold && vector2Distance(inlet->endPosition(), outlet->startPosition()) > 1.0f)
	{
		Vector2 controlPoint;
		bool tangentsIntersect{ lineIntersection(inlet->endPosition(), inlet->tangentAtDistance(0.0f), outlet->startPosition(), outlet->tangentAtDistance(0.0f), controlPoint) };
		
		if (tangentsIntersect)
		{
			connections_.emplace_back(std::make_unique<ConnectionCurved>(inlet, outlet, controlPoint));
			return connections_.back().get();
		}
	}

	connections_.emplace_back(std::make_unique<ConnectionStraight>(inlet, outlet));
	return connections_.back().get();
	
}

const std::vector<Connection*> Intersection::getConnections() const
{
	std::vector<Connection*> connections;
	for (auto& connection : connections_)
	{
		connections.emplace_back(connection.get());
	}
	return connections;
}
