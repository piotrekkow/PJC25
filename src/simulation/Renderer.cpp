#include "Renderer.h"
#include "config.h"
#include "utils.h"
#include <ranges>
#include <string>
#include <iostream>

Renderer::Renderer(const Network* network) : network_{ network }
{
}

void Renderer::render()
{
	for (auto link : network_->getLinks())
	{
		renderLink(link);
	}
	for (auto intersection : network_->getIntersections())
	{
		renderIntersection(intersection);
	}
}

bool Renderer::toggleDebug()
{
	isDebugMode_ = !isDebugMode_;
	return isDebugMode_;
}

void Renderer::renderLink(Link* link)
{
    if (!link) {
        std::cerr << "Tried to render a link which doesn't exist.\n";
        return;
    }
	
	Vector2 linkTangent{ normalizedTangent(link->getTargetPosition(), link->getSourcePosition()) };
	Vector2 linkNormal{ tangent2Normal(linkTangent) };

	for (auto& lane : link->getLanes())
	{
		if (lane)
		{
			DrawLineEx(link->getSourcePosition(), link->getTargetPosition(), LANE_WIDTH, ROAD_COLOR);
		}
	}
	
}

void Renderer::renderIntersection(Intersection* intersection)
{
	if (!intersection) {
		std::cerr << "Tried to render an intersection which doesn't exist.\n";
	}

	if (intersection->getConnections().empty())
	{
		return;
	}

	for (auto& connection : intersection->getConnections())
	{
		if (connection)
		{
			Vector2 inletPosition = connection->getInlet()->getParent()->getTargetPosition();
			Vector2 outletPosition = connection->getOutlet()->getParent()->getSourcePosition();
			drawArrow(inletPosition, outletPosition, 2.0f, TANGENT_COLOR);
		}
	}
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
