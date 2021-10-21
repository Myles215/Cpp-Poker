#include "Player.h"
#include<iostream>

//constructor
Player::Player() {
    std::cout<<"a new player has joined!"<<std::endl;
};

//function to add the players funds
//function to add the players funds
void Player::addFunds(int money) {
    funds = funds + money;

    if (money>=0) {
        std::cout<<"$"<<money<<" has been added to account"<<std::endl;
    } else {
        std::cout<<"$"<<-money<<" has been taken from account"<<std::endl;
    }

    if (funds<=0) {
        funds = 0;
        std::cout<<"you are all in"<<std::endl;
        allIn = true;
        roundStatus = false;
    }
    
}

int Player::checkFunds() {
    return funds;
}

void Player::getHand(int counter,int cards[]) {
    
    int pick1 = rand();
    int pick2 = rand();
    /*modulus operater used to find random between
    1 and counter (starts at 51) as a card is 'taken'
    from the deck it is gone, therefore replacing
    it with the last element in the array and changing
    this last element to 0 */
    pick1 = pick1%(counter);
    hand[0] = cards[pick1];
    cards[pick1] = cards[counter-1]; 
    cards[counter-1] = 0;
    counter--;

    pick2 = pick2%(counter);
    hand[1] = cards[pick2];
    cards[pick1] = cards[counter-1];
    cards[counter-1] = 0;
    counter--;

    //Define suit and number on card
    handCards[0] = hand[0]%4;
    handCards[1] = hand[0]%13;

    handCards[2] = hand[1]%4;
    handCards[3] = hand[1]%13;

}


int Player::getPoints(int cardCount, int table[]) {
    /*uses cards on the table and cards in players
    hand to calculate the points of the player
    Not to be used by player but to find winner
    */

    //if a player is out of the round or game, return 0
    if (gameStatus==false || roundStatus==false && allIn==false) {
        return 0;
    }

    int faceMatch1 = 0;
    int faceMatch2 = 0;
    int suitMatch = 0;
    int faceAdd;
    int high;
    int straight = 0;

   if (handCards[0]==handCards[2]) {
       suitMatch++;
   }
   for (int i=0;i<cardCount*2-1;i++) {
       if (handCards[0]==table[i]) {
           suitMatch++;
       }
       if (handCards[2]==table[i]) {
           suitMatch++;
       }
       i++;
   }

   if (handCards[1]==handCards[3]) {
       faceMatch1++;
       faceMatch2++;
   }
   for (int i=1;i<cardCount*2;i++) {
       if (handCards[1]==table[i]) {
           faceMatch1++;
       }
       if (handCards[3]==table[i]) {
           faceMatch2++;
       }
       i++;
   }

   //check for straight

   int *straightCheck = new int[cardCount+2];
    straightCheck[0] = handCards[1];
    straightCheck[1] = handCards[3];

    int j=0;
    for (int i=2;i<cardCount+2;i++) {
        
        straightCheck[i] = table[(j*2)+1];
        j++;
    }

    int temp;

    //selection sort to sort array in ascending order
    for (int i=0;i<cardCount+1;i++) {

        for (int j=i+1;j<cardCount+2;j++) {
            if (straightCheck[j]<straightCheck[i]) {
                temp = straightCheck[j];
                straightCheck[j] = straightCheck[i];
                straightCheck[i] = temp;
            }
        }
    }

        //go through the sorted straight array
        //and check if the previous number is 1 less
        //than the current number to check if numbers
        //ascend by 1
        //if there is a double up of a number do nothing
        for (int j=1;j<cardCount+2;j++) {
            if (straightCheck[j]==(straightCheck[j-1]+1)) {
                straight++;
            } else if (straightCheck[j]==(straightCheck[j-1]+0)) {
                straight = straight;
            } else {
                straight = 0;
            }
        }

    //delete straight check array as it was declared on heap
    delete [] straightCheck;

   //std::cout<<suitMatch<<" "<<faceMatch1<<" "<<faceMatch2<<std::endl;

    //calculate the highest face in players hand
   high = handCards[1];
       if (handCards[3]>handCards[1]) {
           high = handCards[3];
       }

    //using straight check calculated before
    if (straight==4 && suitMatch>4) {
        points = (13*8+high);
        return points;
    } if (straight==4) {
        points = (13*4+high);
        return points;
    }

    /*code to return the number of points 
    a player has */
    if (suitMatch>4) {
       points = (13*5+high);
       return points;
   } else if (faceMatch1==0 && faceMatch2==0) {
       points =  high;
       return points;
   } else if (faceMatch1==1 && faceMatch2==1) {
       points = (13*2);
       return points;
   } else if (faceMatch1==1) {
       points =  (13+handCards[1]);
       return points;
   } else if (faceMatch2==1) {
       points =  (13+handCards[3]);
       return points;
   } else if (faceMatch1==2) {
       points = (13*3+handCards[1]);
       return points;
   } else if (faceMatch2==2) {
       points = (13*3+handCards[3]);
       return points;
   } else if (faceMatch1==1 && faceMatch2==2) {
       points =  (13*6+high);
       return points;
   } else if (faceMatch1==2 && faceMatch2==1) {
       points = (13*6+high);
       return points;
   } else if (faceMatch1==3) {
       points = (13*7+handCards[1]);
       return points;
   } else if (faceMatch2==3) {
       points = (13*7+handCards[3]);
       return points;
   } else {
       points = high;
       return points;
   }
   return points;
   
}

bool Player::getRoundStat() {
    return roundStatus;
}

bool Player::getGameStat() {
    return gameStatus;
}

int Player::getBet() {
    return bet;
}

bool Player::isAllIn() {
    return allIn;
}

void Player::loser() {
    roundStatus = false;
    gameStatus = false;
}

void Player::newRound() {
    if (gameStatus==true) {
        roundStatus = true;
        allIn = false;
        bet = 0;
    } else {
        allIn = false;
    }
}

void Player::resetBet() {
    bet = 0;
}

Player::~Player() {
    //std::cout<<"Player has been deleted"<<std::endl;
}