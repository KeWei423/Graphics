#include "ThickLine.h"

ThickLine::ThickLine()
{
	VA.setPrimitiveType(TrianglesStrip) ;
	lineVA.setPrimitiveType(LinesStrip) ;
	thickness = 10 ;
	color = Color::Blue ;
}

ThickLine::ThickLine(float const& _thickness, Color const& _color)
{
	VA.setPrimitiveType(TrianglesStrip) ;
	lineVA.setPrimitiveType(LinesStrip) ;
	thickness = _thickness ;
	color = _color ;
}

void ThickLine::addPoint(Vector2f const& p)
{
	line.push_back(p) ;
	if(line.size()>1)
	{
		Vector2f n = line[line.size()-1]-line[line.size()-2] ; n /= Norm(n) ;
		Vector2f u(n.y,-n.x) ;
		VA.append( Vertex(u*thickness+line[line.size()-1],color) ) ;
		VA.append( Vertex(-u*thickness+line[line.size()-1],color) ) ;
		VA.append( Vertex(u*thickness+line[line.size()-2],color) ) ;
		VA.append( Vertex(-u*thickness+line[line.size()-2],color) ) ;
	}
}


void ThickLine::setThickness(float const& _thickness)
{
	thickness= _thickness ;
}

void ThickLine::setPosition(int const& i, Vector2f const& position)
{
	if(i==0)
	{
		line[0] = position ;
		line[line.size()-1] = position ;
	}
	else line[i] = position ;
	
}

void ThickLine::closeLoop()
{
	line.push_back(line[0]) ;
}

void ThickLine::updateVA()
{
	VA.clear() ;
	Vector2f n, u ;
	
	for(int i(1) ; i < line.size() ; i++)
	{
		n = line[i]-line[i-1] ; n /= Norm(n) ;
		u = Vector2f(n.y,-n.x) ;
		VA.append( Vertex(u*thickness+line[i],color) ) ;
		VA.append( Vertex(-u*thickness+line[i],color) ) ;
		VA.append( Vertex(u*thickness+line[i-1],color) ) ;
		VA.append( Vertex(-u*thickness+line[i-1],color) ) ;
	}
}

void ThickLine::clear()
{
	VA.clear() ;
	lineVA.clear() ;
	line.clear() ;
}

vector<Vector2f> ThickLine::getLine() const
{
	return line ;
}

int ThickLine::getSize() const
{
	return line.size() ;
}

void ThickLine::draw(RenderWindow &window)
{
	//window.draw(VA) ;
	drawLine(window) ;
}

void ThickLine::drawLine(RenderWindow &window)
{
	lineVA.clear();
	for(int i(0) ; i < line.size() ; i++)
	{
		lineVA.append(Vertex(line[i],Color::Red)) ;
	}
	window.draw(lineVA) ;
}
