#include "Renderer.h"
#include "config.h"

Renderer::Renderer(const Network* network) : m_network{ network }
{
}

void Renderer::render()
{
	for (Road* road : m_network->getRoads())
	{
		renderRoad(road);
	}
}

void Renderer::renderRoad(const Road* road)
{
	renderSegment(road->getSource()->getOutSegment());
	if (Segment* exSegment = road->getDestination()->getOutSegment())
	{
		renderSegment(exSegment);
	}
}

void Renderer::renderSegment(const Segment* segment)
{
	for (Edge* edge : segment->getEdges())
	{
		renderLane(edge);
	}
}

void Renderer::renderLane(const Edge* edge)
{
	DrawLineEx(edge->getSource()->getPosition(), edge->getDestination()->getPosition(), LANE_WIDTH, ROAD_COLOR);
}
