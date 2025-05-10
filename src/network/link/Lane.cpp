#include "Lane.h"
#include "utils.h"

Lane::Lane(int id, Link* parent)
	: id_ { id }
	, parent_ { parent }
{
}

const Link* Lane::getParent() const
{
	return parent_;
}

const Vector2 Lane::getOutletPosition() const
{
	return parent_->getTargetPosition() + parent_->getNormal() * static_cast<float>(id_) * parent_->getLaneWidth();
}

const Vector2 Lane::getInletPosition() const
{
	return parent_->getSourcePosition() + parent_->getNormal() * static_cast<float>(id_) * parent_->getLaneWidth();
}

