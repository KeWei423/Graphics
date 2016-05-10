#include "ant.h"

Ant::Ant():Organism(){}


Ant::Ant(int r, int c, int type, int age):Organism(r, c, type, age){
    _ant.setSize(sf::Vector2f(SIZE, SIZE));
    _ant.setFillColor(sf::Color(100, 100, 50));
    _ant.setPosition(r*SIZE, c*SIZE);
}


void Ant::Move(Organism* world[][BOX_NUMB], int i, int j, int age){
    cout<<"debug: Ant::Move(Organism* world[][BOX_NUMB], int i, int j, int age)"<<endl;
    int direction = rand()%4;
    switch(direction){
        case 0:
            if(world[i+1][j] == NULL){
                cout<<"right"<<endl;
                world[i+1][j] = new Ant(i+1, j, ANT, age+1);
                world[i+1][j]->setHasMove(true);
                world[i][j] = NULL;
            }
            break;
        case 1:
            if(world[i-1][j] == NULL){
                cout<<"left"<<endl;
                world[i-1][j] = new Ant(i-1, j, ANT, age+1);
                world[i-1][j]->setHasMove(true);
                world[i][j] = NULL;
            }
            break;
        case 2:
            if(world[i][j+1] == NULL){
                cout<<"up"<<endl;
                world[i][j+1] = new Ant(i, j+1, ANT, age+1);
                world[i][j+1]->setHasMove(true);
                world[i][j] = NULL;
            }
            break;
        case 3:
            if(world[i][j-1] == NULL){
                cout<<"down"<<endl;
                world[i][j-1] = new Ant(i, j-1, ANT, age+1);
                world[i][j-1]->setHasMove(true);
                world[i][j] = NULL;
            }
            break;
        default:
            break;
    }
}



void Ant::Breed(Organism* world[][BOX_NUMB], int i, int j){
    cout<<"debu: Ant::Breed(Organism* world[][BOX_NUMB], int i, int j)"<<endl;
    int age = Organism::age();
    if(age % ANT_BREED == 0){
        for(int r = i-1; r<i+2; r++){
            for(int c = j-1; c < j+2; c++){
                if(world[r][c] == NULL){
                    world[r][c] = new Ant(r, c, ANT, 0);
                    return;
                }
            }
        }
    }
}



bool Ant::Starve(){
    cout<<"debug: Ant::Starve()"<<endl;
    return false;
}



void Ant::DrawOrg(sf::RenderWindow& window){
    window.draw(_ant);
}


void Ant::Print(ostream& outs) const{
    outs<<ANT<<endl;
}


int Ant::getType(){
    cout<<"Ant::getType()"<<endl;
    return Organism::getType();
}

