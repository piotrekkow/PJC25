#include "Connection.h"
#include "utils.h"

Connection::Connection(Lane* inlet, Lane* outlet)
	: inlet_{ inlet }
	, outlet_{ outlet }
{
	length_ = vector2Distance(inlet_->getParent()->getSourcePosition(), outlet_->getParent()->getTargetPosition());
}

const Lane* Connection::getInlet() const
{
	return inlet_;
}

const Lane* Connection::getOutlet() const
{
	return outlet_;
}
