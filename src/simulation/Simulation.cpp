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
	
	auto i{ network_->addIntersection() };
	auto ie{ network_->addIntersection() };
	auto is{ network_->addIntersection() };
	auto iw{ network_->addIntersection() };
	auto in{ network_->addIntersection() };
	auto wlin = network_->addLink({ 100, 510 }, { 750, 510 }, ie, i);
	auto wlout = network_->addLink({ 730, 490 }, { 100, 490 }, i, ie);
	wlin->addLane();
	wlin->addLane();
	wlout->addLane();
	auto elin = network_->addLink({ 1800, 490 }, { 850, 490 }, iw, i);
	auto elout = network_->addLink({ 870, 510 }, { 1800, 510 }, i, iw);
	elin->addLane();
	elin->addLane();
	elout->addLane();
	auto nlin = network_->addLink({ 790, 100 }, { 790, 450 }, in, i);
	auto nlout = network_->addLink({ 810, 430 }, { 810, 100 }, i, in);
	nlin->addLane();
	auto slin = network_->addLink({ 810, 1000 }, { 810, 550 }, is, i);
	slin->addLane();
	slin->addLane();
	auto slout = network_->addLink({ 790, 570 }, { 790, 1000 }, i, is);
	slout->addLane();

	i->addConnection(elin->getLanes()[0], slout->getLanes()[0]);
	i->addConnection(elin->getLanes()[1], wlout->getLanes()[0]);
	i->addConnection(elin->getLanes()[2], wlout->getLanes()[1]);
	i->addConnection(elin->getLanes()[2], nlout->getLanes()[0]);

	i->addConnection(wlin->getLanes()[0], nlout->getLanes()[0]);
	i->addConnection(wlin->getLanes()[1], elout->getLanes()[0]);
	i->addConnection(wlin->getLanes()[2], elout->getLanes()[1]);
	i->addConnection(wlin->getLanes()[2], slout->getLanes()[1]);

	i->addConnection(slin->getLanes()[0], wlout->getLanes()[0]);
	i->addConnection(slin->getLanes()[0], wlout->getLanes()[1]);
	i->addConnection(slin->getLanes()[1], nlout->getLanes()[0]);
	i->addConnection(slin->getLanes()[2], elout->getLanes()[1]);

	i->addConnection(nlin->getLanes()[1], wlout->getLanes()[1]);
	i->addConnection(nlin->getLanes()[1], slout->getLanes()[1]);
	i->addConnection(nlin->getLanes()[0], slout->getLanes()[0]);
	i->addConnection(nlin->getLanes()[0], elout->getLanes()[0]);
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