#pragma once

#include <SFML/Graphics.hpp>
#include "Utility.h"

using namespace std ;
using namespace sf ;

class Wall
{
public:
	Wall() ;
	Wall(VertexArray const& _wall) ;
	Vector2f getWall(int const& i) const ;
	Vector2f getDirection(int const& i) const ;
	Vector2f getNormal(int const& i) const ;
	int getSize() const ;
private:
	VertexArray wall ;
	vector<Vector2f> normal ;
};

