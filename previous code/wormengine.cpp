#include "wormengine.h"

wormengine::wormengine(){

}

wormengine::wormengine(int x, int y){
    this->x = x;
    this->y = y;

    started = false;
    currentDir = 6;
    eat_number = 0;
    prevInput = -1;
    int initial_length = 4;
    board = new gameboard<gameToken>(x, y);
    //add wall
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            if(i == 0 || j == 0 || i == x - 1 || j == y - 1){
                board->add_token(WALL, i, j);
            }
        }
    }

    worm.push_back(board->add_token(PLAYER, 5, 3));//head
    for(int i = initial_length; i > 1; i--){
        worm.push_back(board->add_token(TRASH, i, 3));//body
    }
    generate_food();
}

bool wormengine::take_action(int input){
    switch(input){
        //down arrow or number 2
        case 50:
        case 0402:
            return move(2);
        //left arrow or number 4
        case 52:
        case 0404:
            return move(4);
        //right arrow or number 6
        case 54:
        case 0405:
            return move(6);
        //up arrow or number 8
        case 56:
        case 0403:
            return move(8);
    }
    return true;
}

gameToken wormengine::get_head(){
    return worm.front();
}

void wormengine::eat(int number){
    eat_number = number;
    board->score += number;
}

/**
 * move the worm based on input dir
 */
bool wormengine::move(int dir){
    gameToken head = get_head();
    if(is_body_or_wall(dir)){
        return false;
    }
    if(is_fruit(dir) != -1){
        eat(is_fruit(dir));
        head.target(dir)->remove_from_play();
        generate_food();
        generate_wall();
    }
    int lastX = worm.back().x;
    int lastY = worm.back().y;

    board->clear_board(PLAYER);
    board->clear_board(TRASH);
    for(int i = worm.size() - 1; i > 0; i--){
        worm[i].x = worm[i - 1].x;
        worm[i].y = worm[i - 1].y;
        board->add_existed_token(&worm[i]);
    }
    worm[0] = head.playerMove(dir);
    board->add_existed_token(&worm[0]);

    if(eat_number > 0){
        worm.push_back(board->add_token(TRASH, lastX, lastY));
        eat_number--;
    }
    board->add_existed_token(&worm.back());
    return true;
}

/**
 * generate a new food
 */
void wormengine::generate_food(){
    std::srand(time(0));
    int fruit_size = 0;
    while(fruit_size == 0){
        fruit_size = rand() % 10;
    }
    int fruitPosX = 0;
    int fruitPosY = 0;
    while(true){
        fruitPosX = rand() % x;
        fruitPosY = rand() % y;
        if(get_token_ptr(fruitPosX, fruitPosY) == nullptr)
            break;
    }
    gameToken *fruit = new gameToken(ROBOT, fruit_size);
    fruit->x = fruitPosX;
    fruit->y = fruitPosY;
    //solve add_existed_token that has no id with it
    fruit->id = -2;
    board->add_existed_token(fruit);
}

/**
 * generate a new wall when a food is eaten
 */
void wormengine::generate_wall(){
    std::srand(time(0));
    int wallPosX = 0;
    int wallPosY = 0;
    while(true){
        wallPosX = rand() % x;
        wallPosY = rand() % y;
        if(get_token_ptr(wallPosX, wallPosY) == nullptr)
            break;
    }
    gameToken *wall = new gameToken(WALL);
    wall->x = wallPosX;
    wall->y = wallPosY;
    board->add_existed_token(wall);
}

/**
 * check if it is a fruit and return the fruit size
 */
int wormengine::is_fruit(int dir){
    gameToken head = get_head();
    if(head.target(dir) == nullptr)
        return -1;
    if(head.target(dir)->type == ROBOT){
        return head.target(dir)->number;
    }
    return -1;
}

/**
 * check the condition when the game ends
 */
bool wormengine::is_body_or_wall(int dir){
    gameToken head = get_head();
    if(head.target(dir) == nullptr)
        return false;
    else if((head.target(dir)->type == TRASH) || (head.target(dir)->type == WALL)){
        return true;
    }
    return false;
}
