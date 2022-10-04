#include "Robot_game.h"
#include "Robot.h"
#include <algorithm>
#include <fstream>
#include <memory>
#include <iostream>
#include <sstream>

Robot_game::Robot_game()
{
    fstream myFile;
    string line;
    myFile.open("start.txt", ios::in);
    //populating the vector of pointers and the hashmap
    while (getline(myFile,line))
    {
        robots.push_back(make_shared<Robot>(line));
        auto &r =robots.back();
        fieldR[r->getCoordinates()] = r;
    }

}
//calling the show function after sorting the robots based on the ID
void Robot_game::game_show()
{
    sort_ID();
    for (auto &x: robots)
    {
        x->show();
    }

}
//checking if there is an active robot with a certain ID
shared_ptr<Robot> Robot_game:: find_robot(int ID)
{
    for (auto &x: robots)
    {
        //checking if the ID's match
        if (x->getID() == ID)
        {
            //return the pointer of that robot
            return x;
        }
    }
    //if they don't match return a null pointer
    return nullptr;


}

//sorting function based on the ID of the robots
void Robot_game::sort_ID()
{
    sort(robots.begin(),robots.end(),[](const shared_ptr<Robot> &robot1,const shared_ptr<Robot> &robot2)
    {
        return robot1->ID < robot2->ID;
    });
}
//sort based on the steps travelled
//when 2 robots have the same steps travelled, sort based on ID
void Robot_game::sort_travel()
{
    sort(robots.begin(),robots.end(),[](const shared_ptr<Robot> &robot1,const shared_ptr<Robot> &robot2)
    {
        return (robot1->travelled() == robot2->travelled() && robot1->ID < robot2->ID) || (robot1->travelled() < robot2->travelled())
               ;
    });
}
//print out the ID and steps travelled of the robots after sorting
void Robot_game::game_travelled()
{
    sort_travel();
    for (auto &x: robots)
    {
        cout<<x->ID<<" "<<x->travelled()<<endl;
    }
}

void Robot_game::game_within(int x)
{   //keep track of the number of robots that are within x steps from the origin
    int countt;
    for(auto &r: robots)
    {
        if(r->within(x))
        {
            countt++;
        }
    }
    //print out the number of robots within x steps from the origin
    cout<<countt<<endl;
}
//calling turnright function if there is an active robot with that ID
void Robot_game::game_turnright(int ID)
{
    auto s = find_robot(ID);
    if (s)
    {
        s->turnright();
    }

}
//calling turnleft function if there is an active robot with that ID
void Robot_game::game_turnleft(int ID)
{

    auto s = find_robot(ID);
    if (s)
    {
        s->turnleft();
    }

}

void Robot_game::game_move_robot(int ID)
{
    //variable used for keeping track of the coordinates of the  next position of a robot
    auto coordinates= pair<int,int>(0,0);
    auto s = find_robot(ID);
    if (s)
    {
        if(s->getDirection() == Robot::Direction::North){
            coordinates = pair<int,int>(s->getCoordinates().first,s->getCoordinates().second+1);
        }
        if(s->getDirection() == Robot::Direction::South){
            coordinates = pair<int,int>(s->getCoordinates().first,s->getCoordinates().second-1);
        }
        if(s->getDirection() == Robot::Direction::East){
            coordinates = pair<int,int>(s->getCoordinates().first+1,s->getCoordinates().second);
        }
        if(s->getDirection() == Robot::Direction::West){
            coordinates = pair<int,int>(s->getCoordinates().first-1,s->getCoordinates().second);
        }

        auto other_robot = fieldR[coordinates];
        //checking if there is another robot in the position the initial robot wants to move
        if (other_robot)
                {       //check if they are from the same team
                        if(other_robot->getTeam()!=s->getTeam())
                        {

                            remove_if(robots.begin(),robots.end(),[other_robot](const shared_ptr<Robot>&r1)
                            {
                                if(r1->getID()==other_robot->getID())
                            {

                                return true;
                            }
                            else
                            {
                                return false;
                            }

                            }
                          );
                            //remove the other robot's pointer from the vector and from the hashmap
                            robots.erase(find(robots.begin(),robots.end(),other_robot));
                            fieldR.erase(s->getCoordinates());
                            //remove the current robot from the hashmap
                            fieldR.erase(other_robot->getCoordinates());
                            //move the current robot
                            s->move_robot();
                            //update current robot position in the hashmap
                            fieldR[s->getCoordinates()] = s;

                        }
                        //if they are from the same team don't do nothings
                        if(other_robot->getTeam()==s->getTeam()){

                        }
                    }
        else{
            //update and move the current robot if there is no other robot in the next position
            fieldR.erase(s->getCoordinates());
            s->move_robot();
            fieldR[s->getCoordinates()] = s;

            }


    }
}





void Robot_game::readCommands()
{
    fstream myFile;
    //open file
    myFile.open("commands.txt", ios::in);
    if (myFile.is_open())
    {
        string line;
        while (!myFile.eof())
        {
            getline(myFile,line);
            vector<string> Commands;
            stringstream sstream(line);
            while(sstream.good())
            {
                string substring;
                getline(sstream,substring,' ');
                Commands.push_back(substring);
            }
            //Calls to relevant functions depending on the command read if the line is not empty
            if (!line.empty())
            {
                if(Commands.at(0) == "show")
                    game_show();

                if(Commands.at(0) == "travelled")
                    game_travelled();

                if(Commands.at(0) == "within")
                    game_within(stoi(Commands.at(1)));

                if(Commands.at(0) == "turnleft")
                    game_turnleft(stoi(Commands.at(1)));

                if(Commands.at(0) == "turnright")
                    game_turnright(stoi(Commands.at(1)));

                if(Commands.at(0) == "move")
                    game_move_robot(stoi(Commands.at(1)));

            }
        }
    }

}




