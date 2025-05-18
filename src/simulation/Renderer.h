#pragma once
#include <raylib.h>
#include <AgentManager.h>
#include <Network.h>

class Renderer
{
	const Network* network_;
	const AgentManager* agentManager_;
	bool isDebugMode_{ false };

public:
	Renderer(const Network* network, const AgentManager* agentManager);

	void render(Camera2D& camera);
	void renderPauseOverlay();
	bool toggleDebug();

	

private:
	void renderLink(Link* link) const;
	void renderLinkBoundary(Link* link, float boundaryLaneWidth = 0.3f, Color boundaryColor = ORANGE) const;
	void renderIntersection(Intersection* intersection) const;
	void renderVehicle(const Vehicle* vehicle) const;
	void drawArrow(Vector2 start, Vector2 end, float lineWidth, Color color) const;
};

