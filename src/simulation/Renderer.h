#pragma once
#include "Network.h"

class Renderer
{
	const Network* network_;
	bool isDebugMode_{ false };

public:
	Renderer(const Network* network);

	void render(Camera2D& camera);
	void renderPauseOverlay();
	bool toggleDebug();

private:
	void renderLink(Link* link);
	void renderLinkBoundary(Link* link, float boundaryLaneWidth = 0.3f, Color boundaryColor = ORANGE);
	void renderIntersection(Intersection* intersection);
	void drawArrow(Vector2 start, Vector2 end, float lineWidth, Color color);
};

