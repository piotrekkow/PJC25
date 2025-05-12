#include "Renderer.h"
#include "Connection.h"
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
	
	for (auto& lane : link->getLanes())
	{
		drawArrow(lane->startPosition(), lane->endPosition(), 2.0f, ROAD_COLOR);
	}
	drawArrow(link->getSourcePosition(), link->getTargetPosition(), 1.0f, BLACK);
	drawArrow(link->getTargetPosition(), link->getTargetPosition() + link->normal() * link->getLaneWidth() * static_cast<float>(link->getLanes().size()), 1.0f, PURPLE);
}

void Renderer::renderIntersection(Intersection* intersection)
{
	if (intersection) {
		if (intersection->getConnections().empty())
		{
			return;
		}

		for (auto& connection : intersection->getConnections())
		{
			if (connection)
			{
				std::vector<Vector2> geometry{ connection->geometry() };
				for (size_t i = 1; i < geometry.size(); ++i)
				{
					if (i < geometry.size() - 1)
					{
						DrawLineEx(geometry[i - 1], geometry[i], 2.0f, BLUE);
					}
					else
					{
						drawArrow(geometry[i - 1], geometry[i], 2.0f, BLUE);
					}
				}
			}
		}
		for (auto& connection : intersection->getConnections())
		{
			if (connection)
			{
				for (auto& collisionPoint : connection->getCollisionAreas())
				{
					if (collisionPoint)
					{
						Vector2 point{ connection->positionAtDistance(collisionPoint->collisionDistance()) };
						DrawCircleV(point, 3.0f, RED);
					}
				}
			}
		}
	}
	else std::cerr << "Tried to render an intersection which doesn't exist.\n";
}

void Renderer::drawArrow(Vector2 start, Vector2 end, float lineWidth, Color color)
{
	DrawLineEx(start, end, lineWidth, color);

	Vector2 direction = vector2Normalize(end - start);

	float arrowSize = lineWidth * 4.0f;
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
