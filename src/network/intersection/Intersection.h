#pragma once
#include "Link.h"

class Link;

class Intersection
{
	std::vector<Link*> incomingLinks;
	std::vector<Link*> outgoingLinks;
};

