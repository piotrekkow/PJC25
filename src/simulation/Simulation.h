#pragma once
#include "Network.h"
#include "Renderer.h"
#include "InputHandler.h"
#include "AgentManager.h"

class Simulation
{
	/** Time elapsed since the beginning of the simulation */
	double totalTime_{ 0 };

	/** Simulation speed multiplier */
	float simulationSpeed_{ 1.0f };
	bool isPaused_{ false };

	std::unique_ptr<Network> network_;
	std::unique_ptr<Renderer> renderer_;
	std::unique_ptr<InputHandler> inputHandler_;
	std::unique_ptr<AgentManager> agentManager_;
	Camera2D camera_;
	

public:
	Simulation(bool isPaused = false, float simulationSpeed = 1.0f);
	~Simulation();

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

private:
	void processCameraControls();
	void processGeneralInputs();
};

