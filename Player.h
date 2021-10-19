#ifndef PLAYER_H
#define PLAYER_H

#include<string>

class Player 
{
public:
    Player();
    int hand[2];
    int handCards[4];
    int points;
    int funds = 0;
    int bet = 0;
    bool allIn = false;
    bool roundStatus;
    bool gameStatus;
    virtual int makeMove(int currentBet) = 0;
    void addFunds(int money);
    int checkFunds();
    void getHand(int counter, int cards[]);
    virtual void checkHand(std::string suit[],std::string face[]) = 0;
    int getPoints(int cardCount, int table[]);
    bool getRoundStat();
    bool getGameStat();
    void loser();
    int getBet();
    bool isAllIn();
    void newRound();
    virtual bool isHuman() = 0;
    ~Player();
};

#endif //PLAYER_H