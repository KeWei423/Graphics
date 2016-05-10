#include "planet.h"
#include<cmath>
#include<iostream>
#include<ctime>
#include<cstdlib>
planet::planet()
{
    x=0;
    y=0;
    Radius=0;
    velocity_x=0;
    velocity_y=0;
    red=0;
    blue=0;
    green=0;
}

planet ::planet(int _x, int _y, int _Radius,int _red,int _blue,int _green)
{
   x=_x+_Radius;
   y=_y+_Radius;
   Radius=_Radius;
   velocity_x=0;
   velocity_y=0;
   red=_red;
   blue=_blue;
   green=_green;
}

int planet ::get_x()const
{
    return x;
}

int planet ::get_y() const
{
    return y;
}

double planet::get_radius()const
{
   return Radius;
}

double planet::get_velocity_x()
{
    return velocity_x;
}
double planet::get_velocity_y()
{
    return velocity_y;
}


void planet::move(const vector<planet>& V)   // change the position from the circles
{
  update_velocity(V);
  x=x+velocity_x;
  y=y+velocity_y;

}

void eating(planet &first_one, planet &sec_one)
{     
    if((first_one.Radius+sec_one.Radius)>=first_one.distance(sec_one))
        if(sec_one.Radius>=first_one.Radius){
             //momentum function (   MV (totol) = M1v + M2v   _)
            sec_one.velocity_x=(first_one.velocity_x* pow(first_one.Radius,3)+sec_one.velocity_x*pow(sec_one.Radius,3))/(pow(sec_one.Radius,3));
            sec_one.velocity_y=(first_one.velocity_y* pow(first_one.Radius,3)+sec_one.velocity_y*pow(sec_one.Radius,3))/(pow(sec_one.Radius,3));

            sec_one.Radius+=first_one.Radius/4;   // increase 1/4 radiius from smaller one

            first_one=planet(-1,-1,0,0,0,0);  //mark radius equal to 0 , then we delete it in big_bang
        }
        else{
            //momentum function (   MV (totol) = M1v + M2v   _)
            first_one.velocity_x=(sec_one.velocity_x* pow(sec_one.Radius,3)+first_one.velocity_x*pow(first_one.Radius,3))/(pow(first_one.Radius,3));
            first_one.velocity_y=(sec_one.velocity_y* pow(sec_one.Radius,3)+first_one.velocity_y*pow(first_one.Radius,3))/(pow(first_one.Radius,3));

            first_one.Radius+=sec_one.Radius/4;  // increase 1/4 radiius from smaller one

            sec_one=planet(-1,-1,0,0,0,0);     //mark radius equal to 0 , then we delete it in big_bang
        }

}
void big_bang(vector<planet>& V)
{
    for(int i=0;i<V.size();i++){      // put the circles together add radius
        for(int j=i+1; j< V.size();j++){
            eating(V[i],V[j]);
        }
    }

    for(int i=0;i<V.size();i++)    //delete who radius is 0   >>delete
    {
        if(V[i].get_radius()==0){
            V.erase(V.begin()+i);   // note : for delete
        }
    }

    for(int i=0;i<V.size();i++){           //  dont let the circles exit the screen
        if(V[i].get_x()+2*V[i].get_radius()>=SCREEN_WIDTH||V[i].get_x()<=0){
            V[i].velocity_x= -V[i].get_velocity_x();
        }
        if(V[i].get_y()+2*V[i].get_radius()>=SCREEN_HEIGHT||V[i].get_y()<=0){
            V[i].velocity_y= -V[i].get_velocity_y();
        }
    }
}
double planet::distance(const planet &other)
{
    double num;
    // distance= squrt  (  dx^2 + dy^2)
    num= sqrt(pow(x-other.x,2)+pow(y-other.y,2));
    return num;
}

void planet::update_velocity(const vector<planet>& V)
{
   double acc_x_total=0;
   double acc_y_total=0;
   double Dis=0;
   for(int i=0;i< V.size();i++){
      if(!(V[i].get_x()== x&&V[i].get_y()==y)){
          Dis=distance(V[i]);
          cout<<"Dis"<<Dis<<endl;

          //gravitational formular
          acc_x_total+= 100*((V[i].mass()/6)/pow(Dis,3))*((V[i].get_x()-x)/Dis);

          acc_y_total+= 100*((V[i].mass()/6)/pow(Dis,3))*((V[i].get_y()-y)/Dis);
      }
   }
   velocity_x+=acc_x_total;     // acc _ x + initial velocity _x (x direction)
   cout<<"acc_x"<<acc_x_total<<endl;
   velocity_y+=acc_y_total;     // acc _ y + initial velocity _y (y direction)
   cout<<"acc_y"<<acc_y_total<<endl;
}

int planet::get_Red(){
    return red;
}
int planet::get_Blue(){
    return blue;
}

int planet::get_Green(){
    return green;
}

void planet::color_random(){   //randow the color
    srand(time(0));
    green=70+(rand()%100);
    red=50+(rand()%40);
    blue=80+(rand()%120);
}
void fill_particle(vector<planet>& V){    //random 6 circles
    planet temp;
     srand(time(0));
    for(int i=0; i<6;i++){
        temp.Radius=i*5;
        temp.x=i*30+(rand()%1420);
        temp.y=i*40+(rand()%620);
        V.push_back(temp);
    }
}

double planet::mass()const
{   double Mass;
    Mass=  pow(Radius,3);
    return Mass;
}
