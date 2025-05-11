#include "Connection.h"
#include "utils.h"
#include <iostream>

Connection::Connection(Lane* inletLane, Lane* outletLane)
	: previousLane_{ inletLane }
	, nextLane_{ outletLane }
{
	if (!previousLane_)
	{
		std::cerr << "Connection pointing to a null previous lane\n";
	}
	if (!nextLane_)
	{
		std::cerr << "Connection pointing to a null next lane\n";
	}
}

const Lane* Connection::previousLane() const
{
	return previousLane_;
}

const Lane* Connection::nextLane() const
{
	return nextLane_;
}

const Vector2 Connection::startPosition() const
{
	return previousLane()->endPosition();
}

const Vector2 Connection::endPosition() const
{
	return nextLane()->startPosition();
}
