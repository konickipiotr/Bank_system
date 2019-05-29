#pragma once
#include "OperationControl.hpp"
#include <memory>
class LogIn
{
public:
	LogIn(std::shared_ptr<OperationControl>& _operation);
	~LogIn();
	std::string LogUser();

private:
	std::shared_ptr<OperationControl> operation;
};
