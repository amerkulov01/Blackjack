#include <iostream>
#include <cstdlib>
#include <ctime>

#include "headers/player.h"
#include <iostream>
#include <utility>
#include <QMessageBox>


/**
 * @file player.cpp
 * @brief Implementation of the player class for card game operations.
 *
 * Contains the definitions of player actions such as hitting, standing, and evaluating
 * the hand's value. The player can draw cards from the deck, decide to stand, and calculate
 * the total value of their hand considering the dual nature of Aces.
 *
 * @author Hsiao Yuan Lu
 */




/**
 * @brief Draws a card from the deck and adds it to the player's hand.
 *
 * This function checks if the deck pointer is not null before drawing a card.
 * If the deck is valid, it draws a card from the deck and adds it to the player's hand.
 */
void player::Hit() {
    if (deck != nullptr) { // Check if the deck pointer is not null
        Card newCard = deck->drawCard(); // Use the drawCard() method
        hand.push_back(newCard); // Add the drawn card to the hand
    }
}


void player::Stand(){
    //stand so nothing happens
}

/**
 * @brief Calculates the total value of the player's hand.
 *
 * Evaluates the player's hand and returns a pair of integers representing the minimum
 * and maximum values of the hand. This accounts for Aces being either 1 or 11.
 * @return A pair of integers: the first is the minimum value of the hand,
 *         the second is the maximum value considering Aces.
 */
std::pair<int, int> player::CheckHand() {
    int minSum = 0;
    int maxSum = 0;

    for (size_t i = 0; i < hand.size(); ++i) {

        if(hand[i].isAce()){
            minSum += hand[i].value;
            maxSum = minSum + 10;
        }
        else{
            minSum += hand[i].value;
            maxSum += hand[i].value;
        }
    }
    return std::make_pair(minSum, maxSum);
}





/**
 * @brief Generates a string representation of the player's hand value.
 *
 * Constructs and returns a QString summarizing the player's hand value,
 * taking into account the dual value of Aces.
 * @return A QString representing the player's hand value(s).
 */
QString player::GetHandString() {
    bool hasAce = false;
    QString handString;

    for (size_t i = 0; i < hand.size(); ++i) {
        if (hand[i].isAce()){
            hasAce = true;
        }
    }

    if (hasAce) {
        if ((CheckHand().first == 11)&&(CheckHand().second==21)){
            handString += "21";
        }
        else if (CheckHand().second < 22) {
            handString +=QString::number(CheckHand().first) + " or " + QString::number(CheckHand().second) ;
        } else {
            handString +=  QString::number(CheckHand().first) ;
        }
    }
    else{
        handString +=  QString::number(CheckHand().second) ;
    }
    return handString;
}




