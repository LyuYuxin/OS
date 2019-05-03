#include"shell.h"
#include"manager.h"
#include<iostream>
#include<vector>
#include<sstream>
using namespace std;

Shell::Shell(const Manager &m):m_manager(m){}

CommandType
Shell::recongnizeInput(const vector<string> &strs){
	CommandType com = m_manager.getCom(strs[0]);
	return com;
}

string Shell::getInput(){
	cout<<"shell_lyx> ";
	char str[15];
	cin.getline(str, 15);
	string input = string(str);
	return input;
}

string Shell::callManager(CommandType command, const vector<string> &strs){
    return m_manager.interface(command, strs);
}

vector<string> Shell::splitStr(string &str, const char pattern){
	vector<string> splitedStr;
	stringstream input(str);
	string temp;

	while(getline(input, temp, pattern)){
		splitedStr.push_back(temp);
	}
	
	return splitedStr;
}

void
Shell::processCom()
{

	string input = getInput();
	if (!input.size())return;
	vector<string> coms;
	coms = splitStr(input);

	string output;
	CommandType command =  recongnizeInput(coms);//recongize input type
	if (!command)output = "Wrong input!";
	else output = callManager(command, coms);
	cout << output << endl;
}