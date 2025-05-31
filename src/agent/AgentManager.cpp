#include "AgentManager.h"

void AgentManager::update(float deltaTime)
{
	for (auto& vehicle : vehicles_)
	{
		vehicle.get()->update(deltaTime);
	}
	// std::remove_if moves the elements to be erased to the end of the container
	// and returns an iterator to the new logical end of the container.
	auto it = std::remove_if(vehicles_.begin(), vehicles_.end(),
		[](const std::unique_ptr<Vehicle>& vehicle_ptr) 
		{
			// If unique_ptr is null or vehicle requests destruction,
			return !vehicle_ptr || vehicle_ptr->isToBeDestroyed();
		});
	vehicles_.erase(it, vehicles_.end());
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
