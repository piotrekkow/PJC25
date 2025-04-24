#include "Renderer.h"
#include "config.h"
#include "utils.h"
#include <ranges>
#include <string>
#include <iostream>

Renderer::Renderer(const Network* network) : m_network{ network }
{
}

void Renderer::render()
{
	for (auto link : m_network->getLinks())
	{
		renderLink(link);
	}
}

bool Renderer::toggleDebug()
{
	m_isDebugMode = !m_isDebugMode;
	return m_isDebugMode;
}

void Renderer::renderLink(Link* link)
{
    if (!link) {
        std::cerr << "Tried to render a link which doesn't exist.\n";
        return;
    }
    
    const std::vector<Vector2>& linkGeometry{ link->getGeometry() };

	for (auto segment : link->getSegments())
	{
        const std::vector<Lane*> lanes = segment->getLanes();
        const int centerlineOffset = segment->getCenterlineOffset();

        for (size_t i = segment->getGeometrySource() + 1; i <= segment->getGeometryTarget(); ++i)
        {
            const Vector2& geoPointStart = linkGeometry[i - 1];
            const Vector2& geoPointEnd = linkGeometry[i];

            Vector2 tangent = normalizedTangent(geoPointStart, geoPointEnd);
            Vector2 normal = tangent2Normal(tangent);

            float currentLeftOffsetDistance = 0.0f;
            for (int j = centerlineOffset - 1; j >= 0; --j) {

                const Lane* currentLane = lanes[j];
                float laneWidth = currentLane->getWidth();

                float laneCenterOffset = currentLeftOffsetDistance + laneWidth / 2.0f;

                Vector2 offsetVector = normal * laneCenterOffset;
                Vector2 laneStart = geoPointStart + offsetVector;
                Vector2 laneEnd = geoPointEnd + offsetVector;

                DrawLineEx(laneStart, laneEnd, laneWidth, ROAD_COLOR);
                currentLeftOffsetDistance += laneWidth;
            }

            // Draw lanes to the RIGHT of the centerline (indices >= laneCenterOffset)
            float currentRightOffsetDistance = 0.0f;
            for (size_t j = centerlineOffset; j < lanes.size(); ++j) {

                const Lane* currentLane = lanes[j];
                float laneWidth = currentLane->getWidth();

                float laneCenterOffset = currentRightOffsetDistance + laneWidth / 2.0f;

                Vector2 offsetVector = -normal * laneCenterOffset; // Negative normal for right side (right hand rule)
                Vector2 laneStart = geoPointStart + offsetVector;
                Vector2 laneEnd = geoPointEnd + offsetVector;

                DrawLineEx(laneStart, laneEnd, laneWidth, ROAD_COLOR);
                currentRightOffsetDistance += laneWidth;
            }

            if (m_isDebugMode)
            {
                DrawLineV(geoPointStart, geoPointEnd, GREEN);
            }
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
