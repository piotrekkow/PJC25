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

void Renderer::render(Camera2D& camera)
{
	BeginMode2D(camera);

	for (auto link : network_->getLinks())
	{
		renderLink(link);
	}
	for (auto intersection : network_->getIntersections())
	{
		renderIntersection(intersection);
	}

	EndMode2D();
}

void Renderer::renderPauseOverlay()
{
	DrawRectangleLinesEx({ 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT }, 10.0f, RED);
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
		if (!isDebugMode_) DrawLineEx(lane->startPosition(), lane->endPosition(), link->getLaneWidth(), ROAD_COLOR);
		else DrawLineEx(lane->startPosition(), lane->endPosition(), 1.0f, ROAD_COLOR);
	}
	if (isDebugMode_)
	{
		renderLinkBoundary(link);
	}
}

void Renderer::renderLinkBoundary(Link* link, float boundaryLaneWidth, Color boundaryColor)
{
	Vector2 linkSourceOffset{ link->getSourcePosition() + link->normal() * link->getLaneWidth() * static_cast<float>(link->getLanes().size()) };
	Vector2 linkTargetOffset{ link->getTargetPosition() + link->normal() * link->getLaneWidth() * static_cast<float>(link->getLanes().size()) };
	drawArrow(link->getSourcePosition(), link->getTargetPosition(), 0.3f, boundaryColor);
	drawArrow(linkSourceOffset, linkTargetOffset, 0.3f, boundaryColor);
	DrawLineEx(linkSourceOffset, link->getSourcePosition(), boundaryLaneWidth, boundaryColor);
	DrawLineEx(linkTargetOffset, link->getTargetPosition(), boundaryLaneWidth, boundaryColor);
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
					if (!isDebugMode_ && i < geometry.size())
					{
						DrawLineEx(geometry[i - 1], geometry[i], 3.5f, ROAD_COLOR);
					}
					else if (i < geometry.size() - 1)
					{
						DrawLineEx(geometry[i - 1], geometry[i], 0.3f, BLUE);
					}
					else
					{
						drawArrow(geometry[i - 1], geometry[i], 0.3f, BLUE);
					}
				}
			}
		}
		if (isDebugMode_)
		{
			for (auto& connection : intersection->getConnections())
			{
				if (connection)
				{
					for (auto& collisionPoint : connection->getCollisionAreas())
					{
						if (collisionPoint)
						{
							Vector2 point{ connection->positionAtDistance(collisionPoint->collisionDistance()) };
							DrawCircleV(point, 0.5f, RED);
						}
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

	DrawLineEx(end, end + leftWing, lineWidth, color);
	DrawLineEx(end, end + rightWing, lineWidth, color);
}
