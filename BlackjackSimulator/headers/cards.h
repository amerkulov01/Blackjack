#ifndef CARDS_H
#define CARDS_H

#include <QWidget>
#include <QtWidgets>
#include "headers/DeckSetup.h"
#include <QGridLayout>
#include <QApplication>
#include <QLabel>
#include <QPixmap>
#include <QDialog>
#include "headers/gameui.h"

/**
 * @file Cards.h
 * @brief Header file defining the Cards dialog interface.
 *
 * This file contains the declaration of the Cards class, which manages the card-related
 * user interface, including creating decks, drawing cards, and displaying card information.
 *
 * @author Hsiao Yuan Lu
 */



/**
 * @class Cards
 * @brief Dialog interface for managing and displaying card-related actions and information.
 *
 * The Cards class provides functionality to create decks, draw cards from the deck,
 * and display the current deck and drawn cards to the user.
 */
class cards : public QDialog {
    Q_OBJECT
public:


    explicit cards(GameUI* gameUI, MultiDeck& deck, QWidget *parent = nullptr);

    MultiDeck multideck;


    void onDrawCardClicked();
    void onCheckDrawnCardsClicked();

    void showRemainingDeck();

    void displayDrawnCards();

    void showDeck();

    void createDeck();

    void onResultClick();

private slots:

    void onBackButtonClicked();


signals:
    void gameMenuRequested();


private:

    GameUI* gameUIInstance; // Pointer to the GameUI instance



};



#endif // CARDS_H

