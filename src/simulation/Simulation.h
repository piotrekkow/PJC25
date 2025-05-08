#pragma once
#include "Network.h"
#include "Renderer.h"

class Simulation
{
	/** Time elapsed since the beginning of the simulation */
	double totalTime_{ 0 };

	/** Simulation speed multiplier */
	float simulationSpeed_{ 1.0f };
	bool isPaused_{ false };

	std::unique_ptr<Network> network_;
	std::unique_ptr<Renderer> renderer_;

public:
	Simulation(bool isPaused = false, float simulationSpeed = 1.0f);
	~Simulation();

	// Deleted copy and move constructors/assignments
	Simulation(const Simulation&) = delete;
	Simulation& operator=(const Simulation&) = delete;
	Simulation(Simulation&&) = delete;
	Simulation& operator=(Simulation&&) = delete;

	void initialize();

	/** Runs all the time */
	void run();

	/** Updates when unpaused */
	void update();
	void render();
	void shutdown();

	void pause();
	void unpause();
};

