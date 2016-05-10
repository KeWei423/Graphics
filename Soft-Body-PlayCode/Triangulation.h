/* Triangulation by ear clipping method codded by Muzkaw : https://www.youtube.com/user/Muzkaw
   Feel free to use it for whatever application
   It is not the most effective way to triangulate large polygons : this algorithm has a O(n^2) or O(n^2*log(n)) complexity
   You must draw the polygon CCW. You can easily modify the program so that it handles both cases
   if you don't want flat triangles, go for the Delaunay triangulation
   You need to link SFML 2.0 or above to run the program
   Happy coding ! */

#include <SFML/Graphics.hpp>
#include <iostream> 
#include <cmath>
#include "Utility.h"

using namespace std ;
using namespace sf ;

VertexArray triangulate(VertexArray points, Color color) ;