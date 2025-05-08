#pragma once
#include "Link.h"

class Link;

class Lane
{
	float length_;
	float speedLimit_{ 13.8f };	// meters/second
	float width_{ 3.5f };	// meters
	Link* parent_;

public:
	Lane();
	Lane(Link* parent, float speedLimit, float width);
	const Link* getParent() const;
};

