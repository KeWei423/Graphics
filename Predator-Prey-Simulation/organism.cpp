#include "organism.h"

Organism::Organism()
{
//    cout<<"debug: org default constructor"<<endl;
}


Organism::Organism(int r, int c, int type, int age)
{
//    cout<<"debug: :Organism(int r, int c, int type, int age)"<<endl;
    _type = type;
    _lifeSpand = age;
    _hasMoved  = false;
}


int Organism::getType(){
//    cout<<"debug: Organism::getType()"<<endl;
    return _type;
}


ostream& operator <<(ostream& outs, const Organism& printThis){
    printThis.Print(outs);
    return outs;
}



void Organism::Breed(Organism *world[][BOX_NUMB], int i, int j/*, int age*/){
//    cout<<"debug: Organism::Breed()"<<endl;
    world[i][j]->_lifeSpand++;
}


int Organism::age(){
//    cout<<"debug: Organism::age()"<<endl;
    return _lifeSpand;
}


void Organism::setHasMove(bool move){
//    cout<<"debug: Organism::setHasMove(bool move)"<<endl;
    _hasMoved = move;
}


bool Organism::hasMoved(){
//    cout<<"debug: Organism::hasMoved()"<<endl;
    return _hasMoved;
}

