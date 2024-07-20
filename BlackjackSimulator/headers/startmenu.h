/**
 * @file startmenu.h
 * @brief Header file for the StartMenu class in the BlackJack Simulator application.
 *
 * This file declares the StartMenu class, which is responsible for displaying the
 * initial user interface where players can start the game, add balance to their wallet,
 * view the rulebook, and view the moves chart.
 * @author Anthony Martin Pinto, Andrei Le Merkulov
 * @date April 1, 2024
 */

#ifndef STARTMENU_H
#define STARTMENU_H

#include <QWidget>
#include <QtWidgets>
#include <QPixmap>
#include "headers/wallet.h"

class StartMenu : public QWidget {
    Q_OBJECT

public:
  	/**
     * @brief Constructor for the StartMenu class.
     * @param parent Pointer to the parent widget, default is nullptr.
     * @param myWallet Pointer to the wallet object, used for managing game currency.
     */
    StartMenu(QWidget *parent = nullptr, wallet* myWallet = nullptr);


signals:
  	/**
     * @brief Signal emitted when the start game button is clicked.
     */
    void startGameRequested();

private slots:
  	/**
     * @brief Updates the wallet balance based on user input.
     */
    void updateBalance();
    
  	/**
     * @brief Displays a chart showing optimal moves in blackjack.
     */
  	void showChart();
  
  	/**
     * @brief Initiates the game start process.
     */
    void onStartGameClicked();
  
  	/**
     * @brief Displays the blackjack rules.
     */
    void showRules();

private:
    wallet *myWallet;
    QLabel *walletLabel;

};

#endif // STARTMENU_H
