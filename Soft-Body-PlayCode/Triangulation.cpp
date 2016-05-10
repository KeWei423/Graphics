/* Triangulation by ear clipping method codded by Muzkaw : https://www.youtube.com/user/Muzkaw
   Feel free to use it for whatever application
   It is not the most effective way to triangulate large polygons : this algorithm has a O(n^2) or O(n^2*log(n)) complexity
   You must draw the polygon CCW. You can easily modify the program so that it handles both cases
   if you don't want flat triangles, go for the Delaunay triangulation
   You need to link SFML 2.0 or above to run the program
   Happy coding ! */

#include "Triangulation.h"

VertexArray triangulate(VertexArray points, Color color) // the ear clipping algorithm
{
	VertexArray triangles(Triangles) ; /* a dynamic array that will store the points of the triangles : if the triangle n is (An Bn Cn), then the points will be stored as [A1,B1,C1,
																																									  A2,B2,C2,
																																									  A3,B3,C3...] */
	VertexArray initialPoints = points ;
	if(points.getVertexCount() < 3) // let's make sure that the user don't feed the function with less than 3 points !
		return triangles ;
	else
	{
		bool impossibleToTriangulate = false ;
		bool triangleFound = true ;

		while(points.getVertexCount() != 0) // run the algorithm until our polygon is empty
		{
			if(!triangleFound) // if we've looped once without finding any ear, the program is stuck, the polygon is not triangulable for our algorithm (likely to be a 8 shape or such self intersecting polygon)
				return triangles ;

			triangleFound = false ; // we want to find a new ear at each loop

			for(int i(0) ; i < points.getVertexCount()-2 ; i++) // for each 3 consecutive points we check if it's an ear : an ear is a triangle that wind in the right direction and that do not contain any other point of the polygon
			{
				if(!triangleFound) // if we still didn't find an ear
				{
					bool result = false ;
					if(determinant(points[i+1].position-points[i].position,points[i+2].position-points[i+1].position) > 0) // if the triangle winds in the right direction
					{
						result = true ;
						for(int j(0) ; j < initialPoints.getVertexCount() ; j++) // we check if there's no point inside it
						{
							if(collisionTrianglePoint(points[i+2].position,points[i+1].position,points[i].position,initialPoints[j].position))
							{
								result = false ; // if I got a point in my triangle, then it's not an ear !
							}
						}
					}

					if(result) // now, we have found an ear :
					{
						triangleFound = true ;
				
						triangles.append(Vertex(points[i].position,color)) ; // so we add our 3 vec2f to the triangle array : it's one of our triangles !
						triangles.append(Vertex(points[i+1].position,color)) ;
						triangles.append(Vertex(points[i+2].position,color)) ;

						VertexArray bufferArray;
						for(int j(0) ; j < points.getVertexCount() ; j++) // then we delete the triangle in the points array : we already know that it's an ear, we don't need it anymore
						{
							if(j!=i+1) // we copy all the points in a buffer array except the point we don't want
							{
								bufferArray.append( points[j] );
							}
						}
						points = bufferArray ;
					}
				}
			}
		}
	}			
	return triangles ; // we return the triangle array
}
