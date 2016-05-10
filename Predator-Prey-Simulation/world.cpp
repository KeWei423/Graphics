#include "world.h"



World::World()
{
    cout<<"debug: World()"<<endl;
    Init();
    InitW();
    InitA();
    InitD();
}


void World::Init(){
    cout<<"debug: World::Init()"<<endl;
   for(int i = 0; i< BOX_NUMB; i++){
       for(int j= 0; j< BOX_NUMB; j++){
           _grid[i][j] = NULL;
       }
   }
}


void World::InitW(){
    cout<<"debug: World::InitW()"<<endl;
    for(int i = 0; i< BOX_NUMB; i++){
        for(int j= 0; j< BOX_NUMB; j++){
            if(i==0 || i==BOX_NUMB-1 ||j==0 || j==BOX_NUMB-1){
                 _grid[i][j] = new Wall(i, j, WALL,0);
            }
        }
    }
}


void World::InitD(){
    cout<<"debug: World::InitD()"<<endl;
    for(int i = 0; i< BUGINIT;){

        int r = rand()%MAX+1;
        int c = rand()%MAX+1;

        if(_grid[r][c] == NULL){
            _grid[r][c] = new Doodlebug(r,c,BUG,0);
            i++;
        }
    }
//    _grid[10][10] = new Doodlebug(10,10,BUG,0);
}


void World::InitA(){
    cout<<"debug: World::InitA()"<<endl;
    for(int i = 0; i<ANTINIT;){
        int r = rand()%MAX+1;
        int c = rand()%MAX+1;

        if(_grid[r][c] == NULL){
            _grid[r][c] = new Ant(r, c, ANT, 0);
            i++;
        }
    }
//    _grid[9][9] = new Ant(9, 9, ANT, 0);
//    _grid[9][11] = new Ant(9, 11, ANT, 0);
}


void World::DrawWorld(sf::RenderWindow &window){
    for(int i= 0; i < BOX_NUMB; i++){
        for(int j=0; j<BOX_NUMB; j++){
            if(_grid[i][j] != NULL){
                _grid[i][j]->DrawOrg(window);
            }
        }
    }
}


void World::Move(){
    cout<<"debug: World::Move()"<<endl;
    MoveD();
    MoveA();
}



void World::MoveD(){
    cout<<"debug: World::MoveD()"<<endl;
    for(int i=0; i<BOX_NUMB; i++){
        for(int j=0; j<BOX_NUMB; j++){
            if((_grid[i][j] != NULL) && _grid[i][j]->getType() == BUG) {
                if(_grid[i][j]->hasMoved() == false){
                int age = _grid[i][j]->age();
                _grid[i][j]->Move(_grid, i ,j, age);
                }
            }
        }
    }
}



void World::MoveA(){
    cout<<"debug: World::MoveA()"<<endl;
    for(int i=0; i<BOX_NUMB; i++){
        for(int j=0; j<BOX_NUMB; j++){
            if(_grid[i][j] != NULL && _grid[i][j]->getType() == ANT) {
                if(_grid[i][j]->hasMoved() == false){
                    int age = _grid[i][j]->age();
                    _grid[i][j]->Move(_grid, i ,j, age);
                }
            }
        }
    }
}


void World::Reset(){
    cout<<"debug: World::Reset()"<<endl;
    for(int i=0; i<BOX_NUMB; i++){
        for(int j =0; j<BOX_NUMB; j++){
            if(_grid[i][j]!=NULL){
                _grid[i][j]->setHasMove(false);
            }
        }
    }
}



void World::Starve(){
    cout<<"debug: World::Starve()"<<endl;
    for(int i=0; i<BOX_NUMB; i++){
        for(int j =0; j<BOX_NUMB; j++){
            if(_grid[i][j] != NULL && _grid[i][j]->getType() == BUG){
                if(_grid[i][j]->Starve()){
                    delete (_grid[i][j]);
                    _grid[i][j]=NULL;
                }
            }
        }
    }
}


void World::Breed(){
    cout<<"debug: World::Breed()"<<endl;
    for(int i=0; i<BOX_NUMB; i++){
        for(int j=0; j<BOX_NUMB; j++){
            if(_grid[i][j] != NULL && _grid[i][j]->hasMoved() == true) {
                _grid[i][j]->Breed(_grid, i, j);
            }
        }
    }
}



int World::NumbAnt(){
    cout<<"debug: World::NumbAnt()"<<endl;
    int count = 0;
    for(int i=0; i<BOX_NUMB; i++){
        for(int j=0; j<BOX_NUMB; j++){
            if(_grid[i][j]->getType() == ANT){
                count++;
            }
        }
    }
    return count;
}


int World::NumbBug(){
    cout<<"debug: NumbBug()"<<endl;
    int count = 0;
    for(int i=0; i<BOX_NUMB; i++){
        for(int j=0; j<BOX_NUMB; j++){
            if(_grid[i][j]->getType() == BUG){
                count++;
            }
        }
    }
    return count;
}



