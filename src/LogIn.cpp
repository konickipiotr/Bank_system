#include "LogIn.hpp"
#include "Functions.hpp"
#include <string>
#include <iostream>
#include "getch.hpp"

LogIn::LogIn(std::shared_ptr<OperationControl>& _operation)
	:operation(_operation)
{
}

LogIn::~LogIn()
{
}

std::string LogIn::LogUser()
{
	std::string password;
	std::string login;
	std::string account;
	bool tryAgain;
	char key;
	do
	{
		tryAgain = false;
		Functions::clearScreen();
		Functions::menuHeader("Log in");

		std::cout << "\tPodaj login: _______________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
		std::cin >> login;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "\tPodaj haslo: _______________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
		std::cin >> password;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		account = operation->retNrAccount(login, password);
		if (account == "0")
		{
			std::cout << "\n\tDane niepoprawne. Czy chcesz sprobowac jeszcze raz? (y/n)" << std::endl;
			do
			{
				key = pk::getch();
				if (key == 'n')
					return account;
			} while (key != 'y');
			tryAgain = true;

		}
		else if (operation->checkRequest(account, 7))
		{
			std::cout << "\n\tDane poprawne. Konto nieaktwne" << std::endl;
			std::cout << "\tPoczekaj na zatwierdzenie przez administratowa" << std::endl;
			std::cout << "\n\tPress any key to continue ...";
			pk::getch(); pk::getch();
			return "0";

		}

	} while (tryAgain == true);
	std::cout << "\n\tDane poprawne. Konto aktywne" << std::endl;

	std::cout << "\tPress any key to continue ...";
	pk::getch(); pk::getch();
	return account;
}
