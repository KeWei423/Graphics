#include "shape.h"

enum ShapeIndexes { I = 0, O = 4, S = 8, Z = 12, T = 16, L = 20, J = 24 };
bool SHAPES[/*type*/][4][4] = {
                                    // I
                                    { {1,0,0,0},
                                      {1,0,0,0},
                                      {1,0,0,0},
                                      {1,0,0,0} },

                                    { {0,0,0,0},
                                      {0,0,0,0},
                                      {0,0,0,0},
                                      {1,1,1,1} },

                                    { {1,0,0,0},
                                      {1,0,0,0},
                                      {1,0,0,0},
                                      {1,0,0,0} },

                                    { {0,0,0,0},
                                      {0,0,0,0},
                                      {0,0,0,0},
                                      {1,1,1,1} },
                                    // O
                                    { {0,0,0,0},
                                      {0,0,0,0},
                                      {1,1,0,0},
                                      {1,1,0,0} },

                                    { {0,0,0,0},
                                      {0,0,0,0},
                                      {1,1,0,0},
                                      {1,1,0,0} },

                                    { {0,0,0,0},
                                      {0,0,0,0},
                                      {1,1,0,0},
                                      {1,1,0,0} },

                                    { {0,0,0,0},
                                      {0,0,0,0},
                                      {1,1,0,0},
                                      {1,1,0,0} },
                                    // S
                                    { {0,0,0,0},
                                      {0,0,0,0},
                                      {0,1,1,0},
                                      {1,1,0,0} },

                                    { {0,0,0,0},
                                      {1,0,0,0},
                                      {1,1,0,0},
                                      {0,1,0,0} },

                                    { {0,0,0,0},
                                      {0,0,0,0},
                                      {0,1,1,0},
                                      {1,1,0,0} },

                                    { {0,0,0,0},
                                      {1,0,0,0},
                                      {1,1,0,0},
                                      {0,1,0,0} },
                                    // Z
                                    { {0,0,0,0},
                                      {0,0,0,0},
                                      {1,1,0,0},
                                      {0,1,1,0} },

                                    { {0,0,0,0},
                                      {0,1,0,0},
                                      {1,1,0,0},
                                      {1,0,0,0} },

                                    { {0,0,0,0},
                                      {0,0,0,0},
                                      {1,1,0,0},
                                      {0,1,1,0} },

                                    { {0,0,0,0},
                                      {0,1,0,0},
                                      {1,1,0,0},
                                      {1,0,0,0} },
                                    // T
                                    { {0,0,0,0},
                                      {0,0,0,0},
                                      {0,1,0,0},
                                      {1,1,1,0} },

                                    { {0,0,0,0},
                                      {1,0,0,0},
                                      {1,1,0,0},
                                      {1,0,0,0} },

                                    { {0,0,0,0},
                                      {0,0,0,0},
                                      {1,1,1,0},
                                      {0,1,0,0} },

                                    { {0,0,0,0},
                                      {0,1,0,0},
                                      {1,1,0,0},
                                      {0,1,0,0} },
                                    // L
                                    { {0,0,0,0},
                                      {1,0,0,0},
                                      {1,0,0,0},
                                      {1,1,0,0} },

                                    { {0,0,0,0},
                                      {0,0,0,0},
                                      {1,1,1,0},
                                      {1,0,0,0} },

                                    { {0,0,0,0},
                                      {1,1,0,0},
                                      {0,1,0,0},
                                      {0,1,0,0} },

                                    { {0,0,0,0},
                                      {0,0,0,0},
                                      {0,0,1,0},
                                      {1,1,1,0} },
                                    // J
                                    { {0,0,0,0},
                                      {0,1,0,0},
                                      {0,1,0,0},
                                      {1,1,0,0} },

                                    { {0,0,0,0},
                                      {0,0,0,0},
                                      {1,0,0,0},
                                      {1,1,1,0} },

                                    { {0,0,0,0},
                                      {1,1,0,0},
                                      {1,0,0,0},
                                      {1,0,0,0} },

                                    { {0,0,0,0},
                                      {0,0,0,0},
                                      {1,1,1,0},
                                      {0,0,1,0} },
                                };

sf::Color colors[7] = { sf::Color::Red,
                        sf::Color::Green,
                        sf::Color::Blue,
                        sf::Color::Magenta,
                        sf::Color::Cyan,
                        sf::Color::Yellow,
                        sf::Color(255,128,0) };




Shape::Shape():posX (10),posY(0){

    Generate();
}


//==========================================================================================
//              Accessor
//==========================================================================================

//get color

sf::Color Shape::getColor()
{
    return colors[color];
}

//Get x-position
int Shape::GetPosX(){
    return posX;
}


//Get y-position
int Shape::GetPosY(){
    return posY;
}

//Get Element
int Shape::GetElement(int x, int y){
    return data[y][x];
}

//get shape index
int Shape::GetIndex()
{
    return shapeIndex;
}


//Mutator
void Shape::SetPosition(int x, int y){
    posX=x;
    posY=y;


}

//Fill Data
void Shape::FillData(){

    for(int i=0;i < 4;i++){

        for(int m=0;m < 4;m++){

            data[i][m] = SHAPES[shapeIndex][i][m];
        }
    }
}


//Generate
void Shape::Generate(){

    int g = (rand() % 7) * 4;
    shapeIndex = (ShapeIndexes)g;
    color = g / 4;
    FillData();
}

//Move
void Shape::Move(int x, int y){

    if(IsValid(x, y)){

        posX += x;
        posY += y;

    }
}

void Shape::Rotate(){

    int coIndex = shapeIndex;
    shapeIndex = ((shapeIndex + 1) % 4 == 0 ? shapeIndex - 3 : shapeIndex + 1);
    FillData();
    checkColon();
    if(!IsValid()){
        shapeIndex = coIndex;
        FillData();
    }

}

void Shape::checkColon(){

    int col=0;

    if (posX==WIDTH-2){
        for (int y=1;y<4;y++){
            for (int x=0;x<4;x++){
                if(SHAPES[shapeIndex][y][x]==1 && col <=x)
                    col=x;

            }
        }
     posX=posX-col+1;
    }
}

bool Shape::IsValid(int xOffset, int yOffset){

    for(int y=0;y < 4;y++){

        for(int x=0;x < 4;x++){

            if((data[y][x] && (posX + x + xOffset >= WIDTH || posX + xOffset < 0)) || (data[y][x] && (posY + y + yOffset > HEIGHT)) )

                return false;

        }
    }
    return true;
}

void Shape::DrawShape(sf::RenderWindow & window){

    for(int i=0;i < 4;i++){
        for(int m=0;m < 4;m++){
            if(data[i][m])
                drawQuad(window, (m + posX) * SIZE, (i + posY) * SIZE, colors[color]);
        }
    }
}


void Shape::drawQuad(sf::RenderWindow & window, float x, float y, sf::Color c)
{
    sf::RectangleShape rect(sf::Vector2f(SIZE-2, SIZE-2));
    rect.setPosition(x+1, y+1);
    rect.setFillColor(c);
    window.draw(rect);
}



