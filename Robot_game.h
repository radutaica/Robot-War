#ifndef ROBOT_GAME_H
#define ROBOT_GAME_H
#include <vector>
#include <map>
#include "Robot.h"
#include <memory>
using namespace std;
class Robot_game
{
    public:

        void game_travelled();
        void game_show();
        void move_robot(int ID);
        void readCommands();
        void game_within(int x);
        void game_turnright(int ID);
        void game_turnleft(int ID);
        void game_move_robot(int ID);
        shared_ptr<Robot> find_robot(int ID);
        Robot_game();
    private:
        vector<shared_ptr<Robot>> robots;
        void sort_ID();
        void sort_travel();
        map<pair<int,int>,shared_ptr<Robot>> fieldR;



};

#endif // ROBOT_GAME_H
