#ifndef COMPUTER_H
#define COMPUTER_H
#include"Player.h"

#include<iostream>

class Computer : public Player
{
public:
    Computer();
    //computer implementation of virtual makeMove function
    int makeMove(int currentBet);
    char getType();
    bool isHuman();
    void checkHand(std::string suit[],std::string face[]);
    ~Computer();
};

#endif //COMPUTER_H