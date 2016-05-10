#include "SoftBody.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int main()
{
    int const width = 900 ;
    int const height = 900 ;

    ContextSettings antialiasing;
    antialiasing.antialiasingLevel = 32 ;
    RenderWindow window(VideoMode(width, height, 32), "SoftBody", Style::Default, antialiasing);
    window.setFramerateLimit(60) ;

    SoftBody s(30000, 10, 2, 200, 10000000, Color::Color(20,10,235)) ; //stiffness, mass, drag, springDrag, temperature, color
    vector<Vector2f> points ; float ptNb = 20 ;
    for(int i(0) ; i < ptNb ; i++)
    {
        points.push_back(Vector2f(width/2,height/2)+20.f*Vector2f(cos(i/ptNb*2*PI-PI/2.f),sin(i/ptNb*2*PI-PI/2.f))) ; //creates a circular softBody
    }
    s.setPoints(points) ;

    VertexArray bottom(Lines,2) ; bottom[0] = Vertex(Vector2f(5,height-5),Color::Red) ; bottom[1] = Vertex(Vector2f(width-5,height-5),Color::Red) ; //walls
    VertexArray left(Lines,2) ; left[0] = Vertex(Vector2f(5,5),Color::Red) ; left[1] = Vertex(Vector2f(5,height-5),Color::Red) ;
    VertexArray right(Lines,2) ; right[0] = Vertex(Vector2f(width-5,height-5),Color::Red) ; right[1] = Vertex(Vector2f(width-5,5),Color::Red) ;
    VertexArray top(Lines,2) ; top[0] = Vertex(Vector2f(width-5,5),Color::Red) ; top[1] = Vertex(Vector2f(5,5),Color::Red) ;
    VertexArray a(LinesStrip,2) ; a[0] = Vertex(Vector2f(0,height-300),Color::Red) ; a[1] = Vertex(Vector2f(width,height-5),Color::Red) ;
    vector<Wall> wall ; wall.push_back(bottom) ; wall.push_back(left) ; wall.push_back(right) ; wall.push_back(top) ; wall.push_back(a) ;
    for(int i(0) ; i < wall.size() ; i++) s.addWall(&wall[i]) ;

    Clock deltaTime ; float dt=0.001 ;
    Vector2f mousePos ; bool mouseFlag = false ; bool keyFlag = false ;
    bool simulate = false ;

    Event event ;

    while(window.isOpen())
    {
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed){
                window.close();
                exit(0);
            }
        }

        mousePos = Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y) ;

        if(Event::Closed){
            window.close();
            break;
        }

        if(mouseClickedOnce(Mouse::Left,mouseFlag) && !simulate)
        {
            points.push_back(mousePos) ;
            s.setPoints(points) ;
        }
        if(keyPressedOnce(Keyboard::Space,keyFlag)) simulate = true ;

        if(simulate)
        {
            if(Mouse::isButtonPressed(Mouse::Left)) s.addForce(0, (mousePos-s.getPosition(0))*10000.f) ;
            s.addGlobalForce(Vector2f(0,10000)) ;
            s.update(dt) ;
        }

        window.clear(Color::White) ;
        s.drawArea(window) ;
        s.draw(window) ;
        s.drawNormals(window) ;
        window.draw(a) ;
        window.display() ;

        dt = deltaTime.restart().asSeconds() ;
    }
    return 0;
}

