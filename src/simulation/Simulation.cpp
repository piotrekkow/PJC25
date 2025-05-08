#include "Simulation.h"
#include "config.h"

Simulation::Simulation(bool isPaused, float simulationSpeed)
	: simulationSpeed_{ simulationSpeed }
	, isPaused_{ isPaused }
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
	network_ = std::make_unique<Network>();
	renderer_ = std::make_unique<Renderer>(network_.get());
	renderer_->toggleDebug();
	
	auto i1 = network_->addIntersection();
	auto i2 = network_->addIntersection();
	auto l1 = network_->addLink({ 100,100 }, { 200,100 }, i1, i2);
	auto i3 = network_->addIntersection();
	auto l2 = network_->addLink({ 300,200 }, { 300,300 }, i2, i3);
	l2->addLane();
	i2->addConnection(l1->getLanes()[0], l2->getLanes()[0]);
	auto i4 = network_->addIntersection();
	auto l3 = network_->addLink({ 400, 100 }, { 500, 100 }, i2, i4);
	i2->addConnection(l1->getLanes()[0], l3->getLanes()[0]);
}

void Simulation::run()
{
	while (!WindowShouldClose())
	{
		if (!isPaused_)
		{
			update();
		}
		render();
	}
}

void Simulation::update()
{
	float deltaTime{ GetFrameTime() * simulationSpeed_ };
	totalTime_ += deltaTime;
	// update vehicles here in the future
}

void Simulation::render()
{
	BeginDrawing();
	ClearBackground(BACKGROUND_COLOR);

	renderer_->render();

	EndDrawing();
}

void Simulation::shutdown()
{
	// possible clean-up

	CloseWindow();
}

void Simulation::pause()
{
	isPaused_ = true;
}

void Simulation::unpause()
{
	isPaused_ = false;
}