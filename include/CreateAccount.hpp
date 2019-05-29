#pragma once
#include "DataBase.hpp"
#include <memory>
#include <string>
#include <random>
#include "OperationControl.hpp"

using S_User = std::shared_ptr<UserRecord>;

class CreateAccount
{
public:
	CreateAccount(std::shared_ptr<OperationControl>& _operation);
	~CreateAccount();
	void CreatMenu();
	void fillForm(std::shared_ptr<UserRecord> & newUser);
	std::string numberAccountGenerator();
	std::string passwordGenerator();
	void summary(const std::shared_ptr<UserRecord>  & newUser);
private:
	std::shared_ptr<OperationControl> operation;
};
