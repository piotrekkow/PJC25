#include "Renderer.h"
#include "Connection.h"
#include "config.h"
#include "utils.h"
#include <ranges>
#include <string>
#include <iostream>

Renderer::Renderer(const Network* network, const AgentManager* agentManager) 
	: network_{ network }
	, agentManager_{ agentManager }
{
}

void Renderer::render(Camera2D& camera)
{
	BeginMode2D(camera);

	renderNetwork();
	renderAgents();

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

void Renderer::renderNetwork() const
{
	for (auto& link : network_->getLinks())
	{
		renderLink(link);
	}
	for (auto& intersection : network_->getIntersections())
	{
		renderIntersection(intersection);
	}
}

void Renderer::renderAgents() const
{
	for (auto vehicle : agentManager_->getVehicles())
	{
		renderVehicle(vehicle);
	}
}

void Renderer::renderLink(const Link* link) const
{
    if (!link)
	{
        std::cerr << "Tried to render a link which doesn't exist.\n";
        return;
    }

	if (!isDebugMode_)
	{
		for (auto& lane : link->getLanes())
		{
			DrawLineEx(lane->startPosition(), lane->endPosition(), link->getLaneWidth(), ROAD_COLOR);
		}
	}
	else renderLinkDebug(link);
}

void Renderer::renderLinkBoundary(const Link* link, float boundaryLaneWidth, Color boundaryColor) const
{
	Vector2 linkSourceOffset{ link->getSourcePosition() + link->normal() * link->getLaneWidth() * static_cast<float>(link->getLanes().size()) };
	Vector2 linkTargetOffset{ link->getTargetPosition() + link->normal() * link->getLaneWidth() * static_cast<float>(link->getLanes().size()) };
	drawArrow(link->getSourcePosition(), link->getTargetPosition(), 0.3f, boundaryColor);
	drawArrow(linkSourceOffset, linkTargetOffset, 0.3f, boundaryColor);
	DrawLineEx(linkSourceOffset, link->getSourcePosition(), boundaryLaneWidth, boundaryColor);
	DrawLineEx(linkTargetOffset, link->getTargetPosition(), boundaryLaneWidth, boundaryColor);
}

void Renderer::renderIntersection(const Intersection* intersection) const
{
	if (!intersection)
	{
		std::cerr << "Tried to render an intersection which doesn't exist\n";
		return;
	}

	if (intersection->getConnections().empty()) { return; }

	if (!isDebugMode_)
	{
		for (auto& connection : intersection->getConnections())
		{
			renderConnection(connection);
		}
	}
	else renderIntersectionDebug(intersection);
}

void Renderer::renderConnection(const Connection* connection) const
{
	if (!connection)
	{
		std::cerr << "Tried to render a connection which doesn't exist\n";
		return;
	}

	std::vector<Vector2> geometry{ connection->geometry() };

	for (size_t i = 1; i < geometry.size(); ++i)
	{
		DrawLineEx(geometry[i - 1], geometry[i], 3.5f, ROAD_COLOR);
	}
}

void Renderer::drawArrow(Vector2 start, Vector2 end, float lineWidth, Color color) const
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

void Renderer::renderVehicle(const Vehicle* vehicle) const
{
	if (!vehicle) return;
	
	Vector2 pos = vehicle->getPosition();
	Vector2 dir = vehicle->getDirection();
	float length = vehicle->getLength();
	float width = vehicle->getWidth();
	Color color = vehicle->getColor();
	
	Vector2 normal = { -dir.y, dir.x };
	
	Vector2 halfLengthVec = dir * (length / 2.0f);
	Vector2 halfWidthVec = normal * (width / 2.0f);
	
	Vector2 p1 = pos + halfLengthVec + halfWidthVec; // Front-right
	Vector2 p2 = pos - halfLengthVec + halfWidthVec; // Rear-right
	Vector2 p3 = pos - halfLengthVec - halfWidthVec; // Rear-left
	Vector2 p4 = pos + halfLengthVec - halfWidthVec; // Front-left
	
	DrawRectanglePro({ pos.x, pos.y, length, width }, { length / 2.0f, width / 2.0f }, atan2f(dir.y, dir.x) * RAD2DEG, color);
}

void Renderer::renderLinkDebug(const Link* link) const
{
	for (auto& lane : link->getLanes())
	{
		DrawLineEx(lane->startPosition(), lane->endPosition(), 1.0f, ROAD_COLOR);
	}
	renderLinkBoundary(link);
}

void Renderer::renderIntersectionDebug(const Intersection* intersection) const
{
	for (auto& connection : intersection->getConnections())
	{
		renderConnectionDebug(connection);
	}
	// another loop so that collisions show up on top of connection geometry
	for (auto& connection : intersection->getConnections())
	{
		renderCollisionsDebug(connection);
	}
}

void Renderer::renderConnectionDebug(const Connection* connection) const
{
	if (!connection)
	{
		std::cerr << "Tried to render a connection which doesn't exist\n";
		return;
	}

	std::vector<Vector2> geometry{ connection->geometry() };

	for (size_t i = 1; i < geometry.size(); ++i)
	{
		if (i < geometry.size() - 1)
		{
			DrawLineEx(geometry[i - 1], geometry[i], 0.3f, BLUE);
		}
		else
		{
			drawArrow(geometry[i - 1], geometry[i], 0.3f, BLUE);
		}
	}
}

void Renderer::renderCollisionsDebug(const Connection* connection) const
{
	if (!connection)
	{
		std::cerr << "Tried to render a connection which doesn't exist\n";
		return;
	}

	for (auto& collisionPoint : connection->getCollisionAreas())
	{
		if (collisionPoint)
		{
			Vector2 point{ connection->position(collisionPoint->getCollisionDistance()) };
			DrawCircleV(point, 0.5f, RED);
		}
	}
}
