#ifndef HUMAN_H
#define HUMAN_H
#include"Player.h"

#include<iostream>

class Human : public Player
{
public:
    Human();
    //human implementation of virtual makeMove function
    int makeMove(int currentBet);
    bool isHuman();
    void checkHand(std::string suit[],std::string face[]);
    ~Human();
};

#endif //HUMAN_H