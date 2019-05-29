#include "UserPanel.hpp"
#include "Functions.hpp"
#include <iostream>
#include "getch.hpp"

UserPanel::UserPanel(User & _user, std::shared_ptr<OperationControl> & _operation)
	:currentUser{_user}, operation{_operation}
{
}


UserPanel::~UserPanel()
{
}

void UserPanel::displayUserPanel()
{
	int pos = 0;
	do
	{
		Functions::clearScreen();
		if (currentUser->active != true && currentUser->toDelete != false)
		{
			std::cout << "\n\t *** Konto zablokowane ***" << std::endl;
			std::cout << "\n\tPress any key to continue ...";
			pk::getch(); pk::getch();
			return;
		}

		std::string name = currentUser->firstName + " " + currentUser->lastName;
		std::cout << name << std::endl;
		std::vector<std::string> labels{ "Dodaj srodki", "Przelew", "Wyplac","Sprawdz histore","Zamknij konto","Wyloguj" };
		pos = Functions::menuControl(labels, "USER PANEL", currentUser);

		switch (pos)
		{
		case 0: payIn(); break;
		case 1: transfer(); break;
		case 2: payOut(); break;
		case 3: displayMyHistory(); break;
		case 4: deleteAccount(); break;
		}
	} while (pos != 5);
}

void UserPanel::payIn()
{
	Functions::clearScreen();
	Functions::menuHeader("WPLATA");
	double value;
	do
	{
		std::cout << "\tWproawdz kwote: ";
		std::cin >> value;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (!std::cin || value <= 0)
		{
			std::cout << "\n\tNiepoprawne dane. Sprobuj jeszcze raz ...\n";
			std::cout << "\tNacisnij 'Esc' by przerwac lub Enter by kontynuowac\n\n";
			char ch;
			std::cin.clear();
			pk::getch();
			ch = pk::getch();
			
			if (ch == 27)
				return;
		}

	} while (!std::cin || value <= 0);
	std::string str = currentUser->firstName + " " + currentUser->lastName;
	std::shared_ptr<History> newHistRecod (new History{ "*****  ***** ","***** ",str,currentUser->accountNumber,"WPLATA",value });
	currentUser->balance += value;
	operation->transfer(newHistRecod, currentUser);
}

void UserPanel::transfer()
{
	
	using namespace std;
	cin.clear();
	string account;
	string recipient{};
	double amount;
	bool correctAccount;
	bool correctAmount;
	bool correctPass;
	do
	{
		Functions::clearScreen();
		cin.clear();
		Functions::menuHeader("PRZELEW");
		//cout << "\tPodaj odbiorce: ";
		//getline(cin, recipient);
		//cin.clear();
		std::string firstName;
		std::string lastName;
		cout << "\tPodaj Imie odbiorcy: ";
		cin >> firstName;
		recipient = firstName;
		recipient += " ";
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "\tPodaj Nazsiwko odbiorcy: ";
		cin >> lastName;
		recipient += lastName;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			 
		cout << "\tPodaj nr konta odbiorcy: ";
		cin >> account;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		cout << "\tPodaj kwote: ";
		cin >> amount;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


		if (!cin || amount < 0)
		{
			correctAmount = false;
		}
		else
		{
			correctAmount = true;
		}

		if (currentUser->balance - amount < 0)
		{
			correctAmount = false;
			cout << "\tBrak wystarczajacych srodkow na koncie" << endl;

		}

		//_Functions::getch();
		correctAccount = operation->checkRequest(account, 0);
		if (correctAccount == false || correctAmount == false)
		{
			cout << "\n\tNiepoprawne dane" << endl;
			cout << "\t   Esc - przerwij" << endl;
			cout << "\t   Enter - Sproboj ponownie" << endl;
			pk::getch();
			char c = pk::getch();
			if (c == 27)
				return;
		}


	} while (correctAccount == false || correctAmount == false);

	summary(recipient, account, amount);

	char ch;
	do
	{
		ch = pk::getch();
	} while (ch != 'y' && ch != 'n');
	if (ch == 'n')
		return;
	correctPass = checkPassword();
	if (correctPass == false)
		return;

	std::string str = currentUser->firstName + " " + currentUser->lastName;
	std::shared_ptr<History>newHistRecord(new History{ str,currentUser->accountNumber,recipient,account,"PRZELEW", amount });
	currentUser->balance -= amount;
	operation->transfer(newHistRecord, currentUser);
	std::cout << "\tOperacja przebiegla poprawnie. Nacisnij Enter" << std::endl;
	std::cout << "\n\tPress any key to continue ...";
	pk::getch(); pk::getch();
}

void UserPanel::payOut()
{
	using namespace std;
	string account;
	string recipient;
	double amount;
	bool correctAccount;
	bool correctAmount;
	bool correctPass;
	do
	{
		Functions::clearScreen();
		Functions::menuHeader("WYPLATA");
		cout << "\tPodaj kwote: ";
		cin >> amount;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


		if (!cin || amount < 0)
		{
			correctAmount = false;
		}
		else
		{
			correctAmount = true;
		}

		if (currentUser->balance - amount < 0)
		{
			correctAmount = false;
			cout << "\tBrak wystarczajacych srodkow na koncie" << endl;

		}

		pk::getch();

	} while (correctAmount == false);

	cout << endl << endl;
	cout << "\t\tPotwierdzasz operacje? (y/n)" << endl;

	char ch;
	do
	{
		ch = pk::getch();
	} while (ch != 'y' && ch != 'n');

	if (ch == 'n')
		return;

	correctPass = checkPassword();
	if (correctPass == false)
		return;

	std::string str = currentUser->firstName + " " + currentUser->lastName;
	std::shared_ptr<History>newHistRecord(new History{ str,currentUser->accountNumber,"***** *****","*****","WYPLATA", amount });
	currentUser->balance -= amount;
	operation->transfer(newHistRecord, currentUser);
	std::cout << "\tOperacja przebiegla poprawnie. Nacisnij Enter" << std::endl;
	std::cout << "\n\tPress any key to continue ...";
	pk::getch(); pk::getch();

}

void UserPanel::displayMyHistory()
{
	operation->dispalyUserHist(currentUser->accountNumber);
}

void UserPanel::deleteAccount()
{
	Functions::clearScreen();
	Functions::menuHeader("DELETA ACCOUNT");

	std::cout << "\tCzy jestes pewny, ze chcesz usunac konto? (y/n)" << std::endl;
	char ch;
	do
	{
		ch = pk::getch();
	} while (ch != 'y' && ch != 'n');
	if (ch == 'n')
		return;

	bool correctPass = checkPassword();

	if (correctPass == false)
		return;

	currentUser->toDelete = true;
	operation->updateUser(currentUser);
}

void UserPanel::summary(const std::string & recipient, const std::string & rAccount, const double & amount)
{
	Functions::clearScreen();
	Functions::menuHeader("SUMMARY");
	using namespace std;
	cout << "\t TRANSFER FROM:" << endl;
	cout << "\t-------------------" << endl;
	cout << "\t" << currentUser->firstName << " " << currentUser->lastName << endl;
	cout << "\tNumer konta: " << currentUser->accountNumber << endl;
	cout << "\t----------------------------------------" << endl;
	cout << "\tKwota: " << amount << "$" << "\t Saldo po operacji: " << currentUser->balance - amount << "$" << endl;
	cout << "\t----------------------------------------" << endl;
	cout << "\tTRANSFER TO: " << endl;
	cout << "\t-------------------" << endl;
	cout << "\t" << recipient << endl;
	cout << "\tNumer konta: " << rAccount;
	cout << endl << endl;
	cout << "\tPotwierdzasz operacje? (y/n)" << endl;
}

bool UserPanel::checkPassword()
{
	bool correctPass;
	std::string pass;
	std::cout << "\n\tPodaj haslo aby potwierdzic operacja" << std::endl;

	do
	{
		std::cout << "\n\tIlosc prob:" << currentUser->wrongLogCounter << std::endl;
		std::cout << "\tHaslo: ";
		std::cin >> pass;
		correctPass = operation->checkRequest(pass, 3);

		if (correctPass == false)
		{
			currentUser->wrongLogCounter--;
			std::cout << "\n\tBledene haslo" << std::endl;
			std::cout << "\tEsc - przerwij" << std::endl;
			std::cout << "\tEnter - Sproboj ponownie" << std::endl;
			pk::getch();
			char c = pk::getch();
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			if (c == 27)
				return false;
		}

	} while (correctPass == false && currentUser->wrongLogCounter != 0);

	if (currentUser->wrongLogCounter == 0)
	{
		currentUser->active = false;
		operation->updateUser(currentUser);
		std::cout << "\n\t3 razy wspisano bledne haslo" << std::endl;
		std::cout << "\n\tPress any key to continue ...";
		pk::getch(); pk::getch();
		return false;
	}
	else
	{
		currentUser->wrongLogCounter = 3;
		return true;
	}
}

