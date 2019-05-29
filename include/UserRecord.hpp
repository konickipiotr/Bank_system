#pragma once
#include "History.hpp"
#include <vector>
#include <memory>

struct UserRecord
{
	std::string accountNumber;
	std::string firstName;
	std::string lastName;
	std::string password;
	int age;
	bool active{ false };
	double balance{};
	int wrongLogCounter{ 3 };	
	bool toDelete{ false };
	std::vector<std::shared_ptr<History> >vUserHistory{};
};