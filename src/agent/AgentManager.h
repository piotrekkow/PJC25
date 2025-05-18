#pragma once  
#include <vector>  
#include <memory>  
#include "Vehicle.h"

class AgentManager  
{  
	std::vector<std::unique_ptr<Vehicle>> vehicles_;  

public:  
	void update(float deltaTime, Network* network);
	const std::vector<Vehicle*> getVehicles() const;  
	Vehicle* addVehicle(Segment* initialSegment);
};
