#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include<planet.h>

using namespace std;
class Game{
public:
    Game();
    void Draw();
    void run();
    void processEvents();
    void update();
    void render();

private:
    bool increase; //concrol the size
    int m_l;
    int m_r;

    sf::Clock c;    // time concrol
    sf::Time t;

    sf::RenderWindow window;

    vector<planet> solar_system;

    bool pause;          //when click the mouse pause the screen
    planet NewPlanet; // create the circle put it to the planet

    sf::VertexArray mouse_line;   //click the mouse give a line

    bool mouse_move;              //draw the line
    bool mouse_click;
};

#endif // GAME_H
