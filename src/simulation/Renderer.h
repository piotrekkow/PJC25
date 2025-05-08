#pragma once
#include "Network.h"

class Renderer
{
	const Network* network_;
	bool isDebugMode_{ false };

public:
	Renderer(const Network* network);

	void render();
	bool toggleDebug();

private:
	void renderLink(Link* link);
	void renderIntersection(Intersection* intersection);
	void drawArrow(Vector2 start, Vector2 end, float lineWidth, Color color);
};

