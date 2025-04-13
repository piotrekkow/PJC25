#pragma once
#include "Network.h"
#include "Renderer.h"

class Simulation
{
	/** Time elapsed since the beginning of the simulation */
	double m_totalTime{ 0 };

	/** Simulation speed multiplier */
	float m_simulationSpeed{ 1.0f };
	bool m_isPaused{ false };

	/** One network stores all the infrastructure */
	std::unique_ptr<Network> m_network;

	/** Renderer draws the program on the screen */
	std::unique_ptr<Renderer> m_renderer;

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

