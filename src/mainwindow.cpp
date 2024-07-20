/**
 * @file mainwindow.cpp
 * @brief Implementation of the MainWindow class for the BlackJack Simulator application.
 *
 * Implements the MainWindow class, which orchestrates the UI of the BlackJack Simulator application.
 * It initializes the UI components and handles transitions between the application's different UI screens,
 * such as the start menu, game UI, and cards menu. The MainWindow class acts as the backbone of the
 * application's user interface, facilitating interaction between the user and the application's core functionalities.
 * @author Derick Yuan, Dingyan Guo, Ryan Lu
 * @date April 1, 2024
 */

#include "headers/mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief Constructs a new MainWindow object.
 * @param parent Pointer to the parent widget.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initializeUI();
}

/**
 * @brief Destroys the MainWindow object.
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief Initializes the UI components and setups up the initial state of the application window.
 * This includes setting up the minimum size of the window and initializing the start menu.
 */
void MainWindow::initializeUI() {
    this->setMinimumSize(1200, 750);
    startMenu = new StartMenu(this, &myWallet);
    setCentralWidget(startMenu);

    connect(startMenu, &StartMenu::startGameRequested, this, &MainWindow::switchToGameUI);
}

/**
 * @brief Switches the central widget to the game UI and sets up the connection for transitioning to the cards menu UI.
 */
void MainWindow::switchToGameUI() {
    gameUI = new GameUI(this, &myWallet);
    setCentralWidget(gameUI);
    connect(gameUI, &GameUI::cardsMenuRequested, this, &MainWindow::switchToCardsMenuUI);
}

/**
 * @brief Switches the central widget to the cards menu UI if the game UI exists.
 */
void MainWindow::switchToCardsMenuUI() {
    if (gameUI) { // Ensure gameUI exists
        setCentralWidget(cardsMenu);
    }
}

