#include "SoftBody.h"


SoftBody::SoftBody(float const& _stiffness, float const& _mass, float const& _drag, float const& _springDrag, float const& _temperature, Color const& _color)
{
	line.setPrimitiveType(LinesStrip) ;
	size = 0 ;

	stiffness = _stiffness ;
	mass = _mass ;
	drag = _drag ;
	springDrag = _springDrag ;
	temperature = _temperature ;
	restitution = 0.5 ;
	friction = 0.7 ;

	color = _color ;
}
SoftBody::~SoftBody()
{
	for(int i(0) ; i < wall.size() ; i++)
	{
		delete wall[i] ;
		wall[i] = 0 ;
	}
}

void SoftBody::setPoints(vector<Vector2f> const& points)
{
	particle.clear() ;
	line.clear() ;
	fix.clear() ;
	spring.clear() ;

	for(int i(0) ; i < points.size() ; i++)
	{
		particle.push_back(Particle(mass, points[i])) ;
		line.append(Vertex(points[i],Color::Black)) ;
		fix.push_back(false) ;
	}
	line.append(Vertex(points[0],Color::Black)) ;

	size = points.size() ;

	for(int i(0) ; i < size-1 ; i++)
	{
		spring.push_back(SoftBodyJoint(&particle[i], &particle[i+1], stiffness, drag, springDrag ) );
	}	spring.push_back(SoftBodyJoint(&particle[size-1], &particle[0], stiffness, drag, springDrag ) );
	
}
void SoftBody::addForce(int const& i, Vector2f const& force)
{
	if(i < size) particle[i].addForce(force) ;
}
void SoftBody::addGlobalForce(Vector2f const& force)
{
	for(int i(0) ; i < size ; i++) particle[i].addForce(force) ;
}
void SoftBody::fixPoint(int const& i)
{
	if(i < fix.size()-1) fix[i] = true ;
}
float SoftBody::getVolume() const //compute the exact area of the soft body by adding algebraic areas of trapezoids (finite integral = sum) 
{
	float result = 0 ;
	for(int i(0) ; i < size-1 ; i++)
	{
		result += (particle[i].getPosition().x + particle[i+1].getPosition().x)*(particle[i].getPosition().y - particle[i+1].getPosition().y) ;
	}	result += (particle[size-1].getPosition().x + particle[0].getPosition().x)*(particle[size-1].getPosition().y - particle[0].getPosition().y) ;
	return -result/2.f ;
}
Vector2f SoftBody::getPosition(int const& i) const
{
	return particle[i].getPosition() ;
}
void SoftBody::wallCollision()
{
	for(int i(0) ; i < size ; i++)
	{
		for(int j(0) ; j < wall.size() ; j++)
		{
			for(int k(0) ; k < wall[j]->getSize()-1 ; k++)
			{
				if(checkSegmentIntersection(particle[i].getPosition(), particle[i].getPreviousPosition(),
					wall[j]->getWall(k), wall[j]->getWall(k+1)) )
				{
					particle[i].setPosition(particle[i].getPreviousPosition()+wall[j]->getDirection(k) * 
						dotProduct(particle[i].getPosition() - particle[i].getPreviousPosition(),wall[j]->getDirection(k))) ;
					particle[i].setSpeed(particle[i].getSpeed()*friction - restitution * 2.f * wall[j]->getNormal(k) * 
																dotProduct(wall[j]->getNormal(k),particle[i].getSpeed()) ) ;
				}
			}
		}
	}
}
void SoftBody::update(float const& dt)
{
	for(int i(0) ; i < size ; i++)
	{
		spring[i].addForces(getVolume(), temperature, drag) ;
	}		

	for(int i(0) ; i < size ; i++)
	{
		if(fix[i] == false)
		{
			particle[i].updatePosition(dt) ;
			particle[i].clearForce() ;

			line[i].position = particle[i].getPosition() ;
		}
	}
	wallCollision() ;
	line[size].position = line[0].position ;
}

void SoftBody::draw(RenderWindow &window)
{
	window.draw(line) ;
}
void SoftBody::drawNormals(RenderWindow &window)
{
	for(int i(1) ; i < size ; i++)
	{
		drawLine(particle[i].getPosition(), 0.0005f*(spring[i].getPressureForce(getVolume(), temperature)+spring[i-1].getPressureForce(getVolume(), temperature)), window, Color::Black) ;
		drawLine(particle[i].getPosition(), 0.0005f*(spring[i].getSpringForce()-spring[i-1].getSpringForce()), window, Color::Red) ;
		//drawLine(particle[i].getPosition(), -0.05f*particle[i].getSpeed(), window, Color::Green) ;
	}
	if(size>=1) 
	{
		drawLine(particle[0].getPosition(), 0.0005f*(spring[0].getPressureForce(getVolume(), temperature)+spring[size-1].getPressureForce(getVolume(), temperature)), window, Color::Blue) ;
		drawLine(particle[0].getPosition(), 0.0005f*(spring[0].getSpringForce()-spring[size-1].getSpringForce()), window, Color::Red) ;
		drawLine(particle[0].getPosition(), -0.05f*particle[0].getSpeed(), window, Color::Green) ;
	}
}
void SoftBody::drawArea(RenderWindow &window)
{
	triangle = triangulate(line, color) ;
	window.draw(triangle) ;
}

void SoftBody::addWall(Wall *_wall)
{
	wall.push_back(_wall) ;
}