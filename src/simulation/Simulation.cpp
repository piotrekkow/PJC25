#include "Simulation.h"
#include "config.h"
#include "utils.h"

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
	inputHandler_ = std::make_unique<InputHandler>();
	camera_.target = { 0.0f, 0.0f};
	camera_.zoom = 20.0f;

	renderer_->toggleDebug();
	
	auto i{ network_->addIntersection() };
	auto ie{ network_->addIntersection() };
	auto is{ network_->addIntersection() };
	auto iw{ network_->addIntersection() };
	auto in{ network_->addIntersection() };
	float pos1{ 20.0f };
	float len1{ 50.0f };
	auto wlin = network_->addLink({ -len1, 1 }, { -pos1, 1 }, ie, i);
	auto wlout = network_->addLink({ -pos1, -1 }, { -len1, -1 }, i, ie);
	wlin->addLane();
	wlin->addLane();
	wlout->addLane();
	auto elin = network_->addLink({ len1, -1 + 3.5f }, { pos1, -1 + 3.5f }, iw, i);
	auto elout = network_->addLink({ pos1, 1 + 3.5f }, { len1, 1 + 3.5f }, i, iw);
	elin->addLane();
	elin->addLane();
	elout->addLane();
	auto nlin = network_->addLink({ -1, -len1 }, { -1, -pos1 }, in, i);
	auto nlout = network_->addLink({ 1, -pos1 }, { 1, -len1 }, i, in);
	nlin->addLane();
	auto slin = network_->addLink({ 1, len1 }, { 1, pos1 }, is, i);
	slin->addLane();
	slin->addLane();
	auto slout = network_->addLink({ -1, pos1 }, { -1, len1 }, i, is);
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

	i->updateCollisionPoints();
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
		processGeneralInputs();
		processCameraControls();
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

	renderer_->render(camera_);
	if (isPaused_) renderer_->renderPauseOverlay();

	EndDrawing();
}

void Simulation::shutdown()
{
	// possible clean-up
	CloseWindow();
}

void Simulation::processCameraControls()
{
	if (inputHandler_->isMouseButtonDown(MOUSE_BUTTON_MIDDLE))
	{
		Vector2 delta = inputHandler_->getMouseDelta();
		delta = delta * (-1.0f / camera_.zoom);
		camera_.target = camera_.target + delta;
	}

	float wheel = inputHandler_->getMouseWheelMove();
	if (wheel != 0)
	{
		Vector2 mouseWorldPos = GetScreenToWorld2D(inputHandler_->getMousePosition(), camera_);
		camera_.offset = inputHandler_->getMousePosition();
		camera_.target = mouseWorldPos;
		float scaleFactor = 0.2f * wheel;
		camera_.zoom = std::max(0.5f, std::min(expf(logf(camera_.zoom) + scaleFactor), 50.0f));
	}
}

void Simulation::processGeneralInputs()
{
	if (inputHandler_->isKeyPressed(KEY_SPACE)) isPaused_ = !isPaused_;
}
