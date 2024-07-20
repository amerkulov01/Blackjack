#include "headers/cards.h"

/**
 * @file Cards.cpp
 * @brief Implementation of the Cards class.
 *
 * This implementation file provides the functionality to interact with the card deck,
 * including creating a new deck, drawing a card, and displaying the current deck
 * and drawn cards.
 *
 * @author Hsiao Yuan Lu
 */






/**
 * @brief Constructor for the Cards class.
 * @param gameUI Pointer to the GameUI instance.
 * @param deck Reference to a MultiDeck object.
 * @param parent Pointer to the parent widget. Defaults to nullptr.
 *
 * Sets up the UI for the Cards dialog, including layout, buttons, and connections.
 */
cards::cards(GameUI* gameUI, MultiDeck& deck, QWidget *parent) : QDialog(parent), gameUIInstance(gameUI), multideck(deck) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    // Title label
    QLabel *titleLabel = new QLabel("STATS", this);
    titleLabel->setAlignment(Qt::AlignHCenter);
    QFont titleFont("Arial", 20, QFont::Bold);
    titleLabel->setFont(titleFont);
    layout->addWidget(titleLabel);

    layout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));



    QPushButton *button6 = new QPushButton("Previous result", this);
    QPushButton *button7 = new QPushButton("Remaining Cards", this);
    QPushButton *button8 = new QPushButton("Drawn Cards", this);


    layout->addWidget(button6);
    layout->addWidget(button7);
    layout->addWidget(button8);


    connect(button6, &QPushButton::clicked, this, &cards::onResultClick);
    connect(button7, &QPushButton::clicked, this, &cards::showRemainingDeck);
    connect(button8, &QPushButton::clicked, this, &cards::displayDrawnCards);


    // Set layout
    setLayout(layout);

    // Set window properties
    setWindowTitle("BlackJack Simulator");
    setFixedSize(200, 200); // Adjust size as needed




}



/**
 * @brief Displays the entire deck in a new dialog.
 *
 * Opens a dialog window showing all cards in the deck using images.
 */
void cards::showDeck() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Deck Contents");

    // Use QScrollArea to handle more cards
    QScrollArea *scrollArea = new QScrollArea(dialog);
    QWidget *container = new QWidget();
    QGridLayout *layout = new QGridLayout(container);

    int cardsPerRow = 13;
    for (int i = 0; i < 312; ++i) {
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
    dialog->resize(800, 600); // Adjust size as needed
    dialog->exec(); // Show the dialog modally
}



/**
 * @brief Handles the draw card action.
 *
 * Draws a card from the deck, displays its information, and updates the UI.
 */
void cards::onDrawCardClicked() {

    Card drawnCard = multideck.drawCard();
    QString cardDescription = drawnCard.PrintCard2();

    QMessageBox::information(this, "Drawn Card", "A card has been drawn:\n" + cardDescription);

}

/**
 * @brief Displays the drawn cards in a dialog.
 *
 * Shows a dialog window listing all cards that have been drawn so far.
 */
void cards::onCheckDrawnCardsClicked() {

    QMessageBox::information(this, "Drawn Cards", "Check the console for drawn cards.");
}


/**
 * @brief Displays the remaining deck in a dialog.
 *
 * Shows a dialog window with the remaining cards in the deck.
 */
void cards::showRemainingDeck() {

    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Deck Contents");

    // Use QScrollArea to handle more cards
    QScrollArea *scrollArea = new QScrollArea(dialog);
    QWidget *container = new QWidget();
    QGridLayout *layout = new QGridLayout(container);

    int cardsPerRow = 13;
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
    dialog->resize(950, 600); // Adjust size as needed
    dialog->exec(); // Show the dialog modally
}



/**
 * @brief Displays the drawn cards in a dialog.
 *
 * Shows a dialog window listing all cards that have been drawn from the deck.
 */
void cards::displayDrawnCards() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Deck Contents");

    // Use QScrollArea to handle more cards
    QScrollArea *scrollArea = new QScrollArea(dialog);
    QWidget *container = new QWidget();
    QGridLayout *layout = new QGridLayout(container);

    int cardsPerRow = 13;
    for (unsigned long long i = 0; i < (multideck.drawnCards.size()); ++i) {
        QString imagePath = multideck.drawnCards[i].imagePath();
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
    dialog->resize(950, 600); // Adjust size as needed
    dialog->exec(); // Show the dialog modally
}


void cards::onBackButtonClicked() {
    emit gameMenuRequested();
}



/**
 * @brief Displays past results in a dialog.
 *
 * Opens a dialog window showing past game results.
 */
void cards::onResultClick(){

    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Past Results");

    QVBoxLayout *layout = new QVBoxLayout();

    QTextEdit *textEdit = new QTextEdit(dialog);
    textEdit->setReadOnly(true);
    QString resultsString = gameUIInstance->records;
    textEdit->setText(resultsString);

    layout->addWidget(textEdit);

    QPushButton *closeButton = new QPushButton("Close", dialog);
    connect(closeButton, &QPushButton::clicked, dialog, &QDialog::accept);
    layout->addWidget(closeButton);

    dialog->setLayout(layout);
    dialog->resize(200, 600);
    dialog->exec();

}


