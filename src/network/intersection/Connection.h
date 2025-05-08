#pragma once
#include "Lane.h"

class Lane;

class Connection
{
	float length_;
	Lane* inlet_;
	Lane* outlet_;

public:
	Connection(Lane* inlet, Lane* outlet);
	const Lane* getInlet() const;
	const Lane* getOutlet() const;
};

