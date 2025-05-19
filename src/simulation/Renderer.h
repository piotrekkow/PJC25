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
	void renderNetwork() const;
	void renderAgents() const;
	void renderLink(const Link* link) const;
	void renderLinkBoundary(const Link* link, float boundaryLaneWidth = 0.3f, Color boundaryColor = ORANGE) const;
	void renderIntersection(const Intersection* intersection) const;
	void renderConnection(const Connection* connection) const;
	void renderVehicle(const Vehicle* vehicle) const;
	void drawArrow(Vector2 start, Vector2 end, float lineWidth, Color color) const;

	void renderLinkDebug(const Link* link) const;
	void renderIntersectionDebug(const Intersection* intersection) const;
	void renderConnectionDebug(const Connection* connection) const;
	void renderCollisionsDebug(const Connection* connection) const;
};