#pragma once
#include "DataBase.hpp"
class AdminPanel
{
public:
	AdminPanel(std::shared_ptr<DataBase> & _base);
	~AdminPanel();
	void displayAdminMenu();

	void dispalyBase();
	void displayAllHistory();
	void displayLastOperation();
	void diplayUserHistory();
	void activation();
	void removeAccount();

private:
	std::shared_ptr<DataBase> base;
};
