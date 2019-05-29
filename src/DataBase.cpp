#include "DataBase.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include "Functions.hpp"

DataBase::DataBase()
{
	loadDataBase();
	loadAllHist();
	if(!checkRequest("Admin",1))
	{
		vUsersBase.push_back(std::move(std::unique_ptr<UserRecord>(new UserRecord{"00000","Admin","a","a",0,true})));
	}
}


DataBase::~DataBase()
{
	saveBase();
	saveAllHist();
}

void DataBase::addUserToBase(std::unique_ptr<UserRecord> newUser)
{
	vUsersBase.push_back(std::move(newUser));
}


bool DataBase::checkRequest(const std::string & arg, const int & col)
{
	switch (col)
	{
	case 0:
	{
		for (auto& i : vUsersBase)
		{
			if (i->accountNumber == arg)
				return true;
		}
	}
	break;
	case 1:
	{
		for (auto& i : vUsersBase)
		{
			if (i->firstName == arg)
				return true;
		}
	}
	break;
	case 2:
	{
		for (auto& i : vUsersBase)
		{
			if (i->lastName == arg)
				return true;
		}
	}
	break;
	case 3:
	{
		for (auto& i : vUsersBase)
		{
			if (i->password == arg)
				return true;
		}
	}
	break;
	case 7:
	{
		for (auto& i : vUsersBase)
		{
			if (i->accountNumber == arg && i->active == false)
			{
				return true;
			}
		}
	}
	break;

	}

	return false;
}

void DataBase::removeAccount(std::string account)
{
	for (unsigned int i = 0; i < vUsersBase.size(); ++i)
	{
		if (vUsersBase[i]->accountNumber == account)
		{
			vUsersBase.erase(vUsersBase.begin() + i);
		}
	}
}

void DataBase::displayUserHistory(const std::string numberAccount)
{
	for (auto& i : vUsersBase)
	{
		if (i->accountNumber == numberAccount)
		{
			if (i->vUserHistory.empty())
			{
				std::cout << "\t Historia jest pusta" << std::endl;
				return;
			}
			for (auto& j : i->vUserHistory)
			{
				std::cout << std::endl << "\t" << j->operation << "\t FROM: " << j->userFrom << "  | " << j->accountFrom << " \t TO: " << j->userTo << "  " << j->accountTo <<"  | " << j->value <<"$" << std::endl;
			}
		}

	}
}

void DataBase::displayUserHistory(const std::string lastName, const std::string firstName)
{
	for (auto& i : vUsersBase)
	{
		if (i->lastName == lastName && i->firstName == firstName)
		{
			if (i->vUserHistory.empty())
			{
				std::cout << "\t Historia jest pusta" << std::endl;
				return;
			}
			for (auto& j : i->vUserHistory)
			{
				std::cout << std::endl << "\t" << j->operation << "\t FROM: " << j->userFrom << "  | " << j->accountFrom << " \t TO: " << j->userTo << "  " << j->accountTo << "  | " << j->value << "$" << std::endl;
			}
		}

	}
}

std::string DataBase::retNrAccount(const std::string & login, const std::string & pass)
{
	for (auto & i : vUsersBase)
	{
		if (i->lastName == login && i->password == pass)
		{
			return i->accountNumber;
		}
	}
	return "0";
}

bool DataBase::checkLoginData(const std::string & login, const std::string & pass)
{
	for (auto & i : vUsersBase)
	{
		if (i->lastName == login && i->password == pass)
		{
			return true;
		}
	}
	return false;
}

std::vector<std::shared_ptr<UserRecord>> DataBase::activDele(int num)
{
	if (num == 0)
	{
		std::vector<std::shared_ptr<UserRecord> > vActiv{};
		for (auto& i : vUsersBase)
		{
			if (i->active == false)
			{
				vActiv.push_back(std::shared_ptr<UserRecord>(new UserRecord{i->accountNumber, i->firstName, i->lastName }));
			}
		}
		return vActiv;
	}
	else if (num == 1)
	{
		std::vector<std::shared_ptr<UserRecord> > vDele{};
		for (auto& i : vUsersBase)
		{
			if (i->toDelete == true)
			{
				vDele.push_back(std::shared_ptr<UserRecord>(new UserRecord{ i->accountNumber, i->firstName, i->lastName }));
			}
		}
		return vDele;
	}
	return {};
}

void DataBase::updateRecord(std::shared_ptr<UserRecord>& updateUser)
{

	for (auto& i : vUsersBase)
	{
		if (i->accountNumber == updateUser->accountNumber)
		{
			i->firstName = updateUser->firstName;
			i->lastName = updateUser->lastName;
			i->balance = updateUser->balance;
			i->active = updateUser->active;
			i->toDelete = updateUser->toDelete;
		
		}
	}
}

std::shared_ptr<UserRecord> DataBase::retUser(std::string accountNr)
{
	std::shared_ptr<UserRecord> user = std::make_shared<UserRecord>();
	for (auto & i : vUsersBase)
	{
		if (i->accountNumber == accountNr)
		{
			user->accountNumber = i->accountNumber;
			user->firstName = i->firstName;
			user->lastName = i->lastName;
			user->password = i->password;
			user->age = i->age;
			user->balance = i->balance;
			user->active = i->active;
			user->toDelete = i->toDelete;
			for (auto & j : i->vUserHistory)
			{
				user->vUserHistory.push_back(j);
			}
		}
	}
	return user;
}

void DataBase::addHistory(std::shared_ptr<History> newHist, std::string accoutnNumber)
{
	std::string operation = newHist->operation;


	if (operation == "WPLATA")
	{
		for (auto& i : vUsersBase)
		{
			if (i->accountNumber == newHist->accountTo)
			{
				i->vUserHistory.push_back(newHist);
				break;
			}
		}
	}
	else if (operation == "PRZELEW")
	{
		for (auto& i : vUsersBase)
		{
			if (i->accountNumber == newHist->accountTo)
			{
				i->vUserHistory.push_back(newHist);
				break;
			}
		}
		for (auto& i : vUsersBase)
		{
			if (i->accountNumber == newHist->accountFrom)
			{
				i->vUserHistory.push_back(newHist);
				break;
			}
		}
	}
	else if (operation == "WYPLATA")
	{
		for (auto& i : vUsersBase)
		{
			if (i->accountNumber == newHist->accountFrom)
			{
				i->vUserHistory.push_back(newHist);
				break;
			}
		}
	}
	vAllHistory.push_back(newHist);
}

void DataBase::printUserHistory(const std::string & numberAccount)
{
	std::fstream file;
	std::string fileName;
	Functions::clearScreen();
	for (auto& i : vUsersBase)
	{
		if (i->accountNumber == numberAccount)
		{
			if (i->vUserHistory.empty())
			{
				std::cout << "\n\t Brak historii" << std::endl;
				Functions::pause();
				return;
			}
			fileName = i->firstName + "_" + i->lastName + "_hist.txt";
			file.open(fileName, std::ios::out);
			for (auto& j : i->vUserHistory)
			{
				file << j->userFrom << " | " << j->accountFrom << " | " << j->userTo << " | " << j->accountTo << " | " << j->operation << " | " << j->value << std::endl;
			}
			std::cout << "\n\tZapis do pliku poprawny. Nazwa pliku: " << fileName << std::endl;
			file.close();
			break;
		}
	}
}

void DataBase::loadDataBase()
{
	std::fstream file;
	std::string fileName = "base";
	std::string typeNew;
	std::string typeOld ;
	
	try
	{

		file.open(fileName, std::ios::in);
		if(!file.good())
		throw std::runtime_error{ "Nie ma takiego pliku. Zostanie utworzona nowa pusta baza danych" };
	}
	catch (const std::runtime_error& e) 
	{
		std::cout << e.what() << std::endl;
		Functions::pause();
		return;

	}

	file >> typeNew;
	if (file.eof())
	{
		return;
	}
	do
	{
		{
			std::unique_ptr<UserRecord> lUser(new UserRecord);
			file >> lUser->accountNumber;
			file >> lUser->firstName;
			file >> lUser->lastName;
			file >> lUser->password;
			file >> lUser->age;
			file >> lUser->balance;
			file >> lUser->active;
			file >> lUser->toDelete;
			file >> lUser->wrongLogCounter;

			do
			{
				file >> typeNew;
				if (file.eof())
				{
					break;
				}

				if (typeNew == "u")
				{
					break;
				}

				std::shared_ptr<History> lHist = std::make_shared<History>();

				std::string firstName;
				std::string lastName;
				file >> firstName;
				file >> lastName;
				std::string from = firstName + " " + lastName;
				lHist->userFrom = from;
				file >> lHist->accountFrom;
				file >> firstName;
				file >> lastName;
				from.clear();
				from = firstName + " " + lastName;
				lHist->userTo = from;
				file >> lHist->accountTo;
				file >> lHist->operation;
				file >> lHist->value;
				lUser->vUserHistory.push_back(lHist);

				file.clear();
			} while (typeNew == "h");

			vUsersBase.push_back(std::move(lUser));
		}
	} while (!file.eof());
	file.close();
}

void DataBase::saveBase()
{
	std::fstream file;
	std::string fileName = "base";
	file.open(fileName, std::ios::out);
	// if (vUsersBase.empty())
	// {
	// 	return;
	// }
	for (auto & user : vUsersBase)
	{
		file << "u " << user->accountNumber << " " << user->firstName << " " << user->lastName << " " << user->password << " " << user->age << " " << user->balance << " " << user->active << " " << user->toDelete << " " << user->wrongLogCounter << std::endl;
		if (user->vUserHistory.empty())
		{
			continue;
		
		}
		else
		{
			for (auto & j : user->vUserHistory)
			{
				file << "h " << j->userFrom << " " << j->accountFrom << " " << j->userTo << " " << j->accountTo << " " << j->operation << " " << j->value << std::endl;
			}

		}
	}
	file.close();
}


void DataBase::saveAllHist()
{
	std::fstream file;
	std::string fileName = "allHistory";
	file.open(fileName, std::ios::out);
	// if (vAllHistory.empty())
	// {
	// 	return;
	// }
	for (auto & hist : vAllHistory)
	{
		file << hist->userFrom << " " << hist->accountFrom << " " << hist->userTo << " " << hist->accountTo << " " << hist->operation << " " << hist->value << std::endl;
		
	}
	file.close();
}

void DataBase::loadAllHist()
{
	std::fstream file;
	std::string fileName = "allHistory";

	file.open(fileName, std::ios::in);
	if (!file.good())
		return;

	do
	{
        std::shared_ptr<History> lHist = std::make_shared<History>();

        std::string firstName;
        std::string lastName;
        file >> firstName;
        if (file.eof())
        {
            break;
        }
        file >> lastName;
        std::string from = firstName + " " + lastName;
        lHist->userFrom = from;
        file >> lHist->accountFrom;
        file >> firstName;
        file >> lastName;
        from.clear();
        from = firstName + " " + lastName;
        lHist->userTo = from;
        file >> lHist->accountTo;
        file >> lHist->operation;
        file >> lHist->value;
        vAllHistory.push_back(lHist);

        std::cout << lHist->userFrom << " " << lHist->accountFrom << " " << lHist->userTo << " " << lHist->accountTo << " " << lHist->operation << " " << lHist->value << std::endl;
        Functions::pause();
        file.clear();
    
	} while (!file.eof());
	file.close();

}