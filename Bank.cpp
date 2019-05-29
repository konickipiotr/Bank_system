#include "CreateAccount.hpp"
#include "Functions.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include "OperationControl.hpp"
#include "LogIn.hpp"
#include "AdminPanel.hpp"
#include "UserPanel.hpp"

int main()
{
	int x;
	std::shared_ptr<DataBase> base = std::make_shared<DataBase>();
	std::shared_ptr<OperationControl> operation = std::make_shared<OperationControl>(base);
	std::vector<std::string> labels{ "Zaloz konto","Zaloguj","Zakoncz" };
	do
	{

		std::cin.clear();
		x = Functions::menuControl(labels, "Bank");
		
		if (x == 0)
		{
			std::unique_ptr<CreateAccount> newAccount(new CreateAccount(operation));
			newAccount->CreatMenu();
		}
		else if (x == 1)
		{
			std::unique_ptr<LogIn> logIn = std::make_unique<LogIn>(operation);
			std::string accountNr = logIn->LogUser();
			if (accountNr == "0") {
				
			}
			else if (accountNr == "00000")
			{
				std::cout << "admin";
				std::unique_ptr<AdminPanel> adminPanel(new AdminPanel(base));
				adminPanel->displayAdminMenu();
			}
			else
			{
				std::shared_ptr<UserRecord> user = std::make_shared<UserRecord>();
				user = base->retUser(accountNr);
				std::unique_ptr<UserPanel> currentUser(new UserPanel(user, operation));
				currentUser->displayUserPanel();
			}
		}
	} while (x != 2);
    return 0;
}
