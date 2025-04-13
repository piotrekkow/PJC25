#include "Simulation.h"
#include "config.h"

Simulation::Simulation(bool isPaused, float simulationSpeed)
	: m_simulationSpeed{ simulationSpeed }
	, m_isPaused{ isPaused }
{
}

Simulation::~Simulation()
{
	shutdown();
}

void Simulation::initialize()
{
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	SetTargetFPS(60);
	m_network = std::make_unique<Network>();
	m_renderer = std::make_unique<Renderer>(m_network.get());
	m_renderer->toggleDebug();

	auto r1 = m_network->addRoad({ 100, 100 }, { 100, 200 }, 2);
	auto r2 = m_network->addRoad({ 150, 600 }, { 190, 700 }, 2);
	auto r3 = m_network->addRoad({ 400, 100 }, { 320, 320 }, 1);
	m_network->connectRoad(r1, r2, 0, 1, 1);
	m_network->connectRoad(r3, r2, 0, 0, 1);
}

void Simulation::run()
{
	while (!WindowShouldClose())
	{
		if (!m_isPaused)
		{
			update();
		}
		render();
	}
}

void Simulation::update()
{
	float deltaTime{ GetFrameTime() * m_simulationSpeed };
	m_totalTime += deltaTime;
	// update vehicles here in the future
}

void Simulation::render()
{
	BeginDrawing();
	ClearBackground(BACKGROUND_COLOR);

	m_renderer->render();

	EndDrawing();
}

void Simulation::shutdown()
{
	// possible clean-up

	CloseWindow();
}

void Simulation::pause()
{
	m_isPaused = true;
}

void Simulation::unpause()
{
	m_isPaused = false;
}