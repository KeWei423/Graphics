#include <iostream>
#include "doodlebug.h"
#include "game.h"
using namespace std;

Game::Game()
{
//    cout<<"debug: Game()"<<endl;
    _window.create(sf::VideoMode(SIDE, SIDE), "Predator Prey Simulation");
    _window.setFramerateLimit(60);
    _colck.restart();
    _count = 0;
}


void Game::Draw(){
//    cout<<"debug: Draw()"<<endl;
    DrawGrid(_window);
    _gWorld.DrawWorld(_window);
}


void Game::Update()
{
    _escaped = _colck.getElapsedTime();
    int time = _escaped.asMilliseconds();
//    cout<<"time escaped: "<<time<<endl;
//    _gWorld.Move();
}


void Game::Render(){
       _window.clear();
       Draw();
       _window.display();
}



void Game::ProcessEvents()
{
   sf::Event event;
   while (_window.pollEvent(event))//or waitEvent
       {
       // check the type of the event...
           switch (event.type)
           {
               case sf::Event::Closed:
                   _window.close();
                   break;
               // key pressed

               case sf::Event::KeyPressed:
               if(event.key.code==sf::Keyboard::Return)
                {
                   cout<<endl<<endl<<"Generation: "<<_count<<endl;
                    _count++;
                    //set move to false
                    _gWorld.Reset();
                    _gWorld.Move();
                    _gWorld.Starve();
                    _gWorld.Breed();
                }
                break;
           }
       }
}


void Game::DrawGrid(sf::RenderWindow &window){
//    cout<<"debug: DrawGrid(RenderWindow window)"<<endl;
    for(int i= 0; i < BOX_NUMB; i++){
        for(int j=0; j<BOX_NUMB; j++){
            _background.setSize(sf::Vector2f(SIZE-1, SIZE-1));
            _background.setFillColor(sf::Color::Yellow);
            _background.setPosition(i*SIZE, j*SIZE);
            window.draw(_background);
        }
    }
}



void Game::Run()
{
   while (_window.isOpen())
   {
       ProcessEvents();
       Update();
       Render(); //clear/draw/display
   }
}
