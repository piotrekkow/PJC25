#pragma once
#include "Network.h"

class Renderer
{
	const Network* m_network;

public:
	Renderer(const Network* network);

	void render();

private:
	void renderRoad(const Road* road);
	void renderSegment(const Segment* segment);
	void renderLane(const Edge* edge);
};

