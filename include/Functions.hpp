#pragma once
#include "UserRecord.hpp"
#include <vector>

class Functions
{
public:
	Functions();
	~Functions();
	static int menuControl(std::vector<std::string>& labels, std::string header);
	static int menuControl(std::vector<std::string>& labels, std::string header, std::shared_ptr<UserRecord> & currRec);
	static void menuHeader(std::string header);
	static void infoFrame(std::shared_ptr<UserRecord> & currentUser);
	static bool chectText(std::string text);
    static void clearScreen();
    static void pause();
	static void keyInfo();
};
