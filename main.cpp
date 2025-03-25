// Mark Goulet
// CIS-17B
// 3-24-2025

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

// Exception Class for Negative Deposit
class NegativeDepositException : public exception {
	public:
	const char* what() const noexcept override {
		return "Error: Cannot Perform Deposit with Given Amount.";
	}
};

// Exception Class for Overdraw
class OverdrawException : public exception {
	public:
	const char* what() const noexcept override {
		return "Error: Cannot Perform Withdraw with Account Balance.";
	}
};

// Exception Class for Negative Withdraw
class NegativeWithdrawException : public exception {
	public:
	const char* what() const noexcept override {
		return "Error: Cannot Perform Withdraw with Given Amount.";
	}
};

// Exception Class for Closed Account Operations
class InvalidAccountOperationException : public exception {
	public:
	const char* what() const noexcept override {
		return "Error: Invalid Account Operation.\n Option not Available or Account Closed.";
	}
};

// BankAcount Class
class BankAccount {
	private:
		int accountNumber;
		double balance;
		bool isActive;

	public:
		// Class constructor that assigns randomized six-digit number
		BankAccount(double initialBalance) : balance(initialBalance), isActive(true) {
			accountNumber = generateAccountNumber();
		}

		//member functions with associated exception classes
		void deposit(double amount) {
			if (isActive != true) {
				throw InvalidAccountOperationException();
			}
			if (amount < 0) {
				throw NegativeDepositException();
			} else {
				this->balance += amount;
			}
		}

		void withdraw(double amount) {
			if (isActive != true) {
				throw InvalidAccountOperationException();
			}
			if (amount < 0) {
				throw NegativeWithdrawException();
			}
			if (amount > balance) {
				throw OverdrawException();
			} else {
				this->balance -= amount;
			}
		}

		double getBalance() {
			if (isActive != true) {
				throw InvalidAccountOperationException();
			} else {
				return this->balance;
			}
		}

		void closeAccount() {
			isActive = false;
		}

		int generateAccountNumber() {
			srand(time(0));
			int num = rand() % 900000 + 100000;
			return num;
		}

		int getAccountNumber() {
			return this->accountNumber;
		}

};

// global functions with class pointer parameters

void deposit (BankAccount *account) {
	double amount;
	cout << "Enter deposit amount: $";
	cin >> amount;
	try {
		account->deposit(amount);
		cout << "Deposit Successful!" << endl;
		cout << "Account Balance: $" << account->getBalance() << endl;
	} catch (const exception &e) {
		cout << e.what() << endl;
	}

}

void withdraw (BankAccount *account) {
	double amount;
	cout << "Enter withdraw amount: $";
	cin >> amount;
	try {
		account->withdraw(amount);
		cout << "Withdraw Successful!" << endl;
		cout << "Account Balance: $" << account->getBalance() << endl;
	} catch (const exception &e) {
		cout << e.what() << endl;
	}
}

void accountMenu (BankAccount *account) {
	int choice = 0;

	do {
		try {
			cout << "\n------Account Menu----- \n";
			cout << "1. Deposit Funds \n";
			cout << "2. Withdraw Funds \n";
			cout << "3. View Account Balance \n";
			cout << "4. Close Account \n";
			cout << "5. Exit\n";
			cout << "\nSelect a menu option: ";
			cin >> choice;

			switch (choice) {
				case 1:
					deposit(account);
				break;
				case 2:
					withdraw(account);
				break;
				case 3:
					cout << "Account Balance: $" << account->getBalance() << endl;
				break;
				case 4:
					account->closeAccount();
				cout << "Account Closed." << endl;
				break;
				case 5:
					cout << "Thank you for banking with us! Have a Nice Day!" << endl;
				break;
				default:
					cout << "\nInvalid Input. Please Choose Valid Menu Option." << endl;
					cin.clear();
					cin.ignore();
					throw InvalidAccountOperationException();
			}
		} catch (const exception &e) {
			cout << e.what() << endl;
		}

	} while (choice != 5);
}


int main() {
	try {
		double initialDeposit;


		cout << "Please Enter Your Initial Deposit: $";
		cin >> initialDeposit;

		// exception handling for negative intitial balance
		if (initialDeposit < 0) {
			cout << "Account Creation Failed with the following error.." << endl;
			throw NegativeDepositException();
		}
		// unique instance creation of BankAccount
		auto instance = make_unique<BankAccount>(initialDeposit);

		cout << "\nBank Account " << instance->getAccountNumber() << " Created Successfully!" << endl;

		cout << "\nBank Account " << instance->getAccountNumber() << " Information" << endl;
		cout << "Balance: $" << instance->getBalance() << endl;

		// run account menu loop
		accountMenu(instance.get());

	} catch (const exception &e) {
		cout << e.what() << endl;
	}
	return 0;
}