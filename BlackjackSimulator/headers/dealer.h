/**
 * @file dealer.h
 * @brief Definition of the dealer class for card game operations.
 *
 * This file declares the dealer class, which is responsible for managing the dealer's actions
 * in a card game. This includes handling the dealer's hand, dealing cards to players, and
 * determining the outcome of the game.
 *
 * @author Hsiao Yuan Lu
 */


#ifndef GROUP13_DEALER_H
#define GROUP13_DEALER_H
#include "headers/DeckSetup.h"
#include "headers/player.h"





/**
 * @class dealer
 * @brief Manages the dealer's actions in a card game.
 *
 * The dealer class is responsible for managing the dealer's hand and actions such as hitting,
 * revealing the hand, dealing cards to players, and determining the outcome of hands in comparison
 * to the players'.
 */
class dealer {

public:

    std::vector<Card>hand;


    MultiDeck* deck; // Pointer to a MultiDeck instance
    dealer(MultiDeck* deck) : deck(deck) {}

    void Hit();
    void revealHand();
    void dealCardToPlayer(player& player);


    std::pair<int, int> CheckHand();

    QString PlayHand();
    int CompareHands(player& p);
    QString GetHandString();
    QString GetHandString_oneCard();


};


#endif //GROUP13_DEALER_H

