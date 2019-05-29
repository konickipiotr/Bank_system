#pragma once
#include <memory>
#include <vector>
#include "UserRecord.hpp"
#include "History.hpp"
#include <fstream>

class DataBase
{
public:
	
	friend class AdminPanel;

	DataBase();
	~DataBase();
	void addUserToBase(std::unique_ptr<UserRecord>newUser);
	bool checkRequest(const std::string & arg, const int & col);
	void removeAccount(std::string account);
	void displayUserHistory(const std::string numberAccount);
	void displayUserHistory(const std::string  lastName, const std::string firstName);

	std::string retNrAccount(const std::string & login, const std::string & pass);
	bool checkLoginData(const std::string & login, const std::string & pass);
	std::vector<std::shared_ptr<UserRecord>> activDele(int num);
	void updateRecord(std::shared_ptr<UserRecord> & updateUser);
	std::shared_ptr<UserRecord> retUser(std::string accountNr);
	void addHistory(std::shared_ptr<History> newHist, std::string accoutnNumber);
	void printUserHistory(const std::string & numberAccount);

private:
	void loadDataBase();
	void saveBase();
	void saveAllHist();
	void loadAllHist();
	std::vector<std::unique_ptr<UserRecord> > vUsersBase{};
	std::vector < std::shared_ptr<History> > vAllHistory{};
	

};
