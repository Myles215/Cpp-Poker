#include"Computer.h"
#include<iostream>

Computer::Computer() {
    //std::cout<<"new computer created"<<std::endl;
    gameStatus = true;
    roundStatus = true;
}

bool Computer::isHuman() {
    return false;
}

int Computer::makeMove(int currentBet) {
    int random;
    random = rand();
    int choice;
    //every time the computer player makes a move
    //they should check their points
    //if they have low points they should either 
    //fold, check or bluff as they are unlinkely to win
    //this will be decided by a random chance
    if (points<9) {
        random = random%7;
        if (random==0) {
            choice = -1;
        } else if (random>0 || random<4) {
            choice = (currentBet-bet);
        } else {
            choice = (currentBet - bet) + funds*0.15;
        }
    } else if (points>=9 && points<19) {
        random = random%9;
        if (random==0) {
            choice = -1;
        } else if (random>0 && random<4) {
            choice = (currentBet-bet);
        } else if (random>3 && random<7) {
            choice = (currentBet-bet) + funds*0.2;
        } else {
            choice = (currentBet - bet) + funds *0.3;
        }
    } else {
        random = random%11;
        if (random==0) {
            choice = -1;
        } else if (random>0 && random<3) {
            choice = (currentBet - bet);
        } else if (random>2 && random<6) {
            choice = (currentBet - bet) + funds*0.3;
        } else if (random>5 && random<9) {
            choice = (currentBet - bet) + funds*0.4;
        } else {
            choice = (currentBet - bet) + funds*0.5;
        }
    }

    if (choice>=funds) {
        choice = funds;
        std::cout<<"all in"<<std::endl;
        allIn = true;
        roundStatus = false;
    }

    if (choice<0) {
        roundStatus = false;
        return -1;
    }

    bet = bet + choice;
    funds = funds - choice;
    
    return choice;

}

void Computer::checkHand(std::string suit[],std::string face[]) {
    
    //output card number and suit
    std::cout<<face[handCards[1]]<<" of "<<suit[handCards[0]]<<std::endl;
    std::cout<<face[handCards[3]]<<" of "<<suit[handCards[2]]<<std::endl;
}

Computer::~Computer() {
    //std::cout<<"computer deleted"<<std::endl;
}