#include<iostream>
#include"Human.h"

Human::Human() {
    //std::cout<<"a new human player has been created"<<std::endl;
    gameStatus = true;
    roundStatus = true;
}

int Human::makeMove(int currentBet) {
    /*takes in the current bet of the hand 
    and asks the player for their move, if betting
    they must bet equal to or more than the current bet
    */
    int choice;
    

    if (currentBet==0) {
        std::cout<<"select your move:"<<std::endl;
        std::cout<<"1 for call"<<std::endl;
        std::cout<<"2 for fold"<<std::endl;
        std::cout<<"3 for check"<<std::endl;
        std::cin>>choice;

    } else {
        std::cout<<"select your move:"<<std::endl;
        std::cout<<"1 for raise"<<std::endl;
        std::cout<<"2 for fold"<<std::endl;
        std::cin>>choice;
    }
    
    //protective coding to limit choice to 1,2,3
    while (choice>3 || choice<1) {
        std::cout<<"choice is invalid, retry"<<std::endl;
        std::cin>>choice;
    }

    if (choice==1) {
        std::cout<<"how much would you like to bet?"<<std::endl;
        std::cin>>choice;
        /*if choice is less than current bet it must be increased
        but if the current bet is higher than a players funds they
        must go all in if they choose to play
        */
        if (choice>=funds) {
            std::cout<<"all in!"<<std::endl;
            allIn = true;
            roundStatus = false;
            choice = funds;
        }

        while (choice+bet<currentBet && allIn==false) {
            std::cout<<"this choice is invalid, try again"<<std::endl;
            std::cin>>choice;
        }
        funds = funds - choice;
        bet = bet + choice;
        return choice;
    } else if (choice==2) {
        std::cout<<"you have chosen to fold"<<std::endl;
        roundStatus = 0;
        return -1;
    } else if (choice==3) {
        std::cout<<"you have chosen to check"<<std::endl;
        bet = bet;
        return 0;
    } else { return 0; 
    }
}

bool Human::isHuman() {
    return true;
}

void Human::checkHand(std::string suit[], std::string face[]) {
    
    //output card number and suit
    std::cout<<face[handCards[1]]<<" of "<<suit[handCards[0]]<<std::endl;
    std::cout<<face[handCards[3]]<<" of "<<suit[handCards[2]]<<std::endl;
}


Human::~Human() {
    //std::cout<<"human player has been deleted"<<std::endl;
}

