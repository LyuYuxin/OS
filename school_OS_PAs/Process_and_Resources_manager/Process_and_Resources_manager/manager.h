#pragma once
#include<string>
#include<map>
#include<vector>
#define PRIORITY_NUM 3
#define RUNNING 0
#define READY 1
#define BLOCKED 2
const int WRONG_INPUT = -1;

//guide information for schedulers
//-----------------------------
#define RACE_TO_CONTROL 0//抢占当前进程
#define LET_NEXT_PROCESS_RUN 1//直接令下一个优先级最高的进程执行
#define POSSIBLE_RACE_CONTROL 2//可能抢占
const int TIME_OUT = 3;
//------------------------------

//about request operation
#define REQUEST_SATIABLE 0
#define REQUEST_TOO_MUCH -1
#define REQUEST_BLOCKED -2

//about release operation
#define RELEASE_TOO_MUCH -3
#define CUR_PROCESS_DONT_CONTAIN_THE_RESOURCE -4
#define RELEASE_SUCCESS -5

using namespace std;


class RCB;
class PCB;
class pcbManager;
class rcbManager;
class Manager;
typedef string (Manager::*CommandType)(const vector<string> &);

typedef struct SresourcesUseInformation{
    int num;
    PCB* process;
	bool operator==(const SresourcesUseInformation& i)const  {
		return this->process == i.process;
	};
}SresourcesUseInformation;

class PCB{
public:
    PCB(int id, const string &name, PCB*father, int priority, int state);
    void addSon(PCB*son);
	void setStatus(int status);
	friend pcbManager;
	friend Manager;
private:
    int m_PID;
    string m_Pname;
    PCB * m_father;
    vector<PCB *> m_sons;
    int m_sonNum;
    int m_priority;
    map<int, int> m_resources;
	map<int, int> m_waitingResources;
    int m_status;
};


class RCB{
public:
    RCB(int rid, int totalnum);
	friend rcbManager;
	friend Manager;
private:
    int m_RID;
    int m_curUsableNum;
    int m_maxNum;
 
};


class pcbManager{
public:
    pcbManager();

    PCB* init();

    PCB* creat(const string &fathername, int priority, const string &name, int status = READY);

	int release(int rid, int num, PCB * process);

    PCB * getPCBPtr(const string &str);

	friend Manager;
private:
    PCB * m_runningProcess;
    int m_processNum;
	vector<vector<PCB*>> m_readyQueue;
    map<string, PCB*> m_processNameToPCBptr;
};


class rcbManager{
    public:
    rcbManager();

    int request(int rid, int num);

    int release(int rid, int num);

	friend Manager;

    private:
    vector<RCB> m_resouces;
	vector<vector<SresourcesUseInformation>> m_waitingQueue;
	map<string, int> m_name_to_num;
};


class Manager{
	//main function is to manage processes information and resources information.
	//include two modules: PCB manager and RCB manager.
	//provide interface for shell.

    public:
    Manager(const pcbManager &pcbM,const rcbManager &rcbM);

    string interface(CommandType command, const vector<string> &strs);

	CommandType getCom(const string& str);

private:
	PCB* findHighestPriorityProcess();
	
	void scheduler(int operationInformation);

	string init(const vector<string>& strs);

	string creat(const vector<string>& strs);

	string deletethem(const vector<string>& strs);

	string release(const vector<string> &strs);

	string request(const vector<string> &strs);

    string timeOut(const vector<string> &strs);

	string list(const vector<string> &strs);

	string listReady(const vector<string> &strs);

	string listBlock(const vector<string> &strs);

	string listAvailableResources(const vector<string> &strs);

	string curProcess(const vector<string> &strs);

	string printPCB(const vector<string> &);

	void killTree(PCB* process);

    pcbManager m_pmanager;
    rcbManager m_rmanager;
	map<string, CommandType> m_register;
};