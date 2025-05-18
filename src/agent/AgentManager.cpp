#include "AgentManager.h"

void AgentManager::update(float deltaTime, Network* network)
{
	for (auto& vehicle : vehicles_)
	{
		vehicle.get()->update(deltaTime, network);
	}
}

const std::vector<Vehicle*> AgentManager::getVehicles() const
{
	std::vector<Vehicle*> vehicles;
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
