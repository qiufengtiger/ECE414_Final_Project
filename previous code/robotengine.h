#ifndef ROBOTENGINE_H
#define ROBOTENGINE_H
#include "../game/gameengine.h"

class robotengine : public gameengine{
public:
    robotengine();
    robotengine(int x, int y);
    std::vector<gameToken*> robots;
    int currentDir;
    bool started;
    bool game_lose;
    bool loading;


    void initialize(int x, int y, int turn);
    int random_num(int size);
    void random_arr(int size, int arr[], int n);
    void move(int dir);
    bool is_wall(int dir);
    bool is_body(int dir);
    bool safe_move(int dir);
    void teleport();
    void take_action(int input);
    void robot_move();
    bool game_end();
//    void game_win();
};

#endif // ROBOTENGINE_H
