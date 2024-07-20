#include "headers/DeckSetup.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <QString>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>


/**
 * @file DeckSetup.cpp
 * @brief Implementation for deck setup and management for card games.
 *
 * Contains the implementation of card, deck, and multideck functionalities,
 * such as generating decks, shuffling, and drawing cards.
 *
 * @author Hsiao Yuan Lu
 */




int NUM_DECKS = 6;
int currentSize = 312; // Current size of the combined deck


/// Determines if a card is an Ace.
/// @return True if the card is an Ace, false otherwise.
bool Card::isAce()
{
    return name == ACE;
}


/// Prints the card's value and suit to the standard output.
void Card::PrintCard()
{
    PrintValue();
    std::cout << " of ";
    PrintSuit();
    std::cout << std::endl;
}


/// Gets the card's value as a string.
/// @return A QString representing the card's value.
QString Card::PrintValue() const {
    switch (name) {
    case CardNames::JACK: return "Jack";
    case CardNames::QUEEN: return "Queen";
    case CardNames::KING: return "King";
    case CardNames::ACE: return "Ace";
    default: return QString::number(static_cast<int>(value));
    }
}

/// Gets the card's suit as a string.
/// @return A QString representing the card's suit.
QString Card::PrintSuit() const {
    switch (suit) {
    case Suits::CLUBS: return "Clubs";
    case Suits::DIAMONDS: return "Diamonds";
    case Suits::HEARTS: return "Hearts";
    case Suits::SPADES: return "Spades";
    default: return "Unknown";
    }
}


/// Combines the card's value and suit into a single QString.
/// @return A QString representation of the card.
QString Card::PrintCard2() const {
    return PrintValue() + " of " + PrintSuit();
}

/// Prints the card's value to the standard output.
void Card::PrintValue()
{
    if (name == CardNames::JACK) {
        std::cout << "jack";
    } else if (name == CardNames::QUEEN) {
        std::cout << "queen";
    } else if (name == CardNames::KING) {
        std::cout << "king";
    } else if (name == CardNames::ACE) {
        std::cout << "ACE";
    } else {
        std::cout << static_cast<int>(value);
    }
}

/// Prints the card's suit to the standard output.
void Card::PrintSuit()
{
    if (suit == Suits::CLUBS) {
        std::cout << "clubs";
    } else if (suit == Suits::DIAMONDS) {
        std::cout << "diamonds";
    } else if (suit == Suits::HEARTS) {
        std::cout << "hearts";
    } else if (suit == Suits::SPADES) {
        std::cout << "spades";
    }
}


/**
 * Generates a standard deck of 52 cards.
 */
void Deck::generateDeck()
{
    for (int col = (int) Suits::CLUBS; col <= (int) Suits::SPADES; col++) {
        for (int row = (int) CardNames::ACE; row <= (int) CardNames::KING; row++) {
            Card c;
            c.suit = (Suits) col;
            c.name = (CardNames) row;

            if (c.name == CardNames::JACK) {
                c.value = 10;
            } else if (c.name == CardNames::QUEEN) {
                c.value = 10;
            } else if (c.name == CardNames::KING) {
                c.value = 10;
            } else {
                c.value = (int) c.name + 1;
            }
            int index = (13 * col) + row;
            arrCards[index] = c;

            c.generateImagePath();

        }
    }
}



/**
 * Shuffles the specified deck of cards.
 * @param decks An array of Card objects representing the deck to shuffle.
 * @param size The size of the deck to shuffle.
 */
void MultiDeck::shuffle(Card *decks, int size)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 rng(seed); // Initialize with seed
    for (int i = size - 1; i > 0; i--) {
        std::uniform_int_distribution<int> distribution(0, i);
        int j = distribution(rng);
        std::swap(decks[i], decks[j]);
    }
}

/**
 * Creates and shuffles multiple decks to form a single combined deck.
 */
void MultiDeck::createAndShuffleDecks()
{
    Deck deck;

    int index = 0;
    for (int d = 0; d < NUM_DECKS; ++d) {
        deck.generateDeck(); // Generate a new deck

        for (int card = 0; card < 52; ++card) {
            allDecks[index++] = deck.arrCards[card];
        }
    }


    shuffle(allDecks, 312);
}


/**
 * Draws a card from the MultiDeck.
 * @return The drawn Card object.
 * @throw std::out_of_range if attempting to draw from an empty deck.
 */
Card MultiDeck::drawCard()
{
    if (currentSize == 0) {
        throw std::out_of_range("Attempted to draw from an empty deck.");
    }

    Card drawnCard = allDecks[0]; // Get the first card

    // Shift all other cards one position to the left
    for (int i = 1; i < currentSize; ++i) {
        allDecks[i - 1] = allDecks[i];
    }
    currentSize--;
    drawnCards.push_back(drawnCard);
    return drawnCard;
}


/// Gets a QString representing all cards remaining in the MultiDeck.
/// @return A QString list of all remaining cards.
QString MultiDeck::printRemainingDeck2() {
    QString deckDescription;
    for (int i = 0; i < currentSize; ++i) {
        deckDescription += allDecks[i].PrintCard2() + "\n";
    }
    return deckDescription.trimmed();
}

/// Gets a QString representing all cards that have been drawn from the MultiDeck.
/// @return A QString list of drawn cards.
QString MultiDeck::printDrawnCards2() {
    QString cardsDescription;
    for (size_t i = 0; i < drawnCards.size(); ++i) {
        cardsDescription += drawnCards[i].PrintCard2() + "\n";
    }
    return cardsDescription.trimmed();
}

/// Generates the image path for a card based on its value and suit.
/// @return A QString representing the image path for the card.
QString Card::generateImagePath() const {
    return QString(":/images/%1_of_%2.png")
        .arg(PrintValue().toLower())
        .arg(PrintSuit().toLower());
}


/// Wrapper for generateImagePath to maintain API consistency.
/// @return A QString representing the image path for the card.
QString Card::imagePath() const {
    return generateImagePath();
}

