#include "Intersection.h"
#include "utils.h"
#include "ConnectionStraight.h"
#include "ConnectionCurved.h"
#include "Connection.h"
#include <cmath>

Intersection::~Intersection() = default;

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

void Intersection::updateCollisionPoints()
{
	for (auto& connection : connections_)
	{
		for (auto& collisionConnection : connections_)
		{
			if (connection.get() != collisionConnection.get())
			{
				std::vector<float> collisionPoints{ checkCollisionPoints(connection.get(), collisionConnection.get()) };
				if (collisionPoints.empty()) continue;
				else
				{
					for (auto& collisionPoint : collisionPoints)
					{
						connection->addCollisionArea(collisionConnection.get(), collisionPoint);
					}
				}
			}
		}
	}
}


std::vector<float> Intersection::checkCollisionPoints(Connection* connection, Connection* collisionConnection)
{
	std::vector<float> collisionDistances;
	float cumulativeLength{ 0.0f };
	const auto& connGeometry = connection->geometry();
	const auto& collConnGeometry = collisionConnection->geometry(); 

	if (connGeometry.size() < 2 || collConnGeometry.size() < 2) {
		return collisionDistances; // Return empty if not enough points
	}

	for (size_t i = 0; i < connGeometry.size() - 1; ++i)
	{
		Vector2 p1 = connGeometry[i];
		Vector2 p2 = connGeometry[i + 1];
		float segmentLength = vector2Distance(p1, p2);

		if (segmentLength < 1e-5f) {
			cumulativeLength += segmentLength;
			continue;
		}

		for (size_t j = 0; j < collConnGeometry.size() - 1; ++j)
		{
			Vector2 q1 = collConnGeometry[j];
			Vector2 q2 = collConnGeometry[j + 1];

			float t = lineIntersectionCap(p1, p2, q1, q2);

			if (t >= 0.0f) // lineIntersectionCap returns t >= 0 if intersects
			{
				float actualDistanceOnSegment = t * segmentLength;
				collisionDistances.push_back(cumulativeLength + actualDistanceOnSegment);
			}
		}
		cumulativeLength += segmentLength;
	}
	return collisionDistances;
}