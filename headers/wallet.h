#ifndef WALLET_H
#define WALLET_H


/**
 * @file wallet.h
 * @brief Declaration of the wallet class for managing a player's funds.
 *
 * The wallet class is responsible for tracking and managing the player's funds throughout
 * the game. It allows for adding funds, placing bets, and querying the current balance.
 * @author Dingyan Guo, Andrei Merkulov
 */



/**
 * @class wallet
 * @brief Manages player funds for bets and winnings.
 *
 * This class provides methods to handle the player's money, including adding to the balance,
 * placing bets, and setting a starting balance. It ensures that bets are only placed if
 * sufficient funds are available.
 */
class wallet
{
private:
    double balance;

public:
    wallet(); // Constructor to initialize the wallet and ask the user for a starting balance
    double getBalance() const; // Returns the current balance
    void addFunds(double amount); // Adds funds to the wallet
    void startingBal(double amount); // Sets the starting balance (used directly to set the balance)
    bool placeBet(double betAmount); // Attempts to place a bet, returns true if successful
};

#endif // WALLET_H


