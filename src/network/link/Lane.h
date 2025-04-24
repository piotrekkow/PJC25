#pragma once
#include <queue>

class Lane
{
	float m_width{ 35.0f };		// meters
	float m_speedLimit{ 13.8f };	// meters/second

public:
	Lane();
	Lane(float width, float speedLimit);

	const float getWidth() const;
};

