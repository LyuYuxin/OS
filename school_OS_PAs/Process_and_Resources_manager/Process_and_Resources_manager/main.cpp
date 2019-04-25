#include<vector>
#include"shell.h"
#include<iostream>

using namespace std;

 int main() {
	Manager m = Manager(pcbManager(), rcbManager());
	Shell shell = Shell(m);

	while (true)
	{		
		string input = shell.getInput();
		
		vector<string> result;
		result = shell.splitStr(input);
		size_t strNums = result.size();
		if (strNums == 0)continue;

		int input_type = shell.recongnizeInput(result);//recongize input type

		if(input_type != WRONG_INPUT && input_type != EXIT)
        {

			string outputStr;
            outputStr = shell.callManager(input_type, result, strNums);
			cout<<outputStr<<endl;
        }
        else if(input_type == WRONG_INPUT)
        {
			cout<<"shell> Wrong input!"<<endl;
            continue;
        }
		else break;
	}
		return 0;

}