#pragma once  
#include <vector>  
#include <memory>  
#include "Vehicle.h"

class AgentManager  
{  
	std::vector<std::unique_ptr<Vehicle>> vehicles_;  

public:  
	void update(float deltaTime);
	const std::vector<const Vehicle*> getVehicles() const;  
	Vehicle* addVehicle(Segment* initialSegment);
};
