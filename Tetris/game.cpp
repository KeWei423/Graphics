#include "game.h"

//----------------------------------------------------------
// Constructor:
// * set up randonmizer for color and shape
// * set up window size, frame limit
// * upload text font, backgound music, and use interface
//----------------------------------------------------------
game::game()
{
    srand(time(0));
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "!!Tetris!!");
    window.setFramerateLimit(30);
//    Music();
    gameFont.loadFromFile("game-regular.ttf");
    TextInit();
}

//-------------------------------------
// Background: music, interface, image
//-------------------------------------
void game::TextInit()
{
    //set the font
    startText.setFont(gameFont);
    startText.setString("Press [Enter] to Start");
    startText.setCharacterSize(20);
    startText.setColor(sf::Color::White);
    startText.setPosition(200, 370);

    score.setFont(gameFont);
    score.setCharacterSize(30);//we need to set location in relation to window.
    score.setColor(sf::Color::White);
    score.setPosition(600,400);



    END.setFont(gameFont);
    END.setString("GAME OVER");
    END.setCharacterSize(40);
    END.setColor(sf::Color::Red);
    END.setPosition(200,300);

    info.setFont(gameFont);
    info.setString("[x]Exit    [Enter]Play again");
    info.setCharacterSize(20);
    info.setColor(sf::Color::Red);
    info.setPosition(200,340);

}


void game::Music()
{
    if(!theme.openFromFile("theme.wav"))
    {
        cout<<"theme.wav NOT find"<<endl;
    }
    theme.play();
}


void game::Logo()
{
    if(!logoText.loadFromFile("LOGO.png"))
    {
        cout<<"Error: Image load Failed"<<endl;
    }

    logo.setTexture(logoText);
    logo.setPosition(200,150);
    window.draw(logo);
}


void game::UserInter()
{
    if(!UIText.loadFromFile("Tetris-UI.png"))
    {
        cout<<"Error: UI image load Failed"<<endl;
    }

    UI.setTexture(UIText);
    UI.setPosition(0,0);
    window.draw(UI);
}


//---------------------------------------------------------------------------------
// ProcessEvent:
// * looking for input commands from the keyboard to manipulate one tetris piece
// * rotate, move left, move right, and drop down
// * clear the shape after each command
//----------------------------------------------------------------------------------
void game::ProcessEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    // check the type of the event...
   {
       switch (event.type)
       {
           // window closed
           // "close requested" event: we close the window
           case sf::Event::Closed:
               window.close();
               break;

           // key pressed
           case sf::Event::KeyPressed:
               Shape s=fig;
               Shape figHold;

               //hold
               if(event.key.code==sf::Keyboard::H){

                   figHold=fig;
                   figHold.SetPosition(10,10);
//                 fig=figTop;

               }
               if(event.key.code==sf::Keyboard::Up)
               {
                   std::cout<<"Rotate"<<endl;
                   //rotate function
                   fig.Rotate();
                   if(map.IsCollision(fig))
                   {
                       fig=s;
                   }
               }
               if(event.key.code==sf::Keyboard::Space)
               {
                   cout<<"Hard drop"<<endl;
                   while(!map.IsCollision(fig))
                   {
                       fig.Move(0,1);
                   }
               }
               if(event.key.code==sf::Keyboard::Left)
               {
                   cout<<"Left"<<endl;
                   fig.Move(-1, 0);
                   if(map.IsCollision(fig))
                       fig = s;
               }
               if(event.key.code==sf::Keyboard::Right)
               {
                   cout<<"Right"<<endl;
                   fig.Move(1, 0);
                   if(map.IsCollision(fig))
                       fig = s;
               }
               if(event.key.code==sf::Keyboard::Down)
               {
                    cout<<"Down"<<endl;
                    if(tick<=10)
                    {
                        fig.Move(0,3);
                    }
               }
               if(event.key.code==sf::Keyboard::Return){
                   map.Reset();
                   gameOver=false;
                   Start=false;
               }
               break;
//           default:
//               break;
       }//event type
   }//pollEvent
   window.clear();
}


//----------------------------------------------------------------------------------
// CheckStart:
//  * display the starting image and text at start
//  * or alreaddy startedd then, check for update
//----------------------------------------------------------------------------------
void game::CheckStart()
{
    if(!Start)//while not game over is here
    {
        UserInter();
        Update();
    }
    else
    {
        Logo();
        window.draw(startText);
    }
}

//----------------------------------------------------------------------------------------
// Update:
// * if the game did not end, the move the piece downward
// * when the peice is falling always ask if the piece hits the bottom or collide with
//   other pieces
// * and then draw this new piece at its new position
// * check the timer
// * when pieces piled up, one should chekc for game over by check if the piece hits the
//   upper boundry which is when height =0;
// * once the game is over display the "game over" text
//----------------------------------------------------------------------------------------
void game::Update()
{
    CheckEnd();
    Move();
    CheckCollision();
    UpdateScore();
    Draw();
    CheckTick();
    CheckTop();   
}


void game::CheckEnd()
{
    newFig.SetPosition(30,6);
    if(gameOver)
    {
//        window.display();
        window.draw(END);
        window.draw(info);
//        map.Reset();
    }
}


void game::Move()
{
    if(tick%5 == 0  && !gameOver)
    {
        fig.Move(0,1);
    }
}


void game::CheckCollision()
{
    if(map.IsCollision(fig)&&(!gameOver))
    {
        map.AddPart(fig);
        map.DestroyLines();
        fig=newFig;
        newFig=Shape();
        newFig.SetPosition(30,6);
        fig.SetPosition(WIDTH/2, 0);
    }
}


void game::Draw()
{
    map.DrawGrid(window);
    fig.DrawShape(window);
    window.draw(score);
    newFig.DrawShape(window);
}

void game::UpdateScore()
{
    string holdScore=int2str(map.GetScore());
    score.setString(holdScore);
}

void game::CheckTick()
{
    if(tick<=5)
    {
        tick++;
    }
    else
    {
        tick=1;
    }
}


void game::CheckTop()
{
    if(map.IsFull())
    {
        gameOver=true;
    }
}


void game::Render()
{
   window.display();
}


void game::Run()
{
   while (window.isOpen())
   {
       UserInter();
       SelfPlayer();
       ProcessEvents();
       CheckStart();
       Render(); //display
   }
}

void game::SelfPlayer(){

    int x,y;
    Shape l=fig;
    if (fig.GetIndex()==0){

           fig.Move(-1,0);
    }
    else{
        map.CheckPiece(x,y,l);
        fig=l;
        while (fig.GetPosX()>x&&x<WIDTH/2){

            fig.Move(-1,0);
        }
        while (fig.GetPosX()<x&&x>WIDTH/2)
            fig.Move(1,0);
    }
}


//===================
string int2str(int source)
{
    stringstream str;
    str<<source;
    return str.str();
}
