#ifndef WORMENGINE_H
#define WORMENGINE_H
#include <unistd.h>
//#include <curses.h>
#include "../game/gameengine.h"


class wormengine : public gameengine{
public:
    wormengine();
    wormengine(int x, int y);
    std::vector<gameToken> worm;
    int currentDir;
    bool started;
    int eat_number;
    int prevInput;

    bool take_action(int input);
    bool move(int dir);
    int is_fruit(int dir);
    bool is_body_or_wall(int dir);
    void eat(int number);
    void generate_food();
    void generate_wall();
    gameToken get_head();
};

#endif // WORMENGINE_H
