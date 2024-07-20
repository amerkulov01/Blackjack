

#ifndef GROUP13_PLAYER_H
#define GROUP13_PLAYER_H
#include "headers/DeckSetup.h"
/**
 * @file player.h
 * @brief Declaration of the player class for card game operations.
 *
 * Defines the player class, including actions such as hitting, standing, splitting,
 * and doubling down, as well as managing the player's hand.
 *
 * @author Hsioa Yuan Lu
 */




/**
 * @class player
 * @brief Represents a player in a card game.
 *
 * This class includes functionalities for player actions such as hit, stand, split,
 * and double down. It also manages the player's hand and calculates hand values.
 */
class player {
public:

    bool isDoubled = false; /// Indicates whether the player has doubled down on their bet.

    std::vector<Card>hand;

    MultiDeck* deck; /// Pointer to a MultiDeck instance

    player(MultiDeck* deck) : deck(deck) {} /// Constructor to set the deck

    void Hit();
    void Stand();
    void Split();
    void Double();


    /**
     * @brief Evaluates the player's hand and calculates the total value.
     * @return A pair of integers representing the minimum and maximum values of the hand,
     *         accounting for aces as either 1 or 11.
     */
    std::pair<int, int> CheckHand();
    void AddCardToHand(const Card& specificCard);



    QString PrintHand2();
    QString GetHandString();
};


#endif //GROUP13_PLAYER_H

