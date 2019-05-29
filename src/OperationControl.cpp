#include "OperationControl.hpp"
#include "Functions.hpp"
#include <memory>
#include <iostream>
#include "getch.hpp"


OperationControl::OperationControl(std::shared_ptr<DataBase> & _base)
	:base{_base}
{
}


OperationControl::~OperationControl()
{
}

void OperationControl::addUser(User & _newUser)
{
	std::unique_ptr<UserRecord> newUser(new UserRecord{ _newUser->accountNumber, _newUser->firstName, _newUser->lastName, _newUser->password, _newUser->age });
	base->addUserToBase(std::move(newUser));
}


bool OperationControl::checkRequest(const std::string & arg, const int & col)
{
	return base->checkRequest(arg, col);
}

std::string OperationControl::retNrAccount(const std::string & login, const std::string & pass)
{
	if (base->checkLoginData(login, pass)) {
		return base->retNrAccount(login, pass);
	}
	else
	{
		return "0";
	}	
}

void OperationControl::transfer(std::shared_ptr<History> & newHistRecod, User & currentUser)
{
	if (newHistRecod->operation == "PRZELEW")
	{
		User toUser = base->retUser(newHistRecod->accountTo);
		toUser->balance += newHistRecod->value;
		base->addHistory(newHistRecod, currentUser->accountNumber);
		base->updateRecord(currentUser);
		base->updateRecord(toUser);
	}
	else if (newHistRecod->operation == "WPLATA" || newHistRecod->operation == "WYPLATA")
	{
		base->addHistory(newHistRecod, currentUser->accountNumber);
		base->updateRecord(currentUser);
	}
}

void OperationControl::updateUser(User & currentUser)
{
	base->updateRecord(currentUser);
}

void OperationControl::dispalyUserHist(std::string account)
{
	int pos = 0;


	std::vector<std::string> labels{ "Powrot","Wyswietl na ekranie", "Zapis do pliku" };
	do
	{
		pos = Functions::menuControl(labels, "USER HISTORY");

		switch (pos)
		{
		case 0:break;
		case 1:
		{
			base->displayUserHistory(account);
			std::cout << "\n\tNacisnij dowolny klawisz" << std::endl;
			std::cout << "\n\tPress any key to continue ...";
			pk::getch(); pk::getch();
		}
		break;
		case 2:
		{
			base->printUserHistory(account);
			std::cout << "\tNacisnij dowolny klawisz" << std::endl;
			Functions::pause();
		}
		break;
		}


	} while (pos != 0);
}