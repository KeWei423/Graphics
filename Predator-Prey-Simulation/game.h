/**********************************************************************
 * File name: game.h
 * game class declaration
 ***********************************************************************/
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include  "world.h"
//#include "organism.h"

class Game
{
public:
    Game();
    //-------------------------------------
    // Background: music, interface, image
    //-------------------------------------


    //---------------------------
    //Initialize the game at main
    //---------------------------
    void Run();


    //---------------------------
    // Game running procedure
    //---------------------------
    void ProcessEvents(); // Process keyboard commans
    void DrawGrid(sf::RenderWindow& window);
    void Update();

    void Draw();
    void Render();

private:
    int _count;
    World _gWorld;

    //--------------------------
    // SFML variables
    //--------------------------
    sf::Clock _colck;
    sf::Time _escaped;
    sf::RectangleShape _background;
    sf::RenderWindow _window;
};

#endif // GAME_H
