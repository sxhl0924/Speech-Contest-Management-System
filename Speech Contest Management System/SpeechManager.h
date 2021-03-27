#pragma once
#include <iostream>
using namespace std;
#include <vector>
#include <map>
#include "Contestant.h"

class SpeechManager
{
public:
	SpeechManager();

	//menu
	void showMenu();

	//exit system
	void exitSystem();

	~SpeechManager();

	//initalize speech contest
	void init_Speech();

	//create contestants
	void creatContestant();

	//start the process of speech contest
	void startContest();

	//assign contestants into two groups
	void setGroup();

	//the process of speech contest
	void speechContest();

	//show the result of contest
	void showResult();

	//save the records of contest result
	void saveRecord();

	//load previous results
	void loadRecord();

	//display the record of previous contests
	void showRecord();

	//clear record
	void clearRecord();

	//store the information of records 
	map<int, vector<string>> m_Record;//int = No. of contestm vector<string> = info of 3 winners

	//indicate whether the record file is empty
	bool FileIsEmpty;


	//store IDs of 12 contestants
	vector<int> v1;
	//store IDs of 6 contestant spromoted to the 2nd round
	vector<int> v2;
	//store ID of 3 winners
	vector<int> vWinner;
	//store ID and information of winners
	map<int, Contestant> m_Contestant;
	//record the num of rounds
	int m_roundCount = 1;
	
};

