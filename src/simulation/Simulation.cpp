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

	auto link1 = m_network->addLink({ 200, 200 }, { 1400, 200 });
	link1->getSegments()[0]->addLane();
	link1->getSegments()[0]->addLane();
	link1->getSegments()[0]->setCenterlineOffset(1);
	link1->addGeometry(1, { 700, 400 });
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