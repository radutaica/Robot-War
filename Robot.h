#ifndef ROBOT_H
#define ROBOT_H
#include <string>
#include <sstream>
#include <vector>
#include <map>

using namespace std;


class Robot
{
public:
    //using enum class to define direction possibilities
    enum class Direction {North,South,West,East};
    Direction direction;

    int ID;
    int team;
    int x_coordinate;
    int y_coordinate;

    Robot(string a);
    void show();
    int travelled();
    int getX();
    int getY();
    pair<int,int>getCoordinates();
    bool within(int n);
    void turnleft();
    void turnright();
    int getID();
    void move_robot();
    int getTeam();
    Direction getDirection();

private:
    int steps;
    pair<float,float> coordinates;



};

#endif // ROBOT_H
