#pragma once
#include "DataBase.hpp"
#include "UserRecord.hpp"
#include <memory>

typedef std::shared_ptr<UserRecord> User;
class OperationControl
{
public:
	OperationControl(std::shared_ptr<DataBase> & _base);
	~OperationControl();
	void addUser(User & _newUser);
	bool checkRequest(const std::string & arg, const int & col);
	std::string retNrAccount(const std::string & login, const std::string & pass);
	void transfer(std::shared_ptr<History> & newHistRecod, User & currentUser);
	void updateUser(User & currentUser);
	void dispalyUserHist(std::string account);
private:
	std::shared_ptr<DataBase> base;
};
