#pragma once
#include <memory>
#include "UserRecord.hpp"
#include "OperationControl.hpp"

using User = std::shared_ptr<UserRecord>;

class UserPanel
{
public:
	UserPanel(User & _user, std::shared_ptr<OperationControl> & _operation);
	~UserPanel();
	void displayUserPanel();
	void payIn();
	void transfer();
	void payOut();
	void displayMyHistory();
	void deleteAccount();
	void summary(const std::string & recipient, const std::string & rAccount, const double & amount);
	bool checkPassword();
	
private:
	User currentUser;
	std::shared_ptr<OperationControl> operation;
};
