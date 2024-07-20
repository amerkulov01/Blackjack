/**
 * @file startmenu.cpp
 * @brief Implementation of the StartMenu class for the BlackJack Simulator application.
 *
 * This file implements the functionalities of the StartMenu class, providing the UI elements
 * for the game's start menu, including buttons to start the game, add balance to the wallet,
 * view the rulebook, and view the moves chart. It is part of the UI module of the BlackJack Simulator.
 * @author Anthony Martin Pinto, Andrei Le Merkulov
 * @date April 1, 2024
 */

#include "headers/startmenu.h"

#include <QMainWindow>

/**
 * @brief Constructs a StartMenu widget with a given parent and a wallet.
 * @param parent The parent widget of this StartMenu, defaults to nullptr.
 * @param myWallet The wallet object to be used for managing the balance, must not be nullptr.
 */
StartMenu::StartMenu(QWidget *parent, wallet *myWallet) : QWidget(parent), myWallet(myWallet) {
    // setup main layout 
  	QVBoxLayout *layout = new QVBoxLayout(this);
    // Title label
    QLabel *titleLabel = new QLabel("BlackJack Simulator", this);
    titleLabel->setAlignment(Qt::AlignHCenter);
    QFont titleFont("Arial", 20, QFont::Bold);
    titleLabel->setFont(titleFont);
    layout->addWidget(titleLabel);

    // Spacer
    layout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
	// adding wallet label 
    walletLabel = new QLabel(QString("Wallet Balance: $%1").arg(myWallet->getBalance()));
    layout->addWidget(walletLabel);

    // Buttons
    QPushButton *button1 = new QPushButton("Start Game", this);
    QPushButton *button2 = new QPushButton("Add Wallet Balance", this);
    QPushButton *button3 = new QPushButton("Rulebook", this);
    QPushButton *button4 = new QPushButton("Moves Chart", this);

    layout->addWidget(button1);
    layout->addWidget(button2);
    layout->addWidget(button3);
    layout->addWidget(button4);

    // Connect clicked signal of button1 to emit startGameRequested signal
    connect(button1, &QPushButton::clicked, this, &StartMenu::onStartGameClicked);

    // Connect the clicked signal of button2 to a slot that updates the wallet balance
    connect(button2, &QPushButton::clicked, this, &StartMenu::updateBalance);

    // Connect the clicked signal of button3 to a slot that displays the rules of blackjack
    connect(button3, &QPushButton::clicked, this, &StartMenu::showRules);

    // Connect the clicked signal of button4 to a slot that displays the image
    connect(button4, &QPushButton::clicked, this, &StartMenu::showChart);

    // Set layout
    setLayout(layout);

    // Set window properties
    setWindowTitle("BlackJack Simulator");
    setFixedSize(500, 400); // Adjust size as needed
}

/**
 * @brief Updates the wallet balance with an amount specified by the user.
 * 
 * This method prompts the user to enter an amount to add to their wallet balance.
 * If the input is valid, it updates the wallet balance and the displayed balance label.
 */
void StartMenu::updateBalance() {

    bool ok;
    QString addAmountText = QInputDialog::getText(this, "Add Wallet Balance", "Enter the amount to add:", QLineEdit::Normal, QString(), &ok);
    if (ok) {
        // Convert the text input to a double
        double addAmount = addAmountText.toDouble(&ok);
        if (ok) {
            // If conversion is successful, add the amount to the wallet balance
            myWallet->addFunds(addAmount);
            // Update the wallet balance label
            walletLabel->setText("Wallet Balance: $" + QString::number(myWallet->getBalance(), 'f', 2));
        } else {
            // Conversion failed, show an error message
            QMessageBox::critical(this, "Error", "Invalid input. Please enter a valid number.");
        }
    }
}

/**
 * @brief Displays the optimal moves chart in a new window.
 * 
 * This method loads an image representing the optimal moves chart for blackjack
 * and displays it in a QLabel.
 */
void StartMenu::showChart() {
    QPixmap chartPixmap(":/images/moves.png");
    if (chartPixmap.isNull()) {
        qDebug() << "Failed to load image!";
        return;
    }
    QLabel *imageLabel = new QLabel(this);
    imageLabel->setPixmap(chartPixmap);
    imageLabel->setScaledContents(true);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setFixedSize(chartPixmap.size());
    imageLabel->show();
}

/**
 * @brief Signals that the game start has been requested by the user.
 * 
 * This method is connected to the "Start Game" button's clicked signal and emits
 * the startGameRequested signal when the button is clicked.
 */
void StartMenu::onStartGameClicked() {
    emit startGameRequested();
}

/**
 * @brief Displays the blackjack rules in a new window.
 * 
 * This method creates a new window and displays an image with the blackjack rules.
 */
void StartMenu::showRules() {
    // Create a new window to display the rules image
    QMainWindow *rulesWindow = new QMainWindow(this);
    rulesWindow->setWindowTitle("Rulebook");

    // Create a label to display the rules image
    QLabel *rulesImageLabel = new QLabel(rulesWindow);
    QPixmap rulesPixmap(":/images/rules.png"); // Adjust the path as needed
    if (rulesPixmap.isNull()) {
        qDebug() << "Failed to load rules image!";
        return;
    }
    rulesImageLabel->setPixmap(rulesPixmap);
    rulesImageLabel->setScaledContents(true);

    // Set the central widget of the window to the label
    rulesWindow->setCentralWidget(rulesImageLabel);

    // Adjust the size of the window to fit the image
    rulesWindow->resize(rulesPixmap.size());

    // Show the window
    rulesWindow->show();
}


