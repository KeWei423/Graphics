#include "Utility.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>

using namespace sf ;
using namespace std ;

Vector2f Diff(Vector2f const& v1, Vector2f const& v2, float const& deltaTime) 
{
	Vector2f diff = (v1-v2)/deltaTime ;
	return diff ;
}

float Diff(float const& a1, float const& a2, float const& deltaTime) 
{
	float diff = (a1-a2)/deltaTime ;
	return diff ;
}

float Distance(Vector2f const& v1, Vector2f const& v2)
{
	float distance = sqrt(pow((v2.x-v1.x),2) + pow((v2.y-v1.y),2)) ;
	return distance ;
}

float Norm (Vector2f const& v) 
{
	float result = sqrt(pow(v.x,2)+pow(v.y,2)) ;
	return result ;
}


Vector2f Normalize(Vector2f const& v)
{
	return v/Norm(v) ;
}


float determinant(Vector2f const& u, Vector2f const& v) 
{
	float result = u.x*v.y - u.y*v.x ;
	return result ;
}


float dotProduct(Vector2f const& u, Vector2f const& v)
{
	return u.x*v.x + u.y*v.y ;
}


Vector2f rotatePoint(Vector2f const& point, Vector2f const& center, float const& angle) 
{
	float x = center.x + (point.x - center.x)*cos(angle*(PI/180)) - (point.y - center.y)*sin(angle*(PI/180)) ;
	float y = center.y + (point.x - center.x)*sin(angle*(PI/180)) + (point.y - center.y)*cos(angle*(PI/180)) ;
	return Vector2f(x,y) ;
}



bool checkSegmentIntersection(Vector2f const& A, Vector2f const& B, Vector2f const& C, Vector2f const& D)
{
	if(determinant(B-A,C-A)*determinant(B-A,D-A)<0 && determinant(D-C,A-C)*determinant(D-C,B-C)<0)
		return true ;
	return false ;
}

Vector2f getSegmentIntersection(Vector2f const& A, Vector2f const& B, Vector2f const& C, Vector2f const& D) 
{
	
	if(determinant(B-A,C-A)*determinant(B-A,D-A)<0 && determinant(D-C,A-C)*determinant(D-C,B-C)<0)
	{
		if(B.x-A.x != 0 && D.x-C.x !=0)
		{
			float a1 = (B.y-A.y)/(B.x-A.x) ;
			float a2 = (D.y-C.y)/(D.x-C.x) ;
			float b1 = A.y-a1*A.x ;
			float b2 = C.y-a2*C.x ;
			float Ix = (b2-b1)/(a1-a2) ;
			float Iy = a1*Ix+b1 ;
			return Vector2f(Ix,Iy) ;
		}

		if(B.x-A.x == 0)
		{
			float a2 = (D.y-C.y)/(D.x-C.x) ;
			float b1 = A.x ;
			float b2 = C.y-a2*C.x ;
			float Ix = b1 ;
			float Iy = a2*b1+b2 ;
			return Vector2f(Ix,Iy) ;
		}

		if(D.x-C.x == 0)
		{
			float a1 = (B.y-A.y)/(B.x-A.x) ;
			float b1 = A.y-a1*A.x ;
			float b2 = C.x ;
			float Ix = b2 ;
			float Iy = a1*b2+b1 ;
			return Vector2f(Ix,Iy) ;
		}		
	}
	return Vector2f();
}

void drawLine(Vector2f pos, Vector2f dir, float norm, RenderWindow &window, Color color)
{
	dir  /= Norm(dir) ;
	VertexArray line(Lines, 2) ;
	line[0] = Vertex(pos,color) ;
	line[1] = Vertex(pos+dir*norm,color) ;
	window.draw(line) ;
}
void drawLine(Vector2f pos, Vector2f dir, RenderWindow &window, Color color)
{
	VertexArray line(Lines, 2) ;
	line[0] = Vertex(pos,color) ;
	line[1] = Vertex(pos+dir, color) ;
	window.draw(line) ;
}
void drawPoint(Vector2f p, RenderWindow &window) 
{
	CircleShape c(3) ;
	c.setOrigin(1.5,1.5) ;
	c.setPosition(p) ;
	c.setFillColor(Color::Red) ;
	window.draw(c) ;
}

float gaussianFunction(float maxVal, float wideness, float x) 
{
	return maxVal*exp(-pow(x,2)/(2*pow(wideness,2))) ;
}

float clamp(float value, float min, float max) 
{
	float result ;
	if(value > max)
		result = max ;
	else if(value < min)
		result = min ;
	else
		result = value ;
	return result ;
}

bool mouseClickedOnce(Mouse::Button const& button, bool &mouseFlag) 
{
	bool result = false ;
	if(Mouse::isButtonPressed(button) && mouseFlag == false)
	{
		result = true ;
		mouseFlag = true ;
	}
	else if (Mouse::isButtonPressed(button) && mouseFlag == true) 
	{
		result = false ;
		mouseFlag = true ;
	}
	else
	{
		result = false ;
		mouseFlag = false ;
	}
	return result ;
}
bool keyPressedOnce(Keyboard::Key const& key, bool &keyFlag)
{
	bool result = false ;
	if(Keyboard::isKeyPressed(key) && keyFlag == false)
	{
		result = true ;
		keyFlag = true ;
	}
	else if (Keyboard::isKeyPressed(key) && keyFlag == true) 
	{
		result = false ;
		keyFlag = true ;
	}
	else
	{
		result = false ;
		keyFlag = false ;
	}
	return result ;
}

bool collisionTrianglePoint(Vector2f a, Vector2f b, Vector2f c, Vector2f point)
{
	Vector2f ab = b-a ;
	Vector2f bc = c-b ;
	Vector2f ca = a-c ;
	
	if(determinant(ab,point-a) > 0 && determinant(bc,point-b) > 0 && determinant(ca,point-c) > 0)
	{
		return true ;
	}
	else return false ;
}
