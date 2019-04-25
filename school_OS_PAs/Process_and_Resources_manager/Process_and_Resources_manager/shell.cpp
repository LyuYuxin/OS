#include"shell.h"
#include"manager.h"
#include<iostream>
#include<vector>
#include<sstream>
using namespace std;

Shell::Shell(const Manager &m):manager(m){}

int Shell::recongnizeInput(const vector<string> &strs){
	vector<string> normalizedInput = { "init", "cr", "de", "req", "rel",
	"to", "list", "pr", "exit", "cur" };
	vector<string> listCom = { "ready", "block", "res" };
	for (int i = 0; i != 10; i++)
	{
		if (strs[0] == normalizedInput[i] && i < 6)
		{
			return i;	
		}
		else if (strs[0] == normalizedInput[i] && i == 6)
		{
			for (int j = 0; j != 3; j++)
			{
				if (strs[1] == listCom[j])
				{
					return i + j;
				}
			}
			return WRONG_INPUT;
		}
		else if(strs[0] == normalizedInput[i] && i > 6)
		{
			return i + 2;
		}

	}
	return WRONG_INPUT;

}

string Shell::getInput(){
	cout<<"shell_lyx> ";
	char str[15];
	cin.getline(str, 15);
	string input = string(str);
	return input;
}

string Shell::callManager(int operationType,const vector<string> &strs, size_t strNum){
    return manager.interface(operationType, strs, strNum);
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