#include "game.h"
#include "constants.h"
#include <iostream>
#include <cmath>
using namespace std;

Game::Game():mouse_line(sf::Lines,2){
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), " Gravity ");
    pause=1;
    window.setFramerateLimit(FRAME_RATE);
    increase=1;
    m_l=0;
    m_r=0;
    mouse_move=false;
    mouse_click=false;


}

void Game::Draw(){
    //Look at the data and based on the data, draw shapes on window object.

    if(mouse_click==true&&mouse_move==true){
        window.draw(mouse_line);                  //draw the line
    }

    for(int i=0;i<solar_system.size();i++)
    {
        sf::CircleShape temp;
        temp.setRadius(solar_system[i].get_radius());
        temp.setPosition(sf::Vector2f(solar_system[i].get_x(),solar_system[i].get_y()));
        //change the color in every sec
        solar_system[i].color_random();
        temp.setFillColor(sf::Color(solar_system[i].get_Red()+i*15,solar_system[i].get_Blue()-i*50,solar_system[i].get_Green()-i*30));
        window.draw(temp);
    }


    if(NewPlanet.get_radius()!=0)     //  draw the new circle when u create it
    {
        sf::CircleShape temp;
        temp.setRadius(NewPlanet.get_radius());
        temp.setPosition(sf::Vector2f(NewPlanet.get_x(),NewPlanet.get_y()));
        temp.setFillColor(sf::Color::Red);
        window.draw(temp);
    }
}


void Game::update()
{
    if(pause!=1)
    {
      for(int i=0; i< solar_system.size();i++){
          solar_system[i].move(solar_system);
      }
      big_bang(solar_system);
    }

    if(NewPlanet.x!=0)
    {
        if(NewPlanet.Radius<40&&increase)           // hold mouse concrol size
        {
            NewPlanet.Radius+=2;

        }
        else
        {
            NewPlanet.Radius-=2;
            increase=0;
        }
        if(NewPlanet.Radius<=0)
            increase=1;
        NewPlanet.x=m_l-NewPlanet.Radius;
        NewPlanet.y=m_r-NewPlanet.Radius;

    }
}
void Game::render(){
       window.clear();
       Draw();
       window.display();
}



void Game::processEvents()
{
   sf::Event event;
   while (window.pollEvent(event))//or waitEvent
       {
       // check the type of the event...
           switch (event.type)
           {
               // window closed
               // "close requested" event: we close the window
               case sf::Event::Closed:
                   window.close();
                   break;
           case sf::Event::KeyPressed:
               if(event.key.code==sf::Keyboard::Escape)
               {
                   window.close();
               }
               if(event.key.code==sf::Keyboard::R)     // fill the circles
               {

                   fill_particle(solar_system);
               }
               if(event.key.code==sf::Keyboard::T)     // make those circles to be small
               {
                   for(int i=0;i<solar_system.size();i++){
                      solar_system[i].Radius = solar_system[i].get_radius()*(0.8333);
                      solar_system[i].velocity_x = solar_system[i].get_velocity_x()*(0.8333);
                      solar_system[i].velocity_y = solar_system[i].get_velocity_y()*(0.8333);
                      solar_system[i].x=solar_system[i].get_x()*(0.8333);
                      solar_system[i].y=solar_system[i].get_y()*(0.8333);
                   }
               }
               if(event.key.code==sf::Keyboard::C)                         //clear
               {
//                 solar_system.clear();
               }
               break;
           case sf::Event::MouseButtonPressed:                    //click
           {
               pause=1;
                t=c.getElapsedTime();
                m_l=event.mouseButton.x;
                m_r=event.mouseButton.y;
                NewPlanet.x=event.mouseButton.x;
                NewPlanet.y=event.mouseButton.y;

                mouse_click=true;
                mouse_line[0].position =sf::Vector2f(event.mouseButton.x,event.mouseButton.y);

               break;
            }

           case sf::Event::MouseMoved:   //for draw the line
           {
               if(mouse_click==true){
                 mouse_line[1].position=sf::Vector2f(event.mouseMove.x,event.mouseMove.y);
                 mouse_move=true;
               }

               break;
           }
           case sf::Event::MouseButtonReleased:
               pause=0;

               if(mouse_click&&mouse_move){       // give the velocity for circle which one we create
                   NewPlanet.velocity_x=(mouse_line[1].position.x-mouse_line[0].position.x)/70;
                   NewPlanet.velocity_y=(mouse_line[1].position.y-mouse_line[0].position.y)/70;

                   cout<<"1,x :"<<mouse_line[1].position.x<<endl;
                   cout<<"0,x :"<<mouse_line[0].position.x<<endl;
                   cout<<"1,y :"<<mouse_line[1].position.y<<endl;
                   cout<<"0,y :"<<mouse_line[0].position.y<<endl;
                   cout<<"v x :"<<NewPlanet.velocity_x;
                   cout<<"v y :"<<NewPlanet.velocity_y;
               }

               solar_system.push_back(NewPlanet);
               NewPlanet=planet();

               mouse_click=false;
               mouse_move=false;
               break;
           default:
               break;
           }
       }
}
void Game::run()
{
   while (window.isOpen())
   {
       processEvents();
       update();
       render(); //clear/draw/display
   }
}
