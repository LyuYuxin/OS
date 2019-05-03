#pragma once
#include"manager.h"
typedef string(Manager:: *CommandType)(const vector<string> &);

class Shell{
	//used for interacting with users
public:
    Shell(const Manager &m);

	void processCom();

private: 
    string getInput();

    CommandType recongnizeInput(const vector<string> &strs);

    string callManager(CommandType command, const vector<string> &strs);

	vector<string> splitStr(string &str, const char pattern = ' ');

    Manager m_manager;
};