#include "AgentManager.h"

void AgentManager::update(float deltaTime, Network* network, AgentManager* self)
{
	for (auto& vehicle : vehicles_)
	{
		vehicle.get()->update(deltaTime, network, self);
	}
}

const std::vector<const Vehicle*> AgentManager::getVehicles() const
{
	std::vector<const Vehicle*> vehicles;
	for (auto& vehicle : vehicles_)
	{
		vehicles.emplace_back(vehicle.get());
	}
	return vehicles;
}

Vehicle* AgentManager::addVehicle(Segment* initialSegment)
{
	vehicles_.emplace_back(std::make_unique<Vehicle>(initialSegment));
	return vehicles_.back().get();
}
