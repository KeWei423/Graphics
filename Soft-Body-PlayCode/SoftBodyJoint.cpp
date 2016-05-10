#include "SoftBodyJoint.h"

SoftBodyJoint::SoftBodyJoint(Particle *_start, Particle *_end, float const& _stiffness, float const& _drag, float const& _springDrag)
{
	start = _start ;
	end = _end ;
	length = Distance(start->getPosition(), end->getPosition()) ;
	stiffness = _stiffness ;
	drag = _drag ;
	springDrag = _springDrag ;
}
SoftBodyJoint::~SoftBodyJoint()
{
	
}

void SoftBodyJoint::setPoints(Particle *_start, Particle *_end)
{
	start = _start ;
	end = _end ;
}
float SoftBodyJoint::getDistance() const
{
	return Distance(start->getPosition(), end->getPosition()) ;
}
Vector2f SoftBodyJoint::getDirection() const
{
	return Normalize(end->getPosition() - start->getPosition()) ;
}
Vector2f SoftBodyJoint::getNormal() const
{
	return Vector2f(getDirection().y, -getDirection().x) ;
}
Vector2f SoftBodyJoint::getSpringForce() const
{
	if(end != start) return getDirection() * ( ( Distance(start->getPosition(), end->getPosition()) - length )*stiffness - dotProduct(start->getSpeed() - end->getSpeed(),getDirection()) * springDrag ) ;
	else return Vector2f(0,0) ;
}
Vector2f SoftBodyJoint::getPressureForce(float const& volume, float const& temperature) const
{
	return getNormal() * (temperature/volume) * getDistance() ;
}
void SoftBodyJoint::addForces(float const& volume, float const& temperature, float const& drag) 
{
	start->addForce(getSpringForce()) ;
	end->addForce(-getSpringForce()) ;
	start->addForce(getPressureForce(volume, temperature)) ;
	end->addForce(getPressureForce(volume, temperature)) ;
	start->addDrag(drag) ;
	end->addDrag(drag) ;
}