/*
  Name: Jia Huang
  Assignment: Lab04
  Description: Struct and class tutorial using account and transactions
*/

// Provided
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Task 1 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Define an Account struct
struct Account_struct{

  string name;
  int number;

};

// Task 2 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Define an Account class
class Account_class{
   
  friend ostream& operator << (ostream& os, const Account_class& account);

  public:

    Account_class(const string& the_name, const int the_number): name(the_name), number(the_number){};
    /*
    string get_name() const{
      return name;
    }
    int get_number() const{
      return number;
    }
    */

  private:

    string name;
    int number;
};

ostream& operator << (ostream& os, const Account_class& account){
  os << account.name << ' ' << account.number << endl;
  return os;
}

// Task 3 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Define an Account and Transaction classes
class Transaction{

  friend ostream& operator << (ostream& os, const Transaction& transaction);

  public:

    Transaction(const bool the_deposit, const int the_amount): deposit(the_deposit), amount(the_amount){}

    bool is_deposit() const{
      return deposit;
    }

  private:

    bool deposit;
    int amount;
};

class Account_trans{

  friend ostream& operator << (ostream& os, const Account_trans& account);

  public:

    Account_trans(const int the_number, const string& the_name): number(the_number), name(the_name), balance(0){}

    void deposit(int amount){
      balance += amount;
      history.push_back(Transaction(true, amount));
    }

    void withdrawal(int amount){
      if (amount > balance){
        cout << "Account# " << number << " has only " << balance << ". Insufficient for withdrawal of " << amount << '.' << endl;
        return;
      }
      balance -= amount;
      history.push_back(Transaction(false, amount));
    }

    int get_number() const{
      return number;
    }

  private:

    string name;
    int number;
    vector<Transaction> history;
    int balance;
};

ostream& operator << (ostream& os, const Transaction& transaction){
  if (transaction.deposit){
    os << "deposit " << transaction.amount << endl;
  }
  else{
    os << "withdrawal " << transaction.amount << endl;
  }
  return os;
}

ostream& operator << (ostream& os, const Account_trans& account){
  os << account.name << ' ' << account.number << endl;
  for (Transaction transaction: account.history){
    os << "    " << transaction;
  }
  return os;
}

// Task 4 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Define an Account with a nested public Transaction class
class Account_nest_pub{
  
  friend ostream& operator << (ostream& os, Account_nest_pub& account);
  public:
    class Transaction{
      friend ostream& operator << (ostream& os, Transaction& transaction);
      public:
        Transaction(const bool the_deposit, const int the_amount): deposit(the_deposit), amount(the_amount){}
      private:
        bool deposit;
        int amount;
    }; 
  Account_nest_pub(const int the_number, const string& the_name): number(the_number), name(the_name), balance(0){}
    void deposit(int amount){
      balance += amount;
      history.push_back(Transaction(true, amount));
    }
    void withdrawal(int amount){
      if (amount > balance){
        cout << "Account# " << number << " has only " << balance << ". Insufficient for withdrawal of " << amount << '.' << endl;
        return;
      }
      balance -= amount;
      history.push_back(Transaction(false, amount));
    }
    int get_number() const{
      return number;
    }
  private:
    string name;
    int number;
    vector<Transaction> history;
    int balance;
};

ostream& operator << (ostream& os, Account_nest_pub::Transaction& transaction){
  if (transaction.deposit){
    os << "deposit " << transaction.amount << endl;
  }
  else{
    os << "withdrawal " << transaction.amount << endl;
  }
  return os;
}

ostream& operator << (ostream& os, Account_nest_pub& account){
  os << account.name << ' ' << account.number << endl;
  for (Account_nest_pub::Transaction transaction: account.history){
    os << "    " << transaction;
  }
  return os;
}

// Task 5 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Define an Account with a nested private Transaction class
class Account_nest_priv{
  public:
    friend ostream& operator << (ostream& os, const Account_nest_priv& account);
    Account_nest_priv(const int the_number, const string& the_name): number(the_number), name(the_name), balance(0){}
    void deposit(int amount){
      balance += amount;
      history.push_back(Transaction(true, amount));
    }
    void withdrawal(int amount){
      if (balance < amount){
        cout << "Account# " << number << " has only " << balance << ". Insufficient for withdrawal of " << amount << '.' << endl;
        return;
      }
      balance -= amount;
      history.push_back(Transaction(false, amount));
    }
    int get_number() const{
      return number;
    }
  private:
    class Transaction{
      public:
        Transaction(const bool the_deposit, const int the_amount): deposit(the_deposit), amount(the_amount){}
        friend ostream& operator << (ostream& os, const Transaction& transaction);
      private:
        bool deposit;
        int amount;
    }; 
    friend ostream& operator << (ostream& os, const Transaction& transaction);
    int number;
    string name;
    vector<Transaction> history;
    int balance;
};

ostream& operator << (ostream& os, const Account_nest_priv::Transaction& transaction){
  if (transaction.deposit){
    os << "deposit " << transaction.amount << endl;
  }
  else{
    os << "withdrawal " << transaction.amount << endl;
  }
  return os;
}

ostream& operator << (ostream& os, const Account_nest_priv& account){
  os << account.name << ' ' << account.number << endl;
  for (const Account_nest_priv::Transaction& transaction: account.history){
    os << "    " << transaction;
  }
  return os;
}


int main() {

    // Task 1: account as struct /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //      1a
    cout << "Task1a:\n";
    cout << "Filling vector of struct objects, define a local struct instance and set fields explicitly:" << endl;
    //struct vector
    vector<Account_struct> account_struct_vec;
    //local variables for looping file
    string name;
    int number;
    //open file
    ifstream ifs("accounts.txt");
    if (!ifs){
      cerr << "Could not open file";
      exit(1);
    }
    //loop through file
    while (ifs >> name >> number){
      //create and add new account struct to vector
      Account_struct account;
      account.name = name;
      account.number = number;
      account_struct_vec.push_back(account);
    }
    //close file
    ifs.close();
    //display vector
    for (Account_struct& account: account_struct_vec){
      cout << account.name << ' ' << account.number << endl;
    }

    //      1b ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    cout << "Task1b:\n";
    cout << "Filling vector of struct objects, using {} initialization:\n";
    //clear vector
    account_struct_vec.clear();
    //open file
    ifs.open("accounts.txt");
    if (!ifs){
      cerr << "Could not open file";
      exit(1);
    }
    //loop file and add new account struct to vector
    while (ifs >> name >> number){
      Account_struct account{name, number};
      account_struct_vec.push_back(account);
    }
    //close file
    ifs.close();
    //display vector
    for (Account_struct& account: account_struct_vec){
      cout << account.name << ' ' << account.number << endl;
    }

    //==================================
    // Task 2: account as class //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //      2a
    cout << "==============\n";
    cout << "\nTask2a:"; ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    cout << "\nFilling vector of class objects, using local class object:\n";
    //class vector
    vector<Account_class> account_class_vec;
    ifs.open("accounts.txt");
    if (!ifs){
      cerr << "Could not open file";
      exit(1);
    }
    //loop file and add new account class to vector
    while (ifs >> name >> number){
      Account_class account(name, number);
      account_class_vec.push_back(account);
    }
    //close file
    ifs.close();
    //display vector
    for (Account_class& account: account_class_vec){
       cout << account;
    }

    cout << "\nTask2b:\n"; ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    cout << "output using output operator with getters\n";
    //display vector using output operator
    for (Account_class& account: account_class_vec){
       cout << account;
    }

    cout << "\nTask2c:\n"; /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    cout << "output using output operator as friend without getters\n";
    //display vector using new output operator
    for (Account_class& account: account_class_vec){
      cout << account;
    }

    cout << "\nTask2d:\n"; /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    cout << "Filling vector of class objects, using temporary class object:\n";
    //clear vector
    account_class_vec.clear();
    //open file
    ifs.open("accounts.txt");
    if (!ifs){
      cerr << "Could not open file";
      exit(1);
    }
    //loop file and add new account class to vector
    while (ifs >> name >> number){
      account_class_vec.push_back(Account_class(name, number));
    }
    //close file
    ifs.close();
    //display vector
    for (Account_class& account: account_class_vec){
      cout << account;
    }
    
    cout << "\nTask2e:\n"; //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    cout << "Filling vector of class objects, using emplace_back:\n";
    //clear vector
    account_class_vec.clear();
    //open file
    ifs.open("accounts.txt");
    if (!ifs){
      cerr << "Could not open file";
      exit(1);
    }
    //loop file and add new account class to vector
    while (ifs >> name >> number){
      account_class_vec.emplace_back(Account_class(name, number));
    }
    //close file
    ifs.close();
    //display vector
    for (Account_class& account: account_class_vec){
      cout << account;
    }
    
    cout << "==============\n";
    cout << "\nTask 3:\nAccounts and Transaction:\n"; ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    vector<Account_trans> account_trans_vec;
    //looping variable
    string command;
    int amount;
    //open file
    ifs.open("transactions.txt");
    if (!ifs){
      cerr << "Could not open file";
      exit(1);
    }
    //loop file
    while (ifs >> command){
      if (command == "Account"){
        ifs >> name >> number;
        account_trans_vec.emplace_back(Account_trans(number, name));
      }
      else if (command == "Deposit"){
        ifs >> number >> amount;
        for (Account_trans& account: account_trans_vec){
          if (number == account.get_number()){
            account.deposit(amount);
            break;
          }
        }
      }
      else if (command == "Withdraw"){
        ifs >> number >> amount;
        for (Account_trans& account: account_trans_vec){
          if (number == account.get_number()){
            account.withdrawal(amount);
            break;
          }
        }
      }
    }
    //close file
    ifs.close();
    //display vector
    for (Account_trans& account: account_trans_vec){
      cout << account << endl;
    }

    cout << "==============\n";
    cout << "\nTask 4:\nTransaction nested in public section of Account:\n"; ///////////////////////////////////////////////////////////////////////////////////////////
    vector<Account_nest_pub> account_nest_pub_vec;
    ifs.open("transactions.txt");
    if (!ifs){
      cerr << "Could not open file";
      exit(1);
    }
    while (ifs >> command){
      if (command == "Account"){
        ifs >> name >> number;
        account_nest_pub_vec.emplace_back(Account_nest_pub(number, name));
      }
      else if (command == "Deposit"){
        ifs >> number >> amount;
        for (Account_nest_pub& account: account_nest_pub_vec){
          if (number == account.get_number()){
            account.deposit(amount);
            break;
          }
        }
      }
      else if (command == "Withdraw"){
        ifs >> number >> amount;
        for (Account_nest_pub& account: account_nest_pub_vec){
          if (number == account.get_number()){
            account.withdrawal(amount);
            break;
          }
        }
      }
    }
    //close file
    ifs.close();
    //display vector
    for (Account_nest_pub& account: account_nest_pub_vec){
      cout << account << endl;
    }
  
    cout << "==============\n";
    cout << "\nTask 5:\nTransaction nested in private section of Account:\n"; ///////////////////////////////////////////////////////////////////////////////////////////
    vector<Account_nest_priv> account_nest_priv_vec;
    ifs.open("transactions.txt");
    if (!ifs){
      cerr << "Could not open file";
      exit(1);
    }
    while (ifs >> command){
      if (command == "Account"){
        ifs >> name >> number;
        account_nest_priv_vec.emplace_back(Account_nest_priv(number, name));
      }
      else if (command == "Deposit"){
        ifs >> number >> amount;
        for (Account_nest_priv& account: account_nest_priv_vec){
          if (number == account.get_number()){
            account.deposit(amount);
            break;
          }
        }
      }
      else if (command == "Withdraw"){
        ifs >> number >> amount;
        for (Account_nest_priv& account: account_nest_priv_vec){
          if (number == account.get_number()){
            account.withdrawal(amount);
            break;
          }
        }
      }
    }
    //close file
    ifs.close();
    //display vector
    for (Account_nest_priv& account: account_nest_priv_vec){
      cout << account <<endl;
    }
}
