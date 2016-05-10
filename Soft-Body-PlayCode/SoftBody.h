#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Particle.h"
#include "SoftBodyJoint.h"
#include "Triangulation.h"
#include "Wall.h"
#include "Utility.h"

using namespace std ;
using namespace sf ;

class SoftBody
{
public:
	SoftBody(float const& _stiffness, float const& _mass, float const& _drag, float const& _springDrag, float const& _temperature, Color const& _color);
	~SoftBody() ;

	void setPoints(vector<Vector2f> const& points) ;
	void addForce(int const& i, Vector2f const& force) ;
	void addGlobalForce(Vector2f const& force) ;
	void fixPoint(int const& i) ;
	float getVolume() const ;
	Vector2f getPosition(int const& i) const ;
	void  wallCollision() ;
	void update(float const& dt) ;

	void draw(RenderWindow &window) ;
	void drawNormals(RenderWindow &window) ;
	void drawArea(RenderWindow &window) ;

	void addWall(Wall *_wall) ;

private:
	vector<Particle> particle ;
	vector<SoftBodyJoint> spring ;
	vector<bool> fix ;

	VertexArray line ;

	int size ;
	float stiffness, mass, drag, springDrag, temperature, restitution, friction ;
	VertexArray triangle ;
	Color color ;
	vector<Wall*> wall ;
};

