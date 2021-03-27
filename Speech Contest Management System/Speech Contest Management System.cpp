#include <iostream>
using namespace std;
#include "SpeechManager.h"
#include <string>
#include <ctime>


int main()
{
	//random num seed
	srand((unsigned int)time(NULL));
	SpeechManager sm;
	//test codes
	//for (map<int, Contestant>::iterator it = sm.m_Contestant.begin(); it != sm.m_Contestant.end(); it++)
	//{
	//	cout << "Contestant ID: " << it->first << " Contestant Name: " << it->second.m_Name << " Contestant Score: " << it->second.m_Score[0] << endl;
	//}
	int choice = 0;
	
	while (true)
	{
		sm.showMenu();
		cout << "please input your choice" << endl;
		cin >> choice;
		
		switch (choice)
		{
		case 1:
			sm.startContest();
			break;
		case 2:
			sm.showRecord();
			break;
		case 3:
			sm.clearRecord();
			break;
		case 0:
			sm.exitSystem();
			break;
		default:
			system("cls");
			break;
		
		}


	}
	

	system("pause");
	return 0;

}