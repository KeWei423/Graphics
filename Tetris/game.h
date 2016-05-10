#ifndef GAME_H
#define GAME_H
#include "grid.h"
#include <SFML/Audio.hpp>
using namespace std;


class game
{
public:
    //Constructor
    game();

    //-------------------------------------
    // Background: music, interface, image
    //-------------------------------------
    void Music();
    void Logo();
    void TextInit();
    void Drop();
    void UserInter();

    //----------------------------
    // check start and end
    //----------------------------
    bool Start=true;
    bool gameOver=false;

    //---------------------------
    //Initialize the game at main
    //---------------------------
    void Run();

    //---------------------------
    // Game running procedure
    //---------------------------
    void ProcessEvents(); // Process keyboard commans
    void CheckStart();
    void Update();
    void CheckEnd();
    void Move();
    void UpdateScore();
    void CheckCollision();
    void Draw();
    void CheckTick();
    void CheckTop();
    void Render();
    void SelfPlayer();


    //--------------------------
    // SFML variables
    //--------------------------

    /*sound track*/
    sf::Music theme;

    /*logo*/
    sf::Texture logoText;
    sf::Sprite logo;

    /*User Interfaec*/
    sf::Texture UIText;
    sf::Sprite UI;

    /*text variables*/
    sf::Font gameFont;
    sf::Text startText;
    sf::Text score;
    sf::Text END;
    sf::Text info;

    /*accelatere*/
    sf::Time t;
    sf::Clock c;


private:
    Shape fig;
    Shape newFig;
    Grid map;
    int tick;
    sf::RenderWindow window;
};

string int2str(int source);

#endif // GAME_H
