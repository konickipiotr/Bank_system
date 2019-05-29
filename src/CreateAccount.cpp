#include "CreateAccount.hpp"
#include "DataBase.hpp"
#include "Functions.hpp"
#include <memory>
#include <iostream>
#include "getch.hpp"

CreateAccount::CreateAccount(std::shared_ptr<OperationControl>& _operation)
{
	operation = _operation;
}


CreateAccount::~CreateAccount()
{
}

void CreateAccount::CreatMenu()
{
	bool createAccount = false;
	S_User newUser = std::make_shared<UserRecord>();
	fillForm(newUser);

	if (newUser->age < 18)
	{
		return;
	}

	newUser->accountNumber = numberAccountGenerator();
	newUser->password = passwordGenerator();
	
	char key;

	std::cout << "\tPotwierdzasz zalozenie konta? (y/n)";
	do
	{
		key = pk::getch();
		
		if (key == 'n')
			return;

	} while (key != 'y' && key != 'n');

	summary(newUser);
	operation->addUser(newUser);
	
}

void CreateAccount::fillForm(std::shared_ptr<UserRecord> & newUser)
{
	bool correctFName;
	bool correctLName;
	bool correctData;
	using namespace std;
	
	Functions::clearScreen();

	
	Functions::menuHeader("CREATE ACCOUNT");

	do {
		correctData = true;
		cin.clear();
		cout << "\n\tFirst name _________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
		cin >> newUser->firstName;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		correctFName = Functions::chectText(newUser->firstName);
		cout << "\tLast name _________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
		cin >> newUser->lastName;
		correctLName = Functions::chectText(newUser->lastName);


		char key;

	
		
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin.clear();
		cout << "\tAge ___\b\b\b";
		cin >> newUser->age;
		cout << endl;
		if (!cin )
		{	
			correctData = false;
			std::cout << "\tNiepoprawne dane. Sprobuj jeszcze raz ...\n";
			std::cout << "\tNacisnij 'Esc' by przerwac lub Enter by kontynuowac\n\n";
			
			pk::getch();
			key = pk::getch();
			
			
			if (key == 27)
			{
				return;
			}
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				

		}
		else if (newUser->age < 0 || newUser->age>150 || !correctFName || !correctLName)
		{
			correctData = false;
			std::cout << "\tNiepoprawne dane. Spruboj jeszcze raz ...\n";
			std::cout << "\tNacisnij 'Esc' by przerwac lub Enter by kontynuowac\n\n";
			
			pk::getch();
			key = pk::getch();
			
			if (key == 27)
			{
				return;
			}
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (newUser -> age < 18) {
			cout << "\tJestes za mlody\n\t";
			Functions::pause();
			return;
		}
		
	} while (!correctData);
}

std::string CreateAccount::numberAccountGenerator()
{
	bool correct = false;
	std::random_device rd{};
	std::mt19937 gen{ rd() };
	std::uniform_real_distribution<> a(100000, 999999);
	std::string stringAccount;
	do
	{
		correct = false;
		int los = (int)std::round(a(gen));
		stringAccount = std::to_string(los);
		correct = operation->checkRequest(stringAccount, 0);
	} while (correct == true);
	return stringAccount;
}

std::string CreateAccount::passwordGenerator()
{
	std::string password;
	std::random_device rd{};
	std::mt19937 gen{ rd() };
	std::uniform_real_distribution<> a(97, 122);
	std::uniform_real_distribution<> b(65, 90);
	std::uniform_real_distribution<> c(48, 57);
	std::uniform_real_distribution<> d(0, 2);
	const int LENGTHPASS = 3;
	for (int i = 0; i < LENGTHPASS; ++i)
	{
		int num = 0;
		int wyb = (int)std::round(d(gen));
		switch (wyb)
		{
		case 0: num = (int)std::round(a(gen)); break;
		case 1: num = (int)std::round(b(gen)); break;
		case 2: num = (int)std::round(c(gen)); break;
		}

		password += (char)num;
	}
	return password;
}

void CreateAccount::summary(const std::shared_ptr<UserRecord>& newUser)
{
	using namespace std;
	Functions::clearScreen();
	Functions::menuHeader("PODSUMOWANIE");
	cout << "\tUzytkownik: " << newUser->firstName << " " << newUser->lastName << endl;
	cout << "\tWiek: " << newUser->age << endl << endl;
	cout << "\tNumer konta: " << newUser->accountNumber << endl;
	cout << "\t--------------------------------------------" << endl << endl;
	cout << "\tLogin: " << newUser->lastName << "\tHaslo: " << newUser->password << endl;
	cout << "\t!!! Zamapietaj lub zapisz te informacje !!!" << endl;
	cout << "\t--------------------------------------------" << endl << endl;
	cout << "\tSTATUS KONTA: ";
	if (newUser->active == false)
	{
		cout << "Nieaktywne" << endl;
		cout << "\tCzekaj na zatwierdzenie konta przez administratora\n" << endl << endl;
	}
	else
	{
		cout << " Aktywne" << endl << endl;
	}
	cout << "\tPress any key to continue ...";
	pk::getch(); pk::getch();

}