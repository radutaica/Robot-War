#include "Robot.h"
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;
//constructor
Robot::Robot(string a)
{
  string part;
  stringstream sstream(a);

  getline(sstream, part, ' ');
  this->ID = stoi(part);

  getline(sstream, part, ' ');
  this->team = stoi(part);

  getline(sstream, part, ' ');
  this->x_coordinate = stoi(part);

  getline(sstream, part, ' ');
  this->y_coordinate = stoi(part);

  this->coordinates.first = x_coordinate;
  this->coordinates.second = y_coordinate;
  this->direction = Direction::North;


}
//prints out the attributes of a robot
void Robot::show(){
    cout<<this->ID<<" "<<this->team<<" "<<this->coordinates.first<<" "<<this->coordinates.second<<endl;

    }
//returns the number of steps a robot travelled
int Robot::travelled(){
    return this->steps;

}
//checks if a robot is within n steps from the origin
bool Robot::within(int n){
    return (abs(x_coordinate) + abs(y_coordinate))<=n;
}
//returns x coordinate
int Robot::getX(){
    return this->x_coordinate;

}
//returns y coordinate
int Robot::getY(){
    return this->y_coordinate;

}
//returns the coordinates as a type pair
pair<int,int>Robot::getCoordinates(){
    return this->coordinates;
}
//returns the ID of a robot
int Robot:: getID(){
    return this->ID;
}

//changes direction clockwise
void Robot :: turnright(){
    switch(this->direction){
        case Direction::North:
            direction = Direction::East;
            break;
        case Direction::East:
            direction = Direction::South;
            break;
        case Direction::South:
            direction = Direction::West;
            break;
        case Direction::West:
            direction = Direction::West;


    }
}
//returns the direction of a robot
Robot::Direction Robot:: getDirection(){
    return direction;
}
//returns the team of a robot
int Robot:: getTeam(){
    return this->team;
}
//changes direction anticlockwise
void Robot :: turnleft(){
    switch(this->direction){
        case Direction::North:
            direction = Direction::West;
            break;
        case Direction::West:
            direction = Direction::South;
            break;
        case Direction::South:
            direction = Direction::East;
            break;
        case Direction::East:
            direction = Direction::North;


    }
}

//function for moving the robot based on the direction is facing
void Robot::move_robot(){
    switch(this->direction) {
        case Direction::North:
            //incrementing both the y coordinate and the y coordinate in the pair
            this->y_coordinate++;
            this->coordinates.second++;
            steps++;
            break;

        case Direction::South:
            //decrementing both the y coordinate and the y coordinate in the pair
            this->y_coordinate--;
            this->coordinates.second--;
            steps++;
            break;

        case Direction::East:
            //incrementing both the x coordinate and the x coordinate in the pair
            this->x_coordinate++;
            this->coordinates.first++;
            steps++;
            break;

        case Direction::West:
            //decrementing both the x coordinate and the x coordinate in the pair
            this->x_coordinate--;
            this->coordinates.first--;
            steps++;
            break;
    }

}



