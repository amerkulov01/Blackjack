#include "headers/wallet.h"


/**
 * @file wallet.cpp
 * @brief Implementation of the wallet class.
 *
 * Implements the functionalities for managing a player's funds, including adding to the balance,
 * placing bets, and initializing the wallet with a starting balance.
 * @author Dingyan Guo, Andrei Merkulov
 */




/**
 * @brief Default constructor initializing the wallet with a default balance.
 *
 * The wallet is initially set with a balance of 100. This constructor could be
 * modified to accept an initial balance if needed.
 */
wallet::wallet() {
    double initialBalance = 100; // initial balance 100
    //std::cout << "Enter the starting balance: ";
    //while(!(std::cin >> initialBalance) || initialBalance < 0) {
    //    std::cout << "Invalid amount, please enter a non-negative number: ";
    //    std::cin.clear(); // clear the error flag
    //    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard the input
    //}
    balance = initialBalance;
}

/**
 * @brief Retrieves the current balance from the wallet.
 *
 * @return The current balance as a double.
 */
double wallet::getBalance() const {
    return balance;
}


/**
 * @brief Adds a specified amount to the wallet's balance.
 *
 * This method increases the wallet's balance by the specified amount, if the amount
 * is positive.
 *
 * @param amount The amount to be added to the wallet. Must be a positive value.
 */
void wallet::addFunds(double amount) {
    if (amount > 0) {
        balance += amount;
        //std::cout << "Added funds. New balance: " << balance << std::endl;
    }
}

/**
 * @brief Sets the starting balance for the wallet.
 *
 * This method initializes the wallet's balance to the specified amount, if the amount
 * is positive.
 *
 * @param amount The starting balance to set. Must be a positive value.
 */
void wallet::startingBal(double amount) {
    if (amount > 0) {
        balance = amount;
        //std::cout << "Starting balance set to: " << balance << std::endl;
    }
}


/**
 * @brief Attempts to place a bet from the wallet's balance.
 *
 * Deducts the specified bet amount from the wallet's balance if the bet amount is positive
 * and does not exceed the current balance.
 *
 * @param betAmount The amount of the bet to place. Must be a positive value and less than
 *        or equal to the current balance.
 * @return True if the bet is successfully placed, false otherwise.
 */
bool wallet::placeBet(double betAmount) {
    if (betAmount > 0 && betAmount <= balance) {
        balance -= betAmount;
        // std::cout << "Bet placed: " << betAmount << ". New balance: " << balance << std::endl;
        return true;
    } else {
        // std::cout << "Cannot place bet. Insufficient funds or invalid bet amount." << std::endl;
        return false;
    }
}

