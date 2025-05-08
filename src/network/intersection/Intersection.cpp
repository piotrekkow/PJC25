#include "Intersection.h"

void Intersection::addIncomingLink(Link* link)
{
	incomingLinks_.emplace_back(link);
}

void Intersection::addOutgoingLink(Link* link)
{
	outgoingLinks_.emplace_back(link);
}

Connection* Intersection::addConnection(Lane* inlet, Lane* outlet)
{
	connections_.emplace_back(std::make_unique<Connection>(inlet, outlet));
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
