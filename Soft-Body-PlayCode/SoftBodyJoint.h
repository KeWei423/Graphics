#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Particle.h"
#include "Utility.h"

using namespace std ;
using namespace sf ;

class SoftBodyJoint //class simulating a damped spring and a pressure force acting on 2 linked particles
{
public:
	SoftBodyJoint(Particle *_start, Particle *_end, float const& _stiffness, float const& _drag, float const& _springDrag);
	~SoftBodyJoint() ;

	void setPoints(Particle *_start, Particle *_end) ;
	float getDistance() const ;
	Vector2f getDirection() const ;
	Vector2f getNormal() const ;
	Vector2f getSpringForce() const ;
	Vector2f getPressureForce(float const& volume, float const& temperature) const ;
	void addForces(float const& volume, float const& temperature, float const& drag) ;

private:
	Particle *start, *end ;
	float length, stiffness, drag, springDrag ;
};

