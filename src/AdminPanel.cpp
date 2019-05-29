#include "AdminPanel.hpp"
#include "Functions.hpp"
#include <iostream>
#include <vector>
#include "getch.hpp"

AdminPanel::AdminPanel(std::shared_ptr<DataBase> & _base)
	:base{_base}
{
}


AdminPanel::~AdminPanel()
{
}

void AdminPanel::displayAdminMenu()
{
	unsigned int pos = 0;
	
	std::vector<std::string> labels{ "Wyswietl baze danych","Wyswietl cala histrie","Wyswietl historie uzytkownika", "Wyswietl ostatnie operacje","Aktywacje","Do usuniecia","Wyjdz" };
	do 
	{
		Functions::clearScreen();
		
		pos = Functions::menuControl(labels, "Admin Panel");
		
		switch (pos)
		{
		case 0: dispalyBase();
			break;
		case 1: displayAllHistory();
			break;
		case 2: diplayUserHistory();
			break;
		case 3: displayLastOperation();
			break;
		case 4: activation();
			break;
		case 5: removeAccount();
			break;
		default:
			break;
		}	
	} while (pos != labels.size()-1);

	
}

void AdminPanel::dispalyBase()
{
	using namespace std;
	Functions::clearScreen();
	std::cout << "\n\t\t *** BAZA DANYCH ***" << std::endl;
	for (auto & i : base->vUsersBase)
	{
		std::cout<< "\t" << i->accountNumber << "  " << i->firstName << " " << i->lastName << "   PASSWORD: " << i->password << "  age: " << i->age << "  Balance: " << i->balance << "   status:";
		if (i->active)
		{
			std::cout << "ACTIVE";
		}
		else
		{
			std::cout << "DISACTIVE";
		}
		std::cout << " ";
		if (i->toDelete)
		{
			std::cout << "TO_DELETE";
		}
		else
		{
			std::cout << "******";
		}
		std::cout << " " << i->wrongLogCounter;
		std::cout << std::endl;
	}
	Functions::pause();

}

void AdminPanel::displayAllHistory()
{
	Functions::clearScreen();
	std::cout << "\n\t\t *** HISTORIA ***" << std::endl;

	
	for (auto& i : base->vUsersBase)
	{
		std::cout << "\t ----------------------------------------------------- " << std::endl;
		std::cout << "\t" << i->firstName << " " << i->lastName;
		if (i->vUserHistory.empty())
		{
			std::cout << " \t Historia jest pusta" << std::endl;

		}
		else
		{
			for (auto& j : i->vUserHistory)
			{
				std::cout << std::endl << "\t\t" << j->operation << "\t FROM: " << j->userFrom << "   " << j->accountFrom << " \t| TO: " << j->userTo << " | " << j->accountTo << "   " << j->value << "$" << std::endl;
			}

		}
	}
	Functions::pause();
}

void AdminPanel::activation()
{
	int pos = 0;
	do
	{

		std::vector<std::string> labels;
		labels.push_back(" Powrot do menu");
		std::vector<std::shared_ptr<UserRecord> > vActivation = base->activDele(0);
		for (auto i : vActivation)
		{
			std::string tempStr = i->accountNumber + "   " + i->firstName + " " + i->lastName + "    Disactive";
			labels.push_back(tempStr);
		}
		Functions::clearScreen();

		std::cout << std::endl;

		pos = Functions::menuControl(labels, "Request Activation");

		if (pos != 0)
		{
			vActivation.at(pos - 1)->active = true;
			vActivation.at(pos - 1)->wrongLogCounter = 3;
			base->updateRecord(vActivation.at(pos - 1));
		}
	} while (pos != 0);

}

void AdminPanel::removeAccount()
{
	int pos = 0;
	do
	{

		std::vector<std::string> labels;
		labels.push_back(" Powrot do menu");
		std::vector<std::shared_ptr<UserRecord> > vDelete = base->activDele(1);
		for (auto i : vDelete)
		{
			std::string tempStr = i->accountNumber + "   " + i->firstName + " " + i->lastName + "    TO_DELETE";
			labels.push_back(tempStr);
		}
		Functions::clearScreen();

		std::cout << std::endl;

		pos = Functions::menuControl(labels, "Request Delete");

		if (pos != 0)
		{
			char ch;
			std::cout << "\t Czy napewno usunac konto uzytkowniaka: " << vDelete.at(pos - 1)->firstName << " " << vDelete.at(pos - 1)->lastName << "  || (y/n)" << std::endl;
			do
			{
				ch = pk::getch();
				if (ch == 'n')
				{
					break;
				}
				else
				{
					base->removeAccount(vDelete.at(pos - 1)->accountNumber);
				}
			} while (ch != 'y' && ch != 'n');
		}
	} while (pos != 0);
}

void AdminPanel::displayLastOperation()
{
	Functions::clearScreen();
	unsigned int num;
	std::cout << "\n\tIle ostatnich operacji chcesz wyswietlic";
	std::cin >> num;
	Functions::clearScreen();
	Functions::menuHeader("DISPLAY LAST OPERATIONS");
	if (base->vAllHistory.empty())
	{
		std::cout << "\t Hisora jest pusta" << std::endl;
	}
	else
	{
		if (num < base->vAllHistory.size());
		num = base->vAllHistory.size() - 1;
		for (unsigned int i = 0; i <= num; ++i)
		{
			int sh = base->vAllHistory.size() - (i + 1);
			std::cout << "\t  "<<base->vAllHistory[sh]->operation<<"\t" << base->vAllHistory[sh]->userFrom << " " << base->vAllHistory[sh]->accountFrom << " . " << base->vAllHistory[sh]->userTo << " " << base->vAllHistory[sh]->accountTo << " | " << base->vAllHistory[sh]->value << std::endl;
		}
	}
	Functions::pause();
}

void AdminPanel::diplayUserHistory()
{
	int pos = 0;
	do
	{
		Functions::clearScreen();
		std::vector<std::string>labels{ "Sukaj po numerze konta","Szukaj po imieniu i nazwsku","Wroc do menu" };
		pos = Functions::menuControl(labels, "USER HISTORY");
		if (pos == 0)
		{
			std::cout << "\n\t podaj numer konta: ";
			std::string accountNumber;
			std::cin >> accountNumber;
			bool check = base->checkRequest(accountNumber, 0);
			if (check)
			{
				Functions::clearScreen();
				Functions::menuHeader("USER HISTORY");
				base->displayUserHistory(accountNumber);
				Functions::pause();
			}
			else
			{
				std::cout << "\n\t Niepoprawny numer konta" << std::endl;
				Functions::pause();
			}

		}
		else if (pos == 1)
		{
			std::cout << "\n\t Podaj imie: ";
			std::string fname;
			std::cin >> fname;
			std::cout << "\n\t Podaj Nazwisko: ";
			std::string lname;
			std::cin >> lname;
			bool check = base->checkRequest(fname, 1);
			bool check2 = base->checkRequest(lname, 2);
			if ((check = true) && (check2 == true))
			{
				Functions::clearScreen();
				Functions::menuHeader("USER HISTORY");
				base->displayUserHistory(lname, fname);
				Functions::pause();
			}
			else
			{
				std::cout << "\n\t Niepoprawne dane" << std::endl;
				Functions::pause();
			}
		}
	} while (pos != 2);
}