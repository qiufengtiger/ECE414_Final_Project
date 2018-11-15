#include <iostream>
#include "robotengine.h"

robotengine::robotengine(){

}

robotengine::robotengine(int x, int y){
    this->x = x;
    this->y = y;
    turn  = 1;
    board = new gameboard<gameToken>(x, y);
    game_lose = false;
    //add wall
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            if(i == 0 || j == 0 || i == x - 1 || j == y - 1){
                board->add_token(WALL, i, j);
            }
        }
    }
    int px =  random_num(x);
    int py =  random_num(y);
    if(board->get_token_ptr(px,py)==nullptr){
         board->add_token(PLAYER, px,py);
    }

    //add player and robots
    initialize(x,y,1);

}

void robotengine::initialize(int x, int y, int turn){

    //board->clear_board(PLAYER);
    board->clear_board(ROBOT);
    board->clear_board(TRASH);
    int robotcnt = turn * 10;


    while(robotcnt!=0){
        int rx = random_num(x);
        int ry = random_num(y);
        if(board->get_token_ptr(rx,ry)==nullptr){
            board->add_token(ROBOT, rx, ry);
            robotcnt--;
        }
    }
    loading = false;
}

int robotengine::random_num(int size){
    //std::srand(time(0));
    return rand()%(size-2)+1;
}

void robotengine::take_action(int input){
    switch(input){
        case 49:
            move(1);
            break;
        case 50:
            move(2);
            break;
        case 51:
            move(3);
            break;
        case 52:
            move(4);
            break;
        case 53:
            teleport();
            break;
        case 54:
            move(6);
            break;
        case 55:
            move(7);
            break;
        case 56:
            move(8);
            break;
        case 57:
            move(9);
            break;
        }

}

void robotengine::move(int dir){
    gameToken* playerptr = board->get_token_by_id(202);
    if(safe_move(dir)&& playerptr->player_is_movable(dir)){
        playerptr->playerMove(dir);
        board->clear_board(PLAYER);
        board->add_existed_token(playerptr);
        robot_move();
    }
    else{
        return;
    }
    if(game_end()){
        turn = turn + 1;
        loading = true;
        initialize(x,y,turn);
    }
    return;
}


bool robotengine::safe_move(int dir){
    gameToken* playerptr = board->get_token_by_id(202);
//    int tarx = board->get_token_by_id(202)->target(dir)->x;
//    int tary = board->get_token_by_id(202)->target(dir)->y;
    for(int i = 0; i < turn*10; i++){
        if(get_token_by_id(board->nextTokenId-i-1)==nullptr){
            continue;
        }else if(get_token_by_id(board->nextTokenId-i-1)->type == ROBOT){
            if(board->get_token_by_id(board->nextTokenId-i-1)->target(dir)== playerptr){
                return false;
            }else{
                return true;
            }
        }else{
            continue;
        }
    }
    return true;
}

bool robotengine::game_end(){
    for(int i = 0; i < turn*10; i++){
        if(get_token_by_id(board->nextTokenId-i-1)==nullptr){
            continue;
        }else if(get_token_by_id(board->nextTokenId-i-1)->type == ROBOT){
            return false;
        }else{
            continue;
        }
    }

    return true;
}



void robotengine::teleport(){
    std::srand(time(0));
    gameToken* playerptr = board->get_token_by_id(202);
    int tx = random_num(this->x);
    int ty = random_num(this->y);
    if(board->get_token_ptr(tx,ty)==nullptr){
        playerptr->x = tx;
        playerptr->y = ty;
        board->clear_board(PLAYER);
        board->add_existed_token(playerptr);
    }
    else{
        game_lose=true;
    }
}

void robotengine::robot_move(){
    gameToken* playerptr = board->get_token_by_id(202);
    int px = playerptr->x;
    int py = playerptr->y;
    for(int i = 0; i<turn*10; i++){
        if(get_token_by_id(board->nextTokenId-i-1)==nullptr){
            continue;
        }else if(get_token_by_id(board->nextTokenId-i-1)->type == ROBOT){
            gameToken* robotptr = board->get_token_by_id(board->nextTokenId-i-1);

                if(robotptr->x<px && robotptr->y<py){
                    robotptr->robotMove(3);
                    board->clear_board_id(board->nextTokenId-i-1);
                    board->add_existed_token(robotptr);
                }
                if(robotptr->x<px && robotptr->y==py){
                    robotptr->robotMove(6);
                    board->clear_board_id(board->nextTokenId-i-1);
                    board->add_existed_token(robotptr);
                }
                if(robotptr->x<px && robotptr->y>py){
                    robotptr->robotMove(9);
                    board->clear_board_id(board->nextTokenId-i-1);
                    board->add_existed_token(robotptr);
                }
                if(robotptr->x==px && robotptr->y<py){
                    robotptr->robotMove(2);
                    board->clear_board_id(board->nextTokenId-i-1);
                    board->add_existed_token(robotptr);
                }
                if(robotptr->x==px && robotptr->y>py){
                    robotptr->robotMove(8);
                    board->clear_board_id(board->nextTokenId-i-1);
                    board->add_existed_token(robotptr);
                }
                if(robotptr->x>px && robotptr->y<py){
                    robotptr->robotMove(1);
                    board->clear_board_id(board->nextTokenId-i-1);
                    board->add_existed_token(robotptr);
                }
                if(robotptr->x>px && robotptr->y==py){
                    robotptr->robotMove(4);
                    board->clear_board_id(board->nextTokenId-i-1);
                    board->add_existed_token(robotptr);
                }
                if(robotptr->x>px && robotptr->y>py){
                    robotptr->robotMove(7);
                    board->clear_board_id(board->nextTokenId-i-1);
                    board->add_existed_token(robotptr);
                }

        }else{
            continue;
        }
    }

}


