#pragma once
#include <optional>
#include <vector>

class Vehicle;

class PercievedEnvironment
{

	std::optional<Vehicle> leadingVehicle;

public:
	PercievedEnvironment() = default;
	void update();
};

