#ifndef DECKSETUP_H
#define DECKSETUP_H

#include <vector>
#include <QString>


/**
 * @file DeckSetup.h
 * @brief Header file defining card game elements.
 *
 * This file contains the enums, structs, and classes necessary to set up and manage a card deck for games.
 * @author Hsiao Yuan Lu
 */



/**
 * @enum CardNames
 * @brief Enumerates all possible card names.
 */
enum CardNames { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };

/**
 * @enum Suits
 * @brief Enumerates card suits.
 */
enum Suits {
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES,
    // Add more suits as needed
};


/**
 * @struct Card
 * @brief Represents a single playing card.
 * A card consists of a name, suit, and numerical value. It includes methods to print and retrieve card details.
 */
struct Card {
    CardNames name;
    Suits suit;
    int value;

    bool isAce(); /// Checks if the card is an Ace.
    void PrintCard();
    void PrintValue();
    void PrintSuit();

    QString generateImagePath() const; /// Generates the image path for the card.

    QString imagePath() const; /// Retrieves the image path for the card.

    // Methods modified to return QString
    QString PrintCard2() const;
    QString PrintValue() const;
    QString PrintSuit() const;
};

/**
 * @class Deck
 * @brief Represents a standard deck of 52 playing cards.
 * This class is responsible for generating and managing a standard deck of playing cards.
 */
class Deck {
public:
    Card arrCards[52];
    void generateDeck();
};

class MultiDeck {
public:
    std::vector<Card> drawnCards;
    Card allDecks[6 * 52];
    void shuffle(Card *decks, int size);
    void createAndShuffleDecks();
    Card drawCard();

    QString printRemainingDeck2();
    QString printDrawnCards2();

};

#endif // DECKSETUP_H

