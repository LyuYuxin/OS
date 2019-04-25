#pragma once
#include"manager.h"

class Shell{
	//used for interacting with users
public:
    Shell(const Manager &m);

    string getInput();

    int recongnizeInput(const vector<string> &strs);

    string callManager(int operationType, const vector<string> & strs, size_t strNum);

	vector<string> splitStr(string &str, const char pattern = ' ');

private: 

    Manager manager;
};