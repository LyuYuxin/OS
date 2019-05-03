#include<vector>
#include"shell.h"
#include<iostream>

using namespace std;

 int main() {
	 pcbManager p;
	 rcbManager r;
	Manager m(p, r);
	Shell shell(m);

	while (true)
	{		
		shell.processCom();
	}
		return 0;

}