#include "Lane.h"

Lane::Lane()
{
}

Lane::Lane(float width, float speedLimit)
	: m_width{ width }
	, m_speedLimit{ speedLimit }
{
}

const float Lane::getWidth() const
{
	return m_width;
}
