#pragma once
#include "Network.h"

class Renderer
{
	const Network* m_network;
	bool m_isDebugMode{ false };

public:
	Renderer(const Network* network);

	void render();
	bool toggleDebug();

private:
	void renderRoad(const Road* road);
	void renderSegment(const Segment* segment);
	void renderLane(const Edge* edge);
	void drawArrow(Vector2 start, Vector2 end, float lineWidth, Color color);
};

