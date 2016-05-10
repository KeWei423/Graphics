#include "grid.h"
//===========CTOR
Grid::Grid()
{
    Reset();
}
//==========
void Grid::Reset()
{
    score = 0;
    for(int y=0;y < HEIGHT;y++)
        for(int x=0;x < WIDTH+12;x++)
            data[y][x] = 0;
}
//==========Game Functions
bool Grid::IsCollision(Shape part)
{
    for(int y=0;y < 4;y++)
        for(int x=0;x < 4;x++)
            if((part.GetPosY() + y >= 0) && ( ( data[part.GetPosY() + y + 1][part.GetPosX() + x] &&
                part.GetElement(x, y) ) ||( part.GetElement(x, y) && part.GetPosY() + y >= HEIGHT - 1)) )
                return true;
    return false;
}

void Grid::AddPart(Shape part)
{
    for(int y=0;y < 4;y++)
        for(int x=0;x < 4;x++)
            if(part.GetElement(x, y)){
                data[part.GetPosY() + y][part.GetPosX() + x] = 1;
                gridCol[part.GetPosY()+y][part.GetPosX()+x]=part.getColor();
            }

}

void Grid::ApplyGravity(int h)
{
    for(int y=h;y > -1;y--)
        for(int x=0;x < WIDTH;x++)
            if(y < HEIGHT - 1 && data[y+1][x] == 0 && data[y][x])
            {
                data[y][x] = 0;
                data[y+1][x] = 1;

            }
}

void Grid::DestroyLines()
{
    for(int y=0;y <HEIGHT;y++)
    {
        bool good = true;
        for(int x=0;x <WIDTH;x++)
            if(!data[y][x])
            {
                good = false;
                break;
            }
        if(good)
        {
            score++;
            for(int x=0;x < WIDTH;x++)
                data[y][x] = 0;
            ApplyGravity(y);
            y=0;
        }
    }
}

bool Grid::IsFull()
{
    for(int x=0;x < WIDTH;x++)
        if(data[0][x])
            return true;
    return false;
}



void draw(sf::RenderWindow & window, float x, float y, sf::Color c)
{

    sf::RectangleShape rect(sf::Vector2f(SIZE-1, SIZE-1));
    rect.setPosition(x+1, y+1);
    rect.setFillColor(c);
    window.draw(rect);
}


void Grid::DrawGrid(sf::RenderWindow & window)
{

    for(int i=0;i <HEIGHT;i++){
        for(int m=0;m <WIDTH;m++){
//            int c=s.GetColor();
            if(data[i][m])
                ::draw(window, m * SIZE, i * SIZE, gridCol[i][m]);
        }
    }
}

//===========Accessor
int Grid::GetScore()
{
    return score;
}

bool Grid::CheckPiece(int& col, int& row, Shape& s){

    Shape hold=s;

    for (int r=HEIGHT-1;r>0;r--)

        for (int c=1;c<WIDTH-3;c++){

            if (isValid(c,r,hold)&&data[r-1][c]!=1){
                col=c;
                row=r;
                s=hold;
                return true;

            }
            else
                hold.Rotate();

         }
    return false;
}



bool Grid:: isValid(int col,int row,Shape s){

    for (int c=0;c<2;c++){

        int result=data[row][col+c]+s.GetElement(c,3);

        if (result==2||s.GetElement(0,3)==0){

            return false;
        }
    }

    return true;

}
