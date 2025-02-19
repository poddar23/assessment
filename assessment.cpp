#include <iostream>
#include <ctime>  
#include <string> 

using namespace std;

class ATM
{
private:
    int pin = 12345;  
    double initial_balance = 60000.0;  
    double account_balance = 20000.0;  

public:
    
    ATM()
    {
        
    }

    void displayDateTime()
    {
        time_t current_time;
        struct tm * time_info;
        char buffer[80];

        time(&current_time); 
        time_info = localtime(&current_time);

        strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", time_info);  
        string str(buffer);

        cout << "Current Date and Time: " << str << endl << endl;
    }

    void displayMenu()
    {
        cout << "Welcome to the ATM Banking System!" << endl;
        cout << "1. Enter ATM Pin" << endl;
        cout << "2. Help" << endl;
        cout << "3. Exit" << endl;
    }

    void displayHelp()
    {
        cout << "ATM Banking Help: " << endl;
        cout << "1. Enter the correct ATM PIN to access the menu." << endl;
        cout << "2. You can deposit money into your account, check balance, or withdraw funds." << endl;
        cout << "3. Please ensure sufficient balance before withdrawing." << endl;
        cout << "4. If you enter the incorrect PIN, the program will exit." << endl;
    }

    bool checkPin(int enteredPin)
    {
        if (enteredPin == pin)
        {
            return true;
        }
        else
        {
            cout << "Incorrect PIN. Exiting the program..." << endl;
            return false;
        }
    }

    void depositMoney()
    {
        double depositAmount;
        cout << "Enter the amount you want to deposit: Rs. ";
        cin >> depositAmount;

        account_balance += depositAmount;
        cout << "Deposit successful!" << endl;
        cout << "Your new account balance is: Rs. " << account_balance << endl;
    }

    void withdrawMoney()
    {
        double withdrawAmount;
        cout << "Enter the amount you want to withdraw: Rs. ";
        cin >> withdrawAmount;

        if (withdrawAmount > account_balance)
        {
            cout << "Insufficient balance! Withdrawal unsuccessful." << endl;
        }
        else
        {
            account_balance -= withdrawAmount;
            cout << "Withdrawal successful!" << endl;
            cout << "Your new account balance is: Rs. " << account_balance << endl;
        }
    }

    void checkBalance()
    {
        cout << "Your current account balance is: Rs. " << account_balance << endl;
    }
};

int main()
{
    ATM atm;
    int choice, enteredPin;

    atm.displayDateTime();

    while (true)
    {
        atm.displayMenu();
        cout << "Select your choice (1-3): ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            
            cout << "Enter ATM PIN: ";
            cin >> enteredPin;

            if (atm.checkPin(enteredPin))
            {
                int action;
                do
                {
                    cout << "\nATM Menu:" << endl;
                    cout << "1. Deposit Money" << endl;
                    cout << "2. Withdraw Money" << endl;
                    cout << "3. Check Balance" << endl;
                    cout << "4. Exit" << endl;
                    cout << "Enter your choice (1-4): ";
                    cin >> action;

                    switch (action)
                    {
                    case 1:
                        atm.depositMoney();
                        break;

                    case 2:
                        atm.withdrawMoney();
                        break;

                    case 3:
                        atm.checkBalance();
                        break;

                    case 4:
                        cout << "Thank you for using the ATM! Exiting..." << endl;
                        break;

                    default:
                        cout << "Invalid choice! Please try again." << endl;
                    }
                } while (action != 4);
            }
            break;

        case 2:
            atm.displayHelp();
            break;

        case 3:
            cout << "Exiting the ATM system. Goodbye!" << endl;
            return 0;

        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
