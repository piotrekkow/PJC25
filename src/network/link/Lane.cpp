#include "Lane.h"

Lane::Lane()
{
}

Lane::Lane(Link* parent, float speedLimit, float width)
	: parent_ { parent }
	, speedLimit_ { speedLimit }
	, width_ { width }
{
}

const Link* Lane::getParent() const
{
	return parent_;
}
