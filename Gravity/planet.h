#ifndef PLANET_H
#define PLANET_H
#include<vector>
#include<constants.h>
using namespace std;

class planet
{
public:
    planet();
    planet(int _x, int _y, int _Radius,int _red,int _blue,int _green);

    void move(const vector<planet>& V);  //  move
    double distance(const planet &other);
    void update_velocity(const vector<planet>& V); // total Velocity = initial velocity + acc *t

    int get_x()const;
    int get_y()const;
    double get_radius()const;
    double get_velocity_x();      // should add the acc(not const)
    double get_velocity_y();

    friend void eating(planet &first_one, planet &sec_one);  // merge circles
    friend void big_bang(vector<planet>& V);                // delete the smaller one ( mark the radius to 0)

    double mass()const;

    int get_Red();    //  R B G
    int get_Blue();
    int get_Green();

    void color_random();   // random color

    friend void fill_particle(vector<planet> &V);    //random 6 circles to screen

    int x;
    int y;
    int Radius;   // radius;
    double velocity_x;     //velocity
    double velocity_y;
    int red;
    int blue;
    int green;

};

#endif // PLANET_H
