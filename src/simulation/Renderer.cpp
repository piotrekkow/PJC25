#include "Renderer.h"
#include "config.h"
#include <ranges>
#include <string>

Renderer::Renderer(const Network* network) : m_network{ network }
{
}

void Renderer::render()
{
	for (Road* road : m_network->getRoads())
	{
		renderRoad(road);
		if (m_isDebugMode)
		{
			for (int i = 0; i < road->getSource()->getSize(); ++i)
			{
				Vertex* vertex{ getNth(road->getSource()->getVertices(), i) };
				DrawCircleV(vertex->getPosition(), VERTEX_RADIUS, VERTEX_COLOR);
				DrawText(std::to_string(i).c_str(), static_cast<int>(vertex->getPosition().x + VERTEX_RADIUS), static_cast<int>(vertex->getPosition().y + VERTEX_RADIUS), 20, BLACK);
			}
			for (int i = 0; i < road->getDestination()->getSize(); ++i)
			{
				Vertex* vertex{ getNth(road->getDestination()->getVertices(), i) };
				DrawCircleV(vertex->getPosition(), VERTEX_RADIUS, VERTEX_COLOR);
				DrawText(std::to_string(i).c_str(), static_cast<int>(vertex->getPosition().x + VERTEX_RADIUS), static_cast<int>(vertex->getPosition().y + VERTEX_RADIUS), 20, BLACK);
			}
			drawArrow(road->getSource()->getPosition(), road->getDestination()->getPosition(), 2, BLUE);
			for (auto outSegment : road->getDestination()->getOutSegments())
			{
				drawArrow(road->getDestination()->getPosition(), outSegment->getDestination()->getPosition(), 2, BLUE);
			}
		}
	}
}

bool Renderer::toggleDebug()
{
	m_isDebugMode = !m_isDebugMode;
	return m_isDebugMode;
}

void Renderer::renderRoad(const Road* road)
{
	auto firstOutSegments{ road->getSource()->getOutSegments() };
	auto secondOutSegments{ road->getDestination()->getOutSegments() };
	
	for (auto segment : firstOutSegments) // for (auto segment : std::views::concat(firstOutSegments, secondOutSegments)
	{
		renderSegment(segment);
	}
	for (auto segment : secondOutSegments)
	{
		renderSegment(segment);
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

void Renderer::drawArrow(Vector2 start, Vector2 end, float lineWidth, Color color)
{
	DrawLineEx(start, end, lineWidth, color);

	Vector2 direction = vector2Normalize(end - start);

	float arrowSize = 10.0f;
	float arrowAngle = 30.0f * DEG2RAD;

	Vector2 leftWing = {
		direction.x * cosf(arrowAngle) - direction.y * sinf(arrowAngle),
		direction.x * sinf(arrowAngle) + direction.y * cosf(arrowAngle)
	};

	Vector2 rightWing = {
		direction.x * cosf(-arrowAngle) - direction.y * sinf(-arrowAngle),
		direction.x * sinf(-arrowAngle) + direction.y * cosf(-arrowAngle)
	};

	leftWing = -arrowSize * leftWing;
	rightWing = -arrowSize * rightWing;

	Vector2 arrowBase = end - direction * VERTEX_RADIUS;

	DrawLineEx(arrowBase, arrowBase + leftWing, lineWidth, color);
	DrawLineEx(arrowBase, arrowBase + rightWing, lineWidth, color);
}
