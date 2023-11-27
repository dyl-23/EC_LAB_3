#include <iostream>
#include <string>

class Account{
public:
//Use of virtual allows for methods to be overriden in future derived classes
//Constructor for Account class
    Account(const std::string& accountNumber, const std::string& accountHolder, double balance)
        : accountNumber(accountNumber), accountHolder(accountHolder), balance(balance) {}
    //destructor
    virtual ~Account()=default;
    //Will return type of account in future classes
    virtual std::string acType() const=0;

    virtual void displayDetails() const{
        std::cout<< "Account Details for "<< acType()<<" (ID: "<< accountNumber<< "):\n";
        std::cout<<" Holder: "<<accountHolder<<"\n";
        std::cout<<" Balance: $"<<balance<<"\n";
    }

    virtual void deposit(double amount){
        balance+= amount;
    }

    virtual void withdraw(double amount){
        if(amount <= balance){
            balance -=amount;
        }
        else{
            std::cout<< "Not a sufficient balance to withdraw from\n";
        }
    }
    //Allows operator overload for + access to protected variables
    friend Account& operator+(Account&, Account& to);
    //Allows operator overload for << access to protected variables
    friend std::ostream& operator<<(std::ostream& os, const Account& account);

protected:
    std:: string accountNumber;
    std:: string accountHolder;
    double balance;

};
//Will initiate a transfer between two accounts when used in main
Account& operator+(Account& from, Account& to){
    double transferm= 300.00;
    if(transferm<=from.balance){
        from.withdraw(transferm);
        to.deposit(transferm);
        std::cout<< "Account Details after transfer:\n";
    }
    else{
        std::cout<<"Unable to complete transfer. Balance is not sufficient";
        }
    return to;

    }
//Will iniate the details of an account in main
std::ostream& operator<<(std::ostream& os, const Account& account){
    account.displayDetails();
    return os;
    }

class SavingsAccount: public Account{
public:
    //added interestRate
    //Constructor for savingsaccount class
    SavingsAccount(const std::string& accountNumber, const std::string& accountHolder, double balance, double interestRate)
        : Account(accountNumber, accountHolder, balance), interestRate(interestRate){}

    std::string acType() const override{
        return "Savings Account";
    }
    //version of displaydetails displays the interestrate for svaingsaccount
    void displayDetails() const override{
        Account:: displayDetails();
        std::cout<<" Interest Rate: "<<double(interestRate*100)<<"%\n";
        std::cout<<"\n";

    }
    //Overlaoded withdraw method in Savings Account
    virtual void withdraw(double amount){
        double minimumb= 200;
        if(balance-amount>=minimumb){
            balance -=amount;
        }
        else{
            std::cout<< "Cannot complete withdrawal. Minimum balance not met\n";
        }
    }

private:
    double interestRate;
};

class CurrentAccount: public Account{
public:
    //added overdraftlimit
    //constructor for currentaccount class
    CurrentAccount(const std::string& accountNumber, const std::string& accountHolder, double balance, double overdraftlimit)
        : Account(accountNumber, accountHolder, balance), overdraftlimit(overdraftlimit){}

    std::string acType() const override{
        return "Current Account";
    }
    //version of displaydetails prints the overdraftlimit for the currentaccount
    void displayDetails() const override{
        Account:: displayDetails();
        std::cout<<" Overdraft Limit: $"<<overdraftlimit<<"\n";
        std::cout<<"\n";

    }
    //Overloaded withdraw method in CurrentAccount
    virtual void withdraw(double amount){
        if(balance+overdraftlimit>=amount){
            balance -=amount;
        }
        else{
            std::cout<< "Cannot complete withdrawal. Overdraftlimit exceeded\n";
        }
    }
private:
    double overdraftlimit;
};

int main(){
    //creating instance of savingsaccount as savings
    SavingsAccount savings("S123", "John Doe", 1000, 0.02);
    //creating instance of currentaccount as current
    CurrentAccount current("C456", "Jane Doe", 2000, 500);

    std::cout<< savings;
    std::cout<< current;

    savings.deposit(500);
    current.withdraw(1000);

    std::cout<<"Account Details after deposit and withdrawal:\n";
    std::cout<< savings;
    std::cout<< current;

    savings+current;

    std::cout<<savings;
    std::cout<<current;

    return 0;
}