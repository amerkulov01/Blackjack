#include "headers/gameui.h"

#include <QPalette>
#include <QVBoxLayout>
#include <QLabel>
#include <iostream>
#include <utility>
#include <QMessageBox>
#include <QString>
#include "headers/cards.h"
/**
 * @file GameUI.cpp
 * @brief Implementation of the GameUI class.
 *
 * This file implements the graphical user interface for the card game, handling user
 * interactions and displaying game state and information.
 *
 * @author Hsiao Yuan Lu, Dingyan Guo, Derick Yuan 
 */



/**
 * @brief Constructor for the GameUI class.
 * @param parent Pointer to the parent widget.
 * @param passedWallet Pointer to the wallet object for managing player funds.
 *
 * Initializes the game user interface, setting up the deck, players, and UI components.
 */
GameUI::GameUI(QWidget *parent, wallet* passedWallet) : QWidget(parent), myWallet(passedWallet) {

    setupUI();
}



GameUI::~GameUI() {}


/**
 * @brief Sets up the UI components of the game.
 *
 * This method initializes and arranges all UI components including the layout,
 * buttons, labels, and other widgets necessary for the game.
 */
void GameUI::setupUI() {
    // setting main layout background
    QVBoxLayout* main_layout = new QVBoxLayout(this);
    set_table_background(); // set table background


    multideck.createAndShuffleDecks();

    QStringList imagePaths;
    int size = 312;
    for (int i = 0; i < size; ++i) {
        imagePaths.append(multideck.allDecks[i].imagePath());
    }


    // creating player and dealer
    dealer = new class dealer(&multideck);

    // setting deal, hit, stand, (double), End Hand buttons
    dealButton = new QPushButton("Deal", this);
    hitButton = new QPushButton("Hit", this);
    standButton = new QPushButton("Stand", this);
    doubleButton = new QPushButton("Double", this);
    endHandButton = new QPushButton("End Hand", this);
    backToMenu = new QPushButton("Stats", this);

    addPlayer1 = new QPushButton("Add player 1", this);
    addPlayer2 = new QPushButton("Add player 2", this);
    addPlayer3 = new QPushButton("Add player 3", this);

    // set button sizes
    dealButton->setFixedSize(100, 40);
    hitButton->setFixedSize(50, 40);
    standButton->setFixedSize(50, 40);
    doubleButton->setFixedSize(60, 40);
    endHandButton->setFixedSize(100, 40);
    backToMenu->setFixedSize(100, 40);

    dealButton->setStyleSheet("QPushButton { border: 2px solid black; background-color: #FF9999; color: black;}");
    hitButton->setStyleSheet("QPushButton { border: 2px solid black; background-color: #FF9999; color: black; }");
    standButton->setStyleSheet("QPushButton { border: 2px solid black; background-color: #90C5EB; color: black; }");
    doubleButton->setStyleSheet("QPushButton { border: 2px solid black; background-color: #58F470; color: black; }");
    endHandButton->setStyleSheet("QPushButton { border: 2px solid black; background-color: #B9B0B0; color: black; }");
    backToMenu->setStyleSheet("QPushButton { border: 2px solid black; background-color: #90C5EB; color: black;}");

    addPlayer1->setStyleSheet("QPushButton { border: 2px solid black; background-color: #BA68C8; color: black;}");
    addPlayer2->setStyleSheet("QPushButton { border: 2px solid black; background-color: #CE93D8; color: black;}");
    addPlayer3->setStyleSheet("QPushButton { border: 2px solid black; background-color: #E1BEE7; color: black;}");


    addPlayer1->setFixedSize(100,40);
    addPlayer2->setFixedSize(100,40);
    addPlayer3->setFixedSize(100,40);

    // Edit button's intial visibility
    hitButton->hide(); // Hide initially
    standButton->hide();
    doubleButton->hide();
    endHandButton->hide();

    connect(dealButton, &QPushButton::clicked, this, &GameUI::onDealClicked);
    connect(endHandButton, &QPushButton::clicked, this, &GameUI::onEndClicked);
    connect(standButton, &QPushButton::clicked, this, &GameUI::onStandClicked);
    connect(doubleButton, &QPushButton::clicked, this, &GameUI::onDoubleClicked);

    connect(addPlayer1, &QPushButton::clicked, this, &GameUI::onAddPlayer1Clicked);
    connect(addPlayer2, &QPushButton::clicked, this, &GameUI::onAddPlayer2Clicked);
    connect(addPlayer3, &QPushButton::clicked, this, &GameUI::onAddPlayer3Clicked);

    buttonsLayout = new QHBoxLayout(); // No longer a local variable

    buttonsLayout->addWidget(dealButton);
    buttonsLayout->addWidget(hitButton);
    buttonsLayout->addWidget(standButton);
    buttonsLayout->addWidget(doubleButton);
    buttonsLayout->addWidget(endHandButton);
    buttonsLayout->addWidget(backToMenu);

    buttonsLayout->addWidget(addPlayer1);
    buttonsLayout->addWidget(addPlayer2);
    buttonsLayout->addWidget(addPlayer3);

    buttonsLayout->setAlignment(Qt::AlignBottom);
    buttonsLayout->setContentsMargins(30, 0, 0, 100); // Left, Top, Right, Bottom margins


    // Show deck and Show remaining cards buttons
    QHBoxLayout *buttonsLayout2 = new QHBoxLayout();
    QPushButton *button5 = new QPushButton("show deck", this);
    //QPushButton *button6 = new QPushButton("show remaining deck", this);

    button5->setFixedSize(100, 30);
    //button6->setFixedSize(150, 30);
    buttonsLayout2->addWidget(button5);
    //buttonsLayout2->addWidget(button6);
    buttonsLayout2->setAlignment(Qt::AlignRight);

    // back button to menu // cant get this to work !!!
    connect(backToMenu, &QPushButton::clicked, this, &GameUI::onBackClicked);
    // connect show deck button
    connect(button5, &QPushButton::clicked, this, &GameUI::onShowDeckClicked);
    // connect
    //connect(button6, &QPushButton::clicked, this, &GameUI::onShowDeckClicked);
    //button6->move(700, 100);
    connect(hitButton, &QPushButton::clicked, this, &GameUI::onHitClicked);


    // Player and Dealer hand points
    QVBoxLayout *buttonsLayout3 = new QVBoxLayout();
    QVBoxLayout *buttonsLayout4 = new QVBoxLayout();

    playerHandValue1 = new QLabel(this);
    playerHandValue1->move(100,400);
    playerHandValue1->setMinimumWidth(750); // Set a minimum width to accommodate the text
    buttonsLayout4->addWidget(playerHandValue1);
    buttonsLayout4->setAlignment(Qt::AlignLeft);

    dealerHandValue = new QLabel(this);
    dealerHandValue->move(50,200);
    dealerHandValue->setMinimumWidth(200); // Set a minimum width to accommodate the text

    QString dealerHandString = dealer->GetHandString(); // Get the hand string from player1
    dealerHandValue->setText(dealerHandString);

    buttonsLayout3->addWidget(dealerHandValue);
    buttonsLayout3->setAlignment(Qt::AlignRight);

    main_layout->addLayout(buttonsLayout3);
    QSpacerItem* verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    main_layout->addSpacerItem(verticalSpacer);
    main_layout->addLayout(buttonsLayout);
    main_layout->addLayout(buttonsLayout2);


    // total wallet balance setup
    walletLabel = new QLabel(QString("Wallet Balance: $%2").arg(myWallet->getBalance()));
    walletLabel->setStyleSheet("QLabel { color : white; }");

    main_layout->addWidget(walletLabel);
    walletLabel->move(50, 250);

    // setting bet window for bet input
    enter_bet_amount_label = new QLabel("Bet Amount: ", this);
    betAmount = new QLineEdit(this);
    betAmount->setText("1.00");
    betAmount->setFixedSize(75,40);

    QSpacerItem *horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    buttonsLayout->addSpacerItem(horizontalSpacer);
    buttonsLayout->addWidget(enter_bet_amount_label);
    buttonsLayout->addWidget(betAmount);

    // set bet slider
    bet_amount_slider = new QSlider(Qt::Horizontal, this);
    // int sliderMaxValue = myWallet.getBalance();
    bet_amount_slider->setRange(1, myWallet->getBalance());
    bet_amount_slider->setValue(10);
    connect(bet_amount_slider, &QSlider::valueChanged, this, &GameUI::update_bet_amount);
    buttonsLayout->addWidget(bet_amount_slider);

    setLayout(main_layout);



}


/**
 * @brief Handles resizing of the game window.
 * @param event Pointer to the resize event.
 *
 * Ensures the background image scales correctly with the window size.
 */
void GameUI::resizeEvent(QResizeEvent *event) {
    if (background) {
        background->resize(event->size());
    }
    QWidget::resizeEvent(event);
}

/**
 * @brief Sets the background image of the game table.
 *
 * Configures the background of the game window with a specified image.
 */
void GameUI::set_table_background() {
    background = new QLabel(this);
    background->setPixmap(QPixmap(":/images/background.png")); // Adjust path as necessary
    background->setScaledContents(true); // Ensure the image covers the whole label
    background->resize(this->size()); // Match the size of GameUI

}

/**
 * @brief Starts a new game round by dealing cards to players.
 *
 * This slot is triggered by clicking the Deal button. It manages the beginning of a new game
 * round, including dealing cards and adjusting the wallet according to the bet amount.
 */
void GameUI::onDealClicked() {
    setupComplete = false;
    if (playerNum == 0){
        return;
    }
    // subtract bet amount from wallet on deal clicked
    bool ok;
    double doubleBetAmount = betAmount->text().toDouble(&ok);
    if (ok && doubleBetAmount>0) {

        bool place_bet_success = myWallet->placeBet(doubleBetAmount * playerNum);
        if (place_bet_success) {
            updateWalletBalanceLabel();
            // display or hide buttons on screen
            showPlayerActionButtons();
            dealButton->hide();
            enter_bet_amount_label->hide();
            betAmount->hide();
            bet_amount_slider->hide();
            backToMenu->hide();

            addPlayer1->hide();
            addPlayer2->hide();
            addPlayer3->hide();

            // start game - initial dealing of cards
            dealerSetup();
            for (int i = 0; i < playerNum; i++){
                onHitClicked();
                onHitClicked();
                currentPlayingHand ++;
            }
            displayPlayerHandsValue();
            playerHandValue1->show();
            currentPlayingHand = 0;
        } else {
            QMessageBox::warning(this, "Invalid Bet", "Please enter a valid bet amount.");
        }
    }

    setupComplete = true;
    checkBJ();
    if (skiphand == 0){
        buttonsLayout->setContentsMargins(300, 0, 0, 100); // Left, Top, Right, Bottom margins
        std::cout << "        NEWEST CHECK: this is used = "<< currentPlayingHand << std::endl;

        currentPlayingHand ++;
        skiphand = -1;
    }
}


/**
 * @brief Concludes the current game round.
 *
 * This slot is triggered by clicking the End Hand button. It finalizes the round,
 * comparing hands between the dealer and players to determine the outcome.
 */
void GameUI::onEndClicked() {

    // manipulating buttons
    hitButton->hide();
    standButton->hide();
    doubleButton->hide();
    endHandButton->hide();
    dealButton->show();
    enter_bet_amount_label->show();
    betAmount->show();
    bet_amount_slider->show();
    backToMenu->show();

    addPlayer1->show();
    addPlayer2->show();
    addPlayer3->show();

    addPlayer1->setEnabled(true);
    addPlayer2->setEnabled(true);
    addPlayer3->setEnabled(true);

    addPlayer1->setText("Add Player 1");
    addPlayer2->setText("Add Player 2");
    addPlayer3->setText("Add Player 2");

    // updating wallet balance based on win, lose, tie

    for (player* p : players) {
        int result = dealer->CompareHands(*p);
        if (result == 0) {/**updateWalletBalanceLabel();**/} // if dealer wins wallet already subtracted, do nothing
        else if (result == 1 ){ // if player wins hand
            bool ok;
            double initialBetAmount = betAmount->text().toDouble(&ok);
            if (ok && initialBetAmount>0) {
                double winnings = p->isDoubled ? 4 * initialBetAmount : 2 * initialBetAmount;

                    myWallet->addFunds(winnings);
                updateWalletBalanceLabel();
            }
        }
        else{ // tie game
            bool ok;
            double initialBetAmount = betAmount->text().toDouble(&ok);
            if (ok && initialBetAmount>0) {
                double winnings = p->isDoubled ? 2 * initialBetAmount : 1 * initialBetAmount;

                    myWallet->addFunds(winnings);
                updateWalletBalanceLabel();
            }
        }
    }

    updateSliderRange();
    resetPlayerHand();
    resetDealerHand();

    playerHandValue1->hide();
    currentPlayingHand = 0;

    buttonsLayout->setContentsMargins(30, 0, 0, 100); // Left, Top, Right, Bottom margins

    isDoubleDown = false;

}

/**
 * @brief Updates the bet amount based on the slider's value.
 * @param value The new bet amount selected by the slider.
 *
 * Synchronizes the bet amount input field with the value selected using the bet amount slider.
 */
void GameUI::update_bet_amount(int value) {
    this->betAmount->setText(QString::number(value, 'f', 2));
}


/**
 * @brief Shows the deck's current state in a new dialog.
 *
 * This slot is triggered by clicking the Show Deck button. It displays all cards currently
 * in the deck in a scrollable dialog window.
 */
void GameUI::updateSliderRange() {
    int sliderMaxValue = myWallet->getBalance(); // Get the new maximum value based on wallet balance
    bet_amount_slider->setMaximum(sliderMaxValue); // Set the new maximum value for the slider
}

/**
 * @brief Adds the first player to the game.
 *
 * This slot is triggered by clicking the Add Player 1 button. It creates a new player
 * instance and updates the UI to reflect the addition.
 */
void GameUI::updateWalletBalanceLabel() {
    walletLabel->setText(QString("Wallet Balance: $%2").arg(myWallet->getBalance()));
    walletLabel->setStyleSheet("QLabel { color : white; }");


}




/**
 * @brief Responds to the Hit button click by the current player.
 *
 * This method deals an additional card to the current player's hand and updates
 * the UI accordingly. It also checks for conditions such as busts or blackjack
 * and ends the hand if necessary.
 */
void GameUI::onHitClicked(){

    player *currentPlayer = players[currentPlayingHand];
    currentPlayer->Hit();
    int position_index = currentPlayingHand;
    int xPosition = 50 + position_index * 320; // Initial x-coordinate for the first image

    if(currentPlayer->hand.size()== 3){
        doubleButton->hide();
    }

    ///loop through players and display their card images
    for (unsigned long long i = 0; i < currentPlayer->hand.size(); i++){
        QString imagePath = currentPlayer->hand[i].generateImagePath(); // Get the image path for the current card
        QPixmap pixmap(imagePath);
        QSize newSize  = pixmap.size()*2;
        QPixmap scaledPixmap = pixmap.scaled(newSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        // Create a QLabel with enough space to display the entire image
        QLabel *imageLabel = new QLabel(this);
        imageLabel->setPixmap(scaledPixmap);
        imageLabel->setFixedSize(scaledPixmap.size());
        imageLabel->move(xPosition, 250);
        xPosition += 50;
        imageLabel->show();
        playerHandImages.append(imageLabel);
    }
    displayPlayerHandsValue();


    QString handString = currentPlayer->GetHandString();
    std::cout << "Current playerNum = "<< playerNum<< std::endl;
    std::cout << "Current playing hand:  = "<< currentPlayingHand << std::endl;


    if(setupComplete == true){
        // if player busts
        if (currentPlayer->CheckHand().first>21){
            QMessageBox::information(this, "BUST", "Your hand exceeds 21. You lose.\n\nYour Hand: " + handString);
            endHand();
        }
        else if (((currentPlayer->CheckHand().first == 11)&&(player1->CheckHand().second==21))&&(dealer->CheckHand().second != 21)){
            QMessageBox::information(this, "WIN", "BLACK JACK!. You win!");
            endHand();
        }
        // if Player wins hand
        else if ((currentPlayer->CheckHand().first == 21)||(player1->CheckHand().second==21)){
            QMessageBox::information(this, "WIN", "Congradulation. You win!");
            endHand();
        }
    }
}

/**
 * @brief Ends the player's turn without drawing a card.
 *
 * This slot is connected to the Stand button. It ends the current player's turn
 * and proceeds to the next actions, like revealing the dealer's hand or ending the hand.
 */
void GameUI::onStandClicked(){
    endHand();
}


/**
 * @brief Doubles the player's bet and draws one final card.
 *
 * This method is triggered by the Double button. It doubles the current player's bet,
 * draws one additional card, and then ends the player's turn.
 */
void GameUI::onDoubleClicked() {

    player *currentPlayer = players[currentPlayingHand];
    currentPlayer->isDoubled = true;


    bool ok;
    double doubleBetAmount = betAmount->text().toDouble(&ok);
    if (ok && doubleBetAmount>0) {
        bool place_bet_success = myWallet->placeBet(doubleBetAmount);
        if (place_bet_success) {


            updateWalletBalanceLabel(); // update balance with subtracted double bet
            int debug = currentPlayingHand;
            onHitClicked(); // deal player 1 additional card
            std::cout << "          Debug: "<< debug<< "    CPH: "<< currentPlayingHand << std::endl;
            if (debug != currentPlayingHand){
                return;
            }
            else{
                endHand();
            }
        } else {
            QMessageBox::warning(this, "Invalid Bet", "Please enter a valid bet amount.");
        }
    }
}

/**
 * @brief Displays the result of the current hand.
 *
 * Compares the hands of the dealer and all players to determine and display the result
 * of the current hand, including wins, losses, and ties. Updates the game records accordingly.
 */
void GameUI::displayResult(){

    QString message;
    QString gameResult;
    \
        int result;
    gameResult += QString("Dealer value: %1: \n\n").arg(dealer->GetHandString());

    for (int i = 0; i< playerNum; i++){

        result = dealer->CompareHands(*players[i]);

        if (result == 0){
            message += QString("Hand %1: Lose\n").arg(i + 1);
            gameResult += QString("     Hand value: %1: Lose\n").arg(players[i]->GetHandString());

        }
        else if (result == 1 ){
            message += QString("Hand %1: Win\n").arg(i + 1);
            gameResult += QString("     Hand value: %1: Win\n").arg(players[i]->GetHandString());

        }
        else{
            message += QString("Hand %1: Tie\n").arg(i + 1);
            gameResult += QString("     Hand value: %1: Tie\n").arg(players[i]->GetHandString());

        }

    }


    gameResult += QString("     Wallet Balance: $%2\n").arg(myWallet->getBalance());

    ///records will be shown in stats page to show past results
    records.prepend( gameResult + "\n");


    QMessageBox::information(this, "Result", message);
}


/**
 * @brief Reveals all of the dealer's cards at the end of a hand.
 *
 * This function is called to display all of the dealer's cards on the UI,
 * including cards that were initially dealt face down.
 */
void GameUI::dealerReveal(){
    int xPosition = 350; // Initial x-coordinate for the first image
    for (unsigned long long i = 2; i < dealer->hand.size(); i++){
        delay(100);
        QString imagePath = dealer->hand[i].generateImagePath(); // Get the image path for the current card

        QPixmap pixmap(imagePath);
        QSize newSize  = pixmap.size()*2;
        QPixmap scaledPixmap = pixmap.scaled(newSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        // Create a QLabel with enough space to display the entire image
        QLabel *imageLabel = new QLabel(this);
        imageLabel->setPixmap(scaledPixmap);
        imageLabel->setFixedSize(scaledPixmap.size());

        imageLabel->move(xPosition, 25);
        xPosition += 50;

        imageLabel->show();
        dealerHandImages.append(imageLabel);
    }

    QString handString = dealer->GetHandString(); // Get the hand string from player1
    dealerHandValue->setText(handString); // Update the text of the QLabel

}

/**
 * @brief Implements a delay within the UI thread.
 * @param milliseconds The duration of the delay in milliseconds.
 *
 * This is mainly used to mimic the ideal of dealer hitting new cards.
 */
void GameUI::delay(int milliseconds) {
    QTimer timer;
    QEventLoop loop;
    connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    timer.start(milliseconds);
    loop.exec();
}

/**
 * @brief Sets up the initial dealer hand at the start of a game.
 *
 * Draws two cards for the dealer, displaying one face up and one face down, and
 * updates the UI to reflect the dealer's initial hand.
 */
void GameUI::dealerSetup(){
    dealer->Hit();
    dealer->Hit();
    showDealerCard();
    QString HandValue = dealer->GetHandString_oneCard(); // Get the hand string from player1
    dealerHandValue->setText(HandValue);

}

/**
 * @brief Displays the dealer's first card face up and the second card face down.
 *
 * At the start of the game, this function is called to show one of the dealer's
 * cards face up and the other face down, indicating that it's hidden from the player.
 */
void GameUI::showDealerCard(){
    //Face Down Card
    QString imagePath2 = ":/images/backsideOfACard.png"; // Path for the second card

    QPixmap pixmap2(imagePath2);
    QSize newSize2 = pixmap2.size()*1.46;
    QPixmap scaledPixmap2 = pixmap2.scaled(newSize2, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QLabel *imageLabel2 = new QLabel(this);
    imageLabel2->setPixmap(scaledPixmap2);
    imageLabel2->setFixedSize(scaledPixmap2.size());
    imageLabel2->move(250, 25);
    imageLabel2->show();
    dealerHandImages.append(imageLabel2);

    //Face up Card
    QString imagePath = dealer->hand[1].generateImagePath(); // Get the image path for the current card

    QPixmap pixmap(imagePath);
    QSize newSize  = pixmap.size()*2;
    QPixmap scaledPixmap = pixmap.scaled(newSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QLabel *imageLabel = new QLabel(this);
    imageLabel->setPixmap(scaledPixmap);
    imageLabel->setFixedSize(scaledPixmap.size());
    imageLabel->move(300, 25);
    imageLabel->show();
    dealerHandImages.append(imageLabel);



    QString handString = dealer->GetHandString(); // Get the hand string from player1
    dealerHandValue->setText(handString); // Update the text of the QLabel

}



/**
 * @brief Reveals the dealer's face down card.
 *
 * This function is called to flip the dealer's face down card, revealing its value
 * to the player at the appropriate time.
 */
void GameUI::showFaceDownCard(){
    QString imagePath = dealer->hand[0].generateImagePath(); // Get the image path for the current card

    QPixmap pixmap(imagePath);
    QSize newSize  = pixmap.size()*2;
    QPixmap scaledPixmap = pixmap.scaled(newSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QLabel *imageLabel = new QLabel(this);
    imageLabel->setPixmap(scaledPixmap);
    imageLabel->setFixedSize(scaledPixmap.size());
    imageLabel->move(250, 25);
    imageLabel->show();
    dealerHandImages.append(imageLabel);

    int xPosition = 300; // Initial x-coordinate for the first image


    QString imagePath2 = dealer->hand[1].generateImagePath(); // Get the image path for the current card

    QPixmap pixmap2(imagePath2);
    QSize newSize2  = pixmap2.size()*2;
    QPixmap scaledPixmap2 = pixmap2.scaled(newSize2, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Create a QLabel with enough space to display the entire image
    QLabel *imageLabel2 = new QLabel(this);
    imageLabel2->setPixmap(scaledPixmap2);
    imageLabel2->setFixedSize(scaledPixmap2.size());

    imageLabel2->move(xPosition, 25);

    imageLabel2->show();
    dealerHandImages.append(imageLabel2);

    QString handString = dealer->GetHandString(); // Get the hand string from player1
    dealerHandValue->setText(handString); // Update the text of the QLabel

}


/**
 * @brief Resets the player's hand and UI elements related to the player's cards.
 *
 * Clears the player's hand and removes the associated card images from the UI, preparing
 * for the next hand or game.
 */
void GameUI::resetPlayerHand() {
    // Remove image labels
    for (QLabel *imageLabel : playerHandImages) {
        delete imageLabel; // Delete the QLabel
    }
    playerHandImages.clear(); // Clear the list of image labels


    player *currentPlayer;

    for (int i = 0; i < playerNum; i++){

        currentPlayer = players[i];
        currentPlayer->hand.clear();
        currentPlayer->isDoubled = false;

    }

    //clear player list
    players.clear();

    playerNum = 0;
    skiphand = -1;

    // Clear the text of playerHandValue1
    playerHandValue1->clear();

}



/**
 * @brief Resets the dealer's hand and UI elements related to the dealer's cards.
 *
 * Clears the dealer's hand and removes the associated card images from the UI, preparing
 * for the next hand or game.
 */
void GameUI::resetDealerHand() {
    // Remove image labels
    for (QLabel *imageLabel : dealerHandImages) {
        delete imageLabel; // Delete the QLabel
    }
    dealerHandImages.clear(); // Clear the list of image labels

    dealer->hand.clear();

    // Clear the text of dealer
    dealerHandValue->clear();
    currentPlayingHand = 0;
}



/**
 * @brief Shows the deck's current state in a new dialog.
 *
 * When the Show Deck button is clicked, this method displays a dialog with all cards
 * currently in the deck, allowing players to view the deck's composition.
 */
void GameUI::onShowDeckClicked() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Deck Contents");

    // Use QScrollArea to handle more cards
    QScrollArea *scrollArea = new QScrollArea(dialog);
    QWidget *container = new QWidget();
    QGridLayout *layout = new QGridLayout(container);

    int cardsPerRow = 13;

    //loop through deck
    for (unsigned long long i = 0; i < (312- multideck.drawnCards.size()); ++i) {
        QString imagePath = multideck.allDecks[i].imagePath(); // Get the image path
        QLabel *cardLabel = new QLabel;
        QPixmap pixmap(imagePath);
        cardLabel->setPixmap(pixmap.scaled(60, 100, Qt::KeepAspectRatio)); // Resize image
        layout->addWidget(cardLabel, i / cardsPerRow, i % cardsPerRow); // Add to grid
    }

    // Setting up the scroll area
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(container);

    QVBoxLayout *mainLayout = new QVBoxLayout(dialog);
    mainLayout->addWidget(scrollArea);

    QPushButton *closeButton = new QPushButton("Close");
    mainLayout->addWidget(closeButton);
    connect(closeButton, &QPushButton::clicked, dialog, &QDialog::accept);

    dialog->setLayout(mainLayout);
    dialog->resize(930, 600); // Adjust size as needed
    dialog->exec(); // Show the dialog modally
}


/**
 * @brief Adds the first player to the game.
 *
 * When the Add Player 1 button is clicked, this method creates a new player instance
 * and updates the UI and internal game state to include the new player.
 */
void GameUI::onAddPlayer1Clicked(){

    player1 = new class player(&multideck);
    players.append(player1);

    playerNum++;
    addPlayer1->setText("+");
    addPlayer1->setEnabled(false);

}

/**
 * @brief Adds the second player to the game.
 *
 * When the Add Player 2 button is clicked, this method creates a new player instance
 * and updates the UI and internal game state to include the new player.
 */
void GameUI::onAddPlayer2Clicked(){

    player2 = new class player(&multideck);
    players.append(player2);

    playerNum++;
    addPlayer2->setText("+");
    addPlayer2->setEnabled(false);

}

/**
 * @brief Adds the third player to the game.
 *
 * When the Add Player 3 button is clicked, this method creates a new player instance
 * and updates the UI and internal game state to include the new player.
 */
void GameUI::onAddPlayer3Clicked(){
    player3 = new class player(&multideck);
    players.append(player3);

    playerNum++;
    addPlayer3->setText("+");
    addPlayer3->setEnabled(false);
}


/**
 * @brief Displays or hides player action buttons based on game state.
 *
 * This method updates the visibility of action buttons like Hit, Stand, and Double,
 * depending on the current state of the game and which actions are valid.
 */
void GameUI::showPlayerActionButtons(){


    if (playerNum >= 1){
        hitButton->show();
        standButton->show();
        doubleButton->show();
        endHandButton->show();
    }

}

/**
 * @brief Hides player action buttons, typically when a hand ends or it's not the player's turn.
 */
void GameUI::hidePlayerActionButtons(){
    hitButton->hide();
    standButton->hide();
    doubleButton->hide();

}


/**
 * @brief Updates and displays the current hand values for all players.
 *
 * Concatenates the hand values of all players into a single string and updates the
 * playerHandValue1 QLabel to display these values. This allows players to see the total
 * value of their hands during the game.
 */
void GameUI::displayPlayerHandsValue(){

    QString resultString;
    QString singleHandValue;

    singleHandValue = players[0]->GetHandString();
    resultString += "" + singleHandValue;

    for (int i = 1; i < playerNum; i++){
        singleHandValue = players[i]->GetHandString();
        resultString += "                                                                                           " + singleHandValue;
    }

    playerHandValue1->setText(resultString);

}

/**
 * @brief Checks for a blackjack at the start of a hand.
 *
 * Iterates through each player's hand to check if they have blackjack (a hand value of 21).
 * If a player has blackjack, their hand is marked to skip further actions for this round.
 */
void GameUI::checkBJ(){

    for (int i = 0; i < players.size(); i++){
        if (players[i]->CheckHand().second == 21){
            skiphand = i;
            std::cout << "        NEWEST CHECK: this is used in checkBJ = "<< currentPlayingHand << std::endl;

        }
    }
}

/**
 * @brief Ends the current player's turn and proceeds to the next actions.
 *
 * Increments the currentPlayingHand counter to move to the next player or end the hand if
 * all players have completed their turns. Also manages the layout margins for displaying
 * player hands and controls the visibility of action buttons based on the game state.
 */
void GameUI::endHand(){

    //std::cout << "              !!!!DEBUG CHECK: double down bool= "<< isDoubleDown << std::endl;


    isDoubleDown = false;

    currentPlayingHand ++;
    std::cout << "        DEBUG CHECK: Current playing hand = "<< currentPlayingHand << std::endl;
    std::cout << "              DEBUG CHECK: skiphand value = "<< skiphand << std::endl;

    doubleButton->show();



    if ((currentPlayingHand == 0)&&(skiphand != 0)){
        buttonsLayout->setContentsMargins(30, 0, 0, 100);
    }
    else if ((currentPlayingHand == 1)&&(skiphand != 1)){
        buttonsLayout->setContentsMargins(300, 0, 0, 100);
    }
    else if(skiphand == 1){
        buttonsLayout->setContentsMargins(600, 0, 0, 100);
        currentPlayingHand ++;
        skiphand = -1;
    }
    else if ((currentPlayingHand == 2)&&(skiphand != 2)){
        buttonsLayout->setContentsMargins(600, 0, 0, 100);
    }
    else if(skiphand == 2){
        hidePlayerActionButtons();
        currentPlayingHand ++;
    }
    else{
        hidePlayerActionButtons();
    }

    if (currentPlayingHand == playerNum){
        showFaceDownCard();
        dealer->PlayHand();
        dealerReveal(); // Second reveal after dealer plays hand
        displayResult();

        onEndClicked();
    }


}


// TEST => Goes to Stats Menu
void GameUI::onBackClicked() {
    // Assuming multideck is a member variable of GameUI and properly initialized
    cards *cardsDialog = new cards(this, multideck, this); // Adjusted for the new constructor
    cardsDialog->setAttribute(Qt::WA_DeleteOnClose); // Ensure dialog is deleted when closed
    cardsDialog->exec(); // Show as a modal dialog
    // If you want the dialog to be modeless, you would use cardsDialog->show();
}




