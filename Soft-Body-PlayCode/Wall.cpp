#include "Wall.h"

Wall::Wall()
{

}
Wall::Wall(VertexArray const& _wall)
{
	wall = _wall ;
	Vector2f u ;
	for(int i(0) ; i < wall.getVertexCount()-1 ; i++)
	{
		u = Normalize(wall[i+1].position - wall[i].position) ;
		normal.push_back(Vector2f(u.y, -u.x)) ;
	}
}
Vector2f Wall::getWall(int const& i) const
{
	return wall[i].position ;
}
Vector2f Wall::getDirection(int const& i) const
{
	return Vector2f(normal[i].y,-normal[i].x) ;
}
Vector2f Wall::getNormal(int const& i) const
{
	return normal[i] ;
}
int Wall::getSize() const
{
	return wall.getVertexCount() ;
}