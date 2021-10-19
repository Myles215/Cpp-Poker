#include<iostream>
#include"Player.h"
#include"Computer.h"
#include"Human.h"
#include<vector>

void showTable(int table[], int cardNumber, std::string suit[], std::string face[]) {
    //Display face and suit of cards on table
    std::cout<<"The table:"<<std::endl;


    for (int i=0;i<cardNumber;i++) {
        std::cout<<face[table[i*2+1]]<<" of "<<suit[table[i*2]]<<std::endl;
    }
}

int placeCard(int deckCards, int cards[]) {
    int pick1 = rand();
    pick1 = pick1%(deckCards);
    int choice = cards[pick1];
    cards[pick1] = cards[deckCards-1]; 
    cards[deckCards-1] = 0;
    return choice;
}

void lineBreak() {
    std::cout<<"\n"<<"\n"<<std::endl;
}

int main() {
    //initialise array that holds all cards
    int cards[52];

    int money;
    int cardNum = 52;

    for (int i=0;i<52;i++) {
        cards[i] = (i+1);
    }

    //initialise array that holds card suit and face
    std::string suit[4] = {"Diamonds","Hearts","Spades","Clubs"};
    std::string face[13] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};

    int numPlayers;
    int humans;

    std::cout<<"Welcome to Poker, how many players will be participating today? (max 6)"<<std::endl;
    std::cin>>numPlayers;

    //protective coding to limit players
    while (numPlayers>6 || numPlayers<0) {
        std::cout<<"This is an invalid number of players"<<std::endl;
        std::cin>>numPlayers;
    }
    
    std::cout<<"how many human players?"<<std::endl;
    std::cin>>humans;
    //protective coding so input is less than or equal to number of players
    while (humans<0 || humans>numPlayers) {
        std::cout<<"this choice is invalid, try again"<<std::endl;
        std::cin>>humans;
    }

    Human *humanPlayers;
    humanPlayers = new Human[humans];

    Computer *computerPlayers;
    computerPlayers = new Computer[numPlayers-humans];

    //create vector to hold players and add pointers
    std::vector<Player*> players;

    for (int i = 0;i<humans;i++) {
        players.push_back(humanPlayers+i);
    }

    for (int i = 0;i<numPlayers-humans;i++) {
        players.push_back(computerPlayers+i);
    }

    

    std::cout<<"how much money would you like to play with?"<<std::endl;
    std::cin>>money;
    for (int i=0;i<numPlayers;i++) {
        players[i]->addFunds(money);
    }

    std::cout<<players[1]->checkFunds();

    //initialise starting values for the round
    int playersInGame = numPlayers;
    int playersInRound = numPlayers;
    int counter = -1;
    int currentBet = 0;
    int move;
    int playerBet = -1;

    //putting first cards on the table
    int table[10];
    int tableCards[5];
    int tableNum = 0;
    
    
    //the betting 'pot' is initialised at $0
    int pot = 0;
    //winner number used later
    int winner = 0;

    //this is the while loop for the whole game
    //it loops while there is more than 1 player in
    //if a player reaches 0 funds they are out
    while (playersInGame>1) {

        std::cout<<"New Hand"<<"\n"<<std::endl;

        //players pay starting blinds
        std::cout<<"players in pay blinds\n"<<std::endl;
        for (int i = 0;i<numPlayers;i++) {
            if (players[i]->getGameStat()==true) {
                players[i]->addFunds(-(money*0.05));
            }
        }

        //resetting variables before each round
        //first reset deck
        for (int i=0;i<52;i++) {
        cards[i] = (i+1);
        }
        cardNum = 52;
        tableNum = 0;

        //place starting 3 cards on the table
        for (int i=0;i<3;i++) {
        tableCards[i] = placeCard(cardNum, cards);
        //define suit and face on card
        table[i*2] = tableCards[i]%4;
        table[i*2+1] = tableCards[i]%13;
        cardNum--;
        tableNum++;
        }

        //give each player a new hand at the start
        //of each round
        for (int i=0;i<numPlayers;i++) {
        players[i]->getHand(cardNum,cards);
        cardNum = cardNum-2;
        }

        pot = 0;
        playersInRound = playersInGame;
        counter = -1;
        playerBet = -1;
        int pointCheck;

        //Reset round status to true for all players
        for (int i=0;i<numPlayers;i++) {
            players[i]->newRound();
        }
        //this while loop is for individual rounds
        //in each round 5 cards are placed on the table and 
        //players place bets
        //urrentBet = 0;
        //playerBet = -1;

        while (playersInRound > 1) {
        
        //this while loop runs while more than 1 player
        //is in the round and while all players haven't
        //all matched the minimum bet
        currentBet = 0;
        playerBet = -1;
        counter = -1;

        while (playerBet<currentBet && playersInRound>1) {
            counter++;
            /*define whos turn it is in terms of 
            players in the array*/

            //if this player is still in the round, they make their turn
            if (players[counter%numPlayers]->getRoundStat() == true) {
                std::cout<<"ok player "<<counter%numPlayers+1<<" you're up"<<std::endl;
                std::cout<<"you have: $"<<players[counter%numPlayers]->checkFunds()<<std::endl;
                std::cout<<"\n";

                //allow player to see hand before their turn
                std::cout<<"your hand is"<<std::endl;
                players[counter%numPlayers]->checkHand(suit,face);
                lineBreak();

                showTable(table, tableNum, suit, face);
                lineBreak();

                //display current bet for next player
                std::cout<<"current bet is "<<currentBet<<std::endl;

                //player makes their move
                //check if computer player or human
                if (counter%numPlayers<humans) {
                    move = players[counter%numPlayers]->makeMove(currentBet);
                } else {
                    pointCheck = players[counter%numPlayers]->getPoints(tableNum,table);
                    std::cout<<pointCheck<<std::endl;
                    move = players[counter%numPlayers]->makeMove(currentBet);
                    if (move = -1) {
                        std::cout<<"computer player has chosen to fold\n"<<std::endl;
                    } else {
                    std::cout<<"computer player is betting "<<move<<"\n"<<std::endl;
                    }
                }

                if (move==-1) {
                playersInRound--;

                } if (move>=0) {
                    pot = pot+move;
                    lineBreak();
                    std::cout<<"current money in pot:"<<pot<<"\n"<<std::endl;
                    currentBet = move;
                }

                //if all players have played this round check what
                //the next players bet is, if they're all in
                //end this round of betting and if not another round occurs
                //until all bets are equal
                if (counter>=(numPlayers-1)) {
                    if (players[(counter+1)%numPlayers]->isAllIn()==true) {
                        playerBet = currentBet;
                    } else {
                        playerBet = players[(counter+1)%numPlayers]->getBet();
                    }
                }

            //this is for the if statement that checks if players are
            //still in the round, if not, check if they are all in,
            //if they are all in and the next player is also all in
            //end this round
            } else if (players[counter%numPlayers]->isAllIn()==true) {
                std::cout<<"already all in"<<std::endl;
                if (players[(counter+1)%numPlayers]->isAllIn()==true) {
                    playerBet = currentBet;
                }
            }   else {
                std::cout<<"player"<<(counter+1)%numPlayers<<"is out"<<std::endl;
            }
        }

        if (tableNum==5) {
            break;
        } else {
            //place another card on the table after the round of betting
            tableCards[tableNum] = placeCard(cardNum,cards);
            //turn this into a suit and face
            table[tableNum*2] = tableCards[tableNum]%4;
            table[tableNum*2+1] = tableCards[tableNum]%13;
            tableNum++;
        }

        }

        //after 5 cards have been placed on the table
        //and all bets are matched, check for a winner
        winner = 0;
        for (int i=0;i<numPlayers;i++) {
            if (players[i]->getPoints(tableNum,table)>players[winner]->getPoints(tableNum,table)) {
                winner = i;
            }
        }
    std::cout<<"\n"<<"player"<<winner+1<<" wins this round"<<std::endl;
    players[winner]->addFunds(pot);
        //break;
        //if a player is out of money they are out of the game
        for (int i = 0;i<numPlayers;i++) {
            if (players[i]->checkFunds()<1) {
                players[i]->loser();
                playersInGame--;
                std::cout<<"\n"<<"player "<<i+1<<" is out"<<std::endl;
            }
        }

    }

    lineBreak();

    for (int i = 0;i<numPlayers;i++) {
        if (players[i]->getGameStat()==true) {
            std::cout<<"player "<<i+1<<" wins!"<<std::endl;
        }
    }


    delete [] humanPlayers;

    if ((numPlayers-humans)>0) {
        delete [] computerPlayers;
    }
    return 0;
}