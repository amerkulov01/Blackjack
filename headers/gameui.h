#ifndef GAMEUI_H
#define GAMEUI_H

#include "headers/wallet.h"
#include "headers/DeckSetup.h"
#include "headers/player.h"
#include "headers/dealer.h"
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QVector>
#include <QTextBrowser>
#include <QLineEdit>
#include <QSlider>
#include <QPixmap>
#include <QResizeEvent>
#include <QApplication>
#include <QGridLayout>
#include <QtWidgets>
#include <QTimer>


/**
 * @file GameUI.h
 * @brief Header file for the GameUI class, defining the user interface for the card game.
 *
 * The GameUI class is responsible for initializing and managing the graphical user interface
 * components of the card game, handling user interactions, and displaying game information.
 * It integrates game logic with UI elements for a seamless gaming experience.
 *
 * @author Hsiao Yuan Lu, Dingyan Guo, Derick Yuan 
 */



/**
 * @class GameUI
 * @brief Manages the main game window and interactions for the card game.
 *
 * GameUI sets up and manages all UI components necessary for playing the game,
 * including buttons, labels, and other widgets to interact with the game logic,
 * display the game state, and respond to user inputs.
 */
class GameUI : public QWidget {
    Q_OBJECT

public:
    explicit GameUI(QWidget *parent = nullptr, wallet* passedWalled = nullptr);
    ~GameUI();

    void setupUI();

    QString records = "";

    MultiDeck multideck;

    // void clearCardDisplays();

private:

    //cards *cardsInstance;


    bool setupComplete;

    int skiphand = -1; /// Used to skip a hand if necessary.

    QHBoxLayout *buttonsLayout;


    QList<QLabel*> playerHandImages;

    QList<QLabel*> dealerHandImages;

    player *player1;
    player *player2;
    player *player3;

    dealer *dealer;

    QList<player*> players; /// List of player instances. Used to access player info

    int playerNum = 0;

    int currentPlayingHand = 0;

    int setupNum = 0;


    QLabel *background;

    QVector<QPushButton*> player_buttons;
    QPushButton *dealButton;
    QPushButton *hitButton;
    QPushButton *standButton;
    QPushButton *doubleButton;


    QPushButton *endHandButton;
    QPushButton *backToMenu;


    QPushButton *addPlayer1;
    QPushButton *addPlayer2;
    QPushButton *addPlayer3;


    QLabel *enter_bet_amount_label;
    QLineEdit *betAmount;
    QSlider *bet_amount_slider;

    wallet *myWallet;
    QLabel *walletLabel;
    QTextBrowser* wallet_status;
    QLabel *playerHandValue1;


    QLabel *dealerHandValue;

    Deck *myDeck;
    MultiDeck *myMultiDeck;

    void set_table_background();
    void updateSliderRange();
    void updateWalletBalanceLabel();

    bool isDoubleDown = false;

private slots:

    void onDealClicked();
    void onEndClicked();

    void update_bet_amount(int value);

    void onBackClicked();
    void onDoubleClicked();

    void onShowDeckClicked();
    void onHitClicked();
    void resetPlayerHand();
    void showDealerCard();
    void dealerSetup();
    void resetDealerHand();
    void onStandClicked();
    void dealerReveal();
    void displayResult();
    void showFaceDownCard();
    void delay(int milliseconds);


    void onAddPlayer1Clicked();
    void onAddPlayer2Clicked();
    void onAddPlayer3Clicked();

    void showPlayerActionButtons();
    void hidePlayerActionButtons();

    void displayPlayerHandsValue();

    void checkBJ();

    void endHand();



signals:
    void cardsMenuRequested();


protected:
    void resizeEvent(QResizeEvent *event) override;

};

#endif // GAMEUI_H

