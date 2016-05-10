#include "wall.h"

Wall::Wall(): Organism(){

}


Wall::Wall(int r, int c, int type, int age): Organism(r, c, type, age){
    _wall.setSize(sf::Vector2f(SIZE, SIZE));
    _wall.setPosition(r*SIZE, c*SIZE);
    _wall.setFillColor(sf::Color(50, 50, 50));
}


void Wall::Move(Organism *world[][BOX_NUMB], int i, int j, int age){
    return;
}


void Wall::Breed(Organism* world[][BOX_NUMB], int i, int j){
    return;
}


bool Wall::Starve(){
    return false;
}


void Wall::DrawOrg(sf::RenderWindow& window){
//    cout<<"draw wall"<<endl;
    window.draw(_wall);
}


void Wall::Print(ostream& outs) const{
    outs<<WALL<<endl;
}



int Wall::getType(){
    return Organism::getType();
}
