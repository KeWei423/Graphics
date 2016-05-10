#include "doodlebug.h"

Doodlebug::Doodlebug(): Organism(){
    _moveUntilDie = 0 ;
}


Doodlebug::Doodlebug(int r, int c, int type, int age): Organism(r, c, type, age){
    _bug.setSize(sf::Vector2f(SIZE, SIZE));
    _bug.setFillColor(sf::Color(20, 100, 200));
    _bug.setPosition(r*SIZE,c*SIZE);
    _moveUntilDie = 0 ;
}


Doodlebug::Doodlebug(int r, int c, int type, int age, int move): Organism(r, c, type, age){
    _bug.setSize(sf::Vector2f(SIZE, SIZE));
    _bug.setFillColor(sf::Color(20, 100, 200));
    _bug.setPosition(r*SIZE,c*SIZE);
    _moveUntilDie = move ;
}


int Doodlebug::age(){
    cout<<"debug: Doodlebug::age()"<<endl;
    return Organism::age();
}

void Doodlebug::Move(Organism* world[][BOX_NUMB], int i, int j, int age){
    cout<<"debug: Doodlebug:: Move(Organism* world[][BOX_NUMB], int i, int j, int age)"<<endl;
    bool eat = Eat(world, i, j);
    if(!eat){
        _moveUntilDie++;
        int direction = rand()%4;
        cout<<" direction: "<<direction<<endl;
        randMove(world, i, j, age, direction);
    }
}




void Doodlebug::Breed (Organism* world[][BOX_NUMB], int i, int j){
    cout<<"debug: Doodlebug::Breed(Organism* world[][BOX_NUMB], int i, int j)"<<endl;
    Organism::Breed(world, i, j);
    int age = Organism::age();
    cout<<"age: "<<age<<endl;

    if(age % BUG_BREED == 0){
        for(int r = i-1; r<i+2; r++){
            for(int c = j-1; c < j+2; c++){
                if(world[r][c] == NULL){
                    world[r][c] = new Doodlebug(r, c, BUG, 0);
                    return;
                }
            }
        }
    }
}



bool Doodlebug::Starve(){
    cout<<"debug: Doodlebug::Starve()"<<endl;
    if(_moveUntilDie > STARVE){
        return true;
    }
    return false;
}



void Doodlebug::DrawOrg(sf::RenderWindow& window){
    window.draw(_bug);
}


void Doodlebug::Print(ostream& outs) const{
    outs<<BUG<<endl;
}


int Doodlebug::getType(){
    return Organism::getType();
}



bool Doodlebug::Eat(Organism *world[][BOX_NUMB], int i, int j){
    cout<<"debug: Doodlebug::Eat(Organism *world[][BOX_NUMB], int i, int j)"<<endl;
    if(world[i+1][j] != NULL && (world[i+1][j]->getType() == ANT)){
        int age = world[i][j]->age();
        world[i+1][j] = new Doodlebug(i+1, j, BUG, age+1);
        delete (world[i][j]);
        world[i][j] = NULL;
        _moveUntilDie = 0;
        return true;
    }
    else if(world[i-1][j] != NULL && (world[i-1][j]->getType() == ANT)){
        int age = world[i][j]->age();
        world[i-1][j] = new Doodlebug(i+1, j, BUG, age+1);
        delete (world[i][j]);
        world[i][j] = NULL;
        _moveUntilDie = 0;
        return true;
    }
    else if(world[i][j+1] != NULL && (world[i][j+1]->getType() == ANT)){
        int age = world[i][j]->age();
        world[i][j+1] = new Doodlebug(i, j+1, BUG, age+1);
        delete (world[i][j]);
        world[i][j] = NULL;
        _moveUntilDie = 0;
        return true;
    }
    else if(world[i][j-1] != NULL && (world[i][j-1]->getType() == ANT)){
        int age = world[i][j]->age();
        world[i][j-1] = new Doodlebug(i, j+1, BUG, age+1);
        delete (world[i][j]);
        world[i][j] = NULL;
        _moveUntilDie = 0;
        return true;
    }
    return false;

}


void Doodlebug::randMove(Organism *world[][BOX_NUMB], int i, int j, int age, int direction){
    cout<<"debug: Doodlebug::randMove(Organism *world[][BOX_NUMB], int i, int j, int age, int direction)"<<endl;
    switch(direction){
        case 0:
            if(world[i+1][j] == NULL){
                cout<<"right"<<endl;
                world[i+1][j] = new Doodlebug(i+1, j, BUG, age, _moveUntilDie);
                world[i+1][j]->setHasMove(true);
                world[i][j] = NULL;
            }
            break;
        case 1:
            if(world[i-1][j] == NULL){
                cout<<"left"<<endl;
                world[i-1][j] = new Doodlebug(i-1, j, BUG, age, _moveUntilDie);
                world[i-1][j]->setHasMove(true);
                world[i][j] = NULL;
            }
            break;
        case 2:
            if(world[i][j+1] == NULL){
                cout<<"down"<<endl;
                world[i][j+1] = new Doodlebug(i, j+1, BUG, age, _moveUntilDie);
                world[i][j+1]->setHasMove(true);
                world[i][j] = NULL;
            }
            break;
        case 3:
            if(world[i][j-1] == NULL){
                cout<<"up"<<endl;
                world[i][j-1] = new Doodlebug(i, j-1, BUG, age, _moveUntilDie);
                world[i][j-1]->setHasMove(true);
                world[i][j] = NULL;
            }
            break;
        default:
            break;
    }
}
