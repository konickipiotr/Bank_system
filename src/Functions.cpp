#include "Functions.hpp"
#include <iostream>
#include <string>
#include <cctype>
#include<unistd.h>
#include<termios.h>
#include "getch.hpp"

using namespace std;

Functions::Functions()
{
}


Functions::~Functions()
{
}

void Functions::clearScreen()
{
    #ifdef WINDOWS
        std::system("cls");
    #else
        std::system ("clear");
    #endif
}

void Functions::pause()
{
    std::cin.get();
}

void Functions::keyInfo()
{
	cout<<"\n\n\t [ w ] - UP\t[ s ] - down\t[ a ] - accept\n";
}

int Functions::menuControl(std::vector<std::string>& labels, std::string header)
{
	const int MENUSIZE = labels.size();
	vector<char> checkBox{};
	for (int i = 0; i < MENUSIZE; ++i)
	{
		checkBox.push_back(' ');
	}
	int pos = 0;
	checkBox.at(pos) = 'X';
	do
	{

		Functions::clearScreen();
		menuHeader(header);
		
		for (int i = 0; i < MENUSIZE; ++i)
		{
			cout << "\t[" << checkBox.at(i) << "]\t" << labels.at(i) << endl;
		}

		Functions::keyInfo();
		char ch = pk::getch();

		switch (ch)
		{
		case 's':
		{
			if (pos < checkBox.size() - 1)
			{
				checkBox.at(pos) = ' ';
				pos++;
				checkBox.at(pos) = 'X';
			}
		}
		break;
		case 'w':
		{
			if (pos > 0)
			{
				checkBox.at(pos) = ' ';
				pos--;
				checkBox.at(pos) = 'X';
			}
		}
		break;
		case 'a':
		{
			return pos;
		}
		default:
			break;
		}

	} while (true);
}

int Functions::menuControl(std::vector<std::string>& labels, std::string header, std::shared_ptr<UserRecord>& currRec)
{
	const int MENUSIZE = labels.size();
	vector<char> checkBox{};
	for (int i = 0; i < MENUSIZE; ++i)
	{
		checkBox.push_back(' ');
	}
	int pos = 0;
	checkBox.at(pos) = 'X';
	do
	{

		Functions::clearScreen();
		menuHeader(header);
		infoFrame(currRec);

		for (int i = 0; i < MENUSIZE; ++i)
		{
			cout << "\t[" << checkBox.at(i) << "]\t" << labels.at(i) << endl;
		}
		char ch = pk::getch();

		switch (ch)
		{
		case 's':
		{
			if (pos < checkBox.size() - 1)
			{
				checkBox.at(pos) = ' ';
				pos++;
				checkBox.at(pos) = 'X';
			}
		}
		break;
		case 'w':
		{
			if (pos > 0)
			{
				checkBox.at(pos) = ' ';
				pos--;
				checkBox.at(pos) = 'X';
			}
		}
		break;
		case 'a':
		{
			return pos;
		}
		default:
			break;
		}

	} while (true);
}

void Functions::menuHeader(std::string header)
{
	cout << "\n\t\t *** " << header << " ***" << endl;
	cout << "\t\t----------------------" << endl << endl;

}

void Functions::infoFrame(std::shared_ptr<UserRecord>& currentUser)
{
	using namespace std;
	cout << "\t-------------------------" << endl;
	cout << "\t" << currentUser->firstName << " " << currentUser->lastName << std::endl;
	cout << "\t-------------------------" << endl << endl;
	cout << "\tAge: " << currentUser->age << endl << endl;
	cout << "\t********************************" << endl;
	cout << "\tAccount Number: " << currentUser->accountNumber << endl;
	cout << "\tBalance: " << currentUser->balance << "$" << endl;
	cout << "\t********************************" << endl << endl;

}

bool Functions::chectText(std::string text)
{
	for (int i = 0; i < text.size(); ++i)
	{
		if (isdigit(text[i]))
		{
			return false;
		}
	}
	return true;
}