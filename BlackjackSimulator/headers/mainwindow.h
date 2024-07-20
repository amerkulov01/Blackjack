/**
 * @file mainwindow.h
 * @brief Header file for the MainWindow class in the BlackJack Simulator application.
 *
 * This file declares the MainWindow class, which serves as the central window of the application.
 * It handles the transitions between the start menu, game UI, and cards menu, effectively managing
 * the different stages of the application's lifecycle. This class is a crucial part of the application's
 * user interface, ensuring a seamless user experience.
 * @author Derick Yuan, Dingyan Guo, Ryan Lu
 * @date April 1, 2024
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "headers/startmenu.h"
#include "headers/gameui.h"
#include "headers/wallet.h"
#include "headers/cards.h" //tesitng only


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	/**
     * @brief Constructor for MainWindow.
     * @param parent Pointer to the parent widget, default is nullptr.
     */
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    
    StartMenu *startMenu;
    
    GameUI *gameUI;
    
    wallet myWallet;
    
    cards *cardsMenu; // testing only
    
    /**
     * @brief Initializes the UI components and setups up initial state of the application window.
     */
    void initializeUI();

private slots:
	/**
     * @brief Switches the central widget to the game UI.
     */
    void switchToGameUI();

	/**
     * @brief Switches the central widget to the cards menu UI.
     */
    void switchToCardsMenuUI(); // for testing only

};
#endif // MAINWINDOW_H

