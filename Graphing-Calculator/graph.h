#ifndef GAME_H
#define GAME_H
#include"shuntingyard.h"
#include "coordplane.h"
#include"const.h"

class Game
{
public:
    Game();
    void processEvents();

    void update();

    void Draw();
    void render();
    void run();
private:
    CoordPlane _scale;
    sf::RenderWindow _window;
    sf::VertexArray line;
    sf::VertexArray line2;
    sf::View V;
};

Game::Game():line(sf::LinesStrip,10000), line2(sf::LinesStrip,10000){
    _window.create(sf::VideoMode(WIND_W, WIND_H),"Graphng Calculator");

}

void Game::processEvents(){
    sf::Event event;
    while(_window.pollEvent(event)){
        switch(event.type){
             case sf::Event::Closed:
                        _window.close();
                        break;
             case sf::Event::KeyPressed:
                if(event.key.code==sf::Keyboard::Down){
                    V.zoom(1.1f);
                    V.setCenter(sf::Vector2f(X_OG, Y_OG));
                    _window.setView(V);
                }
                if(event.key.code==sf::Keyboard::Up){
                    V.zoom(0.9f);
                    V.setCenter(sf::Vector2f(X_OG, Y_OG));
                    _window.setView(V);
                }
                break;
             default:
                cout<<"Should not see this"<<endl;
                break;
        }
    }
}

void Game::update(){
     string myfxn = "( sin ( x ) ) / ( cos ( x ) ) ~";
     int pos = 0;
     for(int i = -5000; i<5000;i++){
         ShuntingYard func(myfxn,i);
         func.postFix();
         double Y = func.calculateIt();
//         cout<<"Y: "<<Y<<endl;
         line[pos].position = sf::Vector2f(X_OG + i, ( Y_OG - Y));
         line[pos].color = sf::Color::Magenta;
         pos++;
     }

     string myfxn2 = "( sin ( x ^ 2 ) ) + ( cos ( x ^ 2 ) ) ~";
     int pos2 = 0;
     for(int j = -5000; j<5000;j++){
         ShuntingYard func2(myfxn2,j);
         func2.postFix();
         double Y2 = func2.calculateIt();
//         cout<<"Y: "<<Y2<<endl;
         line2[pos2].position = sf::Vector2f(X_OG + j, (Y_OG - Y2) );
         line2[pos2].color = sf::Color::Green;
         pos2++;
     }

}

void Game::Draw(){
    _scale.DrawXCoord(_window);
    _scale.DrawYCoord(_window);
    _window.draw(line);
    _window.draw(line2);
}

void Game::run(){
    while(_window.isOpen()){
        processEvents();
        update();
        render();
    }

}
void Game::render(){
    _window.clear();
    Draw();
    _window.display();
}

#endif // GAME_H
