
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "headers/dealer.h"
#include <iostream>

/**
 * @file dealer.cpp
 * @brief Implementation of the dealer class.
 *
 * Defines the actions and behaviors of the dealer in a card game, including dealing cards,
 * hitting, and evaluating hands.
 *
 * @author Hsiao Yuan Lu
 */


/**
 * @brief Adds a card to the dealer's hand from the deck.
 *
 * This function draws a card from the deck and adds it to the dealer's hand.
 * It checks if the deck is not null before attempting to draw a card.
 */
void dealer::Hit() {
    if (deck != nullptr) { // Check if the deck pointer is not null
        Card newCard = deck->drawCard(); // Use the drawCard() method
        hand.push_back(newCard); // Add the drawn card to the hand
    }
}

/**
 * @brief Deals a card to a player.
 * @param player Reference to the player object receiving the card.
 *
 * This method delegates the card drawing to the player's Hit function.
 */
void dealer::dealCardToPlayer(player& player) {
    if (deck != nullptr) {
        player.Hit(); // Add the card to the player's hand
    }
}



/**
 * @brief Evaluates the dealer's hand and calculates the possible scores.
 * @return A pair containing the minimum and maximum possible scores of the hand.
 *
 * This function calculates the total score of the dealer's hand considering the dual
 * value of aces. It returns both the minimum and maximum scores as a pair.
 */
std::pair<int, int> dealer::CheckHand() {
    int minSum = 0;
    int maxSum = 0;

    for (size_t i = 0; i < hand.size(); ++i) {
        // Access and use 'hand[i]'

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
 * @brief Plays out the dealer's hand according to the game rules.
 * @return A QString describing the outcome of the dealer's play.
 *
 * The dealer will continue to hit until the hand's value is 17 or higher.
 * This method returns a string describing whether the dealer stands or busts.
 */
QString dealer::PlayHand() {
    QString returnString;

    bool shouldHit = true;

    while (shouldHit) {

        int dealerHandMin = CheckHand().first;
        int dealerHandMax = CheckHand().second;

        int handValue = (dealerHandMax <= 21) ? dealerHandMax : dealerHandMin;


        if (handValue < 17) {
            Hit();

        } else {
            shouldHit = false; // The dealer stops hitting
        }
    }

    int finaldealerMin = CheckHand().first;
    int finaldealerMax = CheckHand().second;


    int finalHandValue = (finaldealerMax <= 21) ? finaldealerMax : finaldealerMin;

    if (finalHandValue > 21) {
        return returnString += "Dealer busts with a total of " + QString::number(finalHandValue) + "\n";

    } else {
        return returnString += "Dealer stands with a total of " + QString::number(finalHandValue) + "\n";
    }

}


/**
 * @brief Reveals the dealer's entire hand and calculates the possible scores.
 *
 * This function prints the dealer's hand and shows the potential scores, taking into
 * account the dual value of aces. It handles the logic for aces differently based on
 * the total hand value.
 */
void dealer::revealHand() {

    bool hasAce = false;

    for (size_t i = 0; i < hand.size(); ++i) {
        if (hand[i].isAce()){
            hasAce = true;
        }
    }

    if (hasAce) {
        if (CheckHand().second < 22) {

            std::cout << "Dealer value could be: " << CheckHand().first << " or: " << CheckHand().second<< std::endl;
            for (size_t i = 0; i < hand.size(); ++i) {
                // Access and use 'hand[i]'
                hand[i].PrintCard();
            }
        } else {
            std::cout << "Dealer hand value: " << CheckHand().first << std::endl;
            for (size_t i = 0; i < hand.size(); ++i) {
                // Access and use 'hand[i]'
                hand[i].PrintCard();
            }
        }
    }

    else{
        std::cout << "Your hand value: " << CheckHand().second <<std::endl;
        for (size_t i = 0; i < hand.size(); ++i) {
            // Access and use 'hand[i]'
            hand[i].PrintCard();
        }
    }

}


/**
 * @brief Compares the dealer's hand with a player's hand to determine the outcome.
 * @param p Reference to the player object to compare hands with.
 * @return Integer code representing the game outcome (0 for dealer wins, 1 for player wins, 2 for tie).
 *
 * This function compares the hands of the dealer and a player to decide the winner.
 * It accounts for scenarios like busts and ties.
 */

int dealer::CompareHands(player& p) {
    int dealerHandMin = CheckHand().first;
    int dealerHandMax = CheckHand().second;
    int dealerHand;

    if(dealerHandMin < 22 && dealerHandMax < 22) {
        dealerHand = dealerHandMax;
    }
    else{
        dealerHand = dealerHandMin;
    }


    int playerHandMin = p.CheckHand().first;
    int playerHandMax = p.CheckHand().second;


    int playerHand;

    if(playerHandMin < 22 && playerHandMax < 22) {
        playerHand = playerHandMax;
    }
    else{
        playerHand = playerHandMin;
    }

    std::cout <<std::endl;
    std::cout << "Dealer's hand: " << dealerHand << std::endl;
    std::cout << "Player's hand: " << playerHand << std::endl;

    if ((dealerHand > 21)&&(playerHand < 22)) {

        return 1;

    } else if((dealerHand > 21)&&(playerHand > 21)){
        return 0;

    }   else if (playerHand > 21) {
        ///player busts, dealer wins
        return 0;
    } else if (dealerHand > playerHand) {
        ///dealer wins with higher hand
        return 0;
    } else if (playerHand > dealerHand) {
        ///player wins with higher hand
        return 1;
    } else {
        ///else tie
        return 2;
    }
}



/**
 * @brief Generates a string representation of the dealer's hand.
 * @return A QString representing the hand's value.
 *
 * This method returns a string describing the dealer's hand value, considering the dual
 * value of aces. It uses the best possible score that does not exceed 21.
 */
QString dealer::GetHandString() {
    bool hasAce = false;
    QString handString;

    for (size_t i = 0; i < hand.size(); ++i) {
        if (hand[i].isAce()){
            hasAce = true;
        }
    }

    if (hasAce) {
        if (CheckHand().second < 22) {
            handString += QString::number(CheckHand().second) ;
        }
        else{
            handString +=  QString::number(CheckHand().first) ;
        }
    }
    else{
        handString +=  QString::number(CheckHand().second) ;

    }

    return handString;

}


/**
 * @brief Generates a string representation of one card from the dealer's hand.
 * @return A QString representing the value of one card in the hand.
 *
 * This function is used to show the value of the dealer's second card (usually the hole card)
 * after the initial deal.
 */
QString dealer::GetHandString_oneCard(){
    QString handString;

    int value = hand[1].value;


    if (hand[1].isAce()) {
        handString += "11";

    }
    else{
        handString +=   QString::number(value) ;
    }
    return handString;

}





