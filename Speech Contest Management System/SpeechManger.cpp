#include "SpeechManager.h"
#include<iostream>
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <string> 
#include <fstream>
#include <vector>

SpeechManager::SpeechManager()
{
	//initialize containers and propeties
	this->init_Speech();

	//create 12 contestants
	this->creatContestant();	

	this->loadRecord();
}

void SpeechManager::showMenu()
{
	cout << "**********************************************************" << endl;
	cout << "********       Welcome to the Speech Contest!     ********" << endl;
	cout << "**********************************************************" << endl;
	cout << "******** 1. Start a new Speech Contest            ********" << endl;
	cout << "******** 2. Review the records of Speech Contest  ********" << endl;
	cout << "******** 3. Clear the records of Speech Contest   ********" << endl;
	cout << "******** 0. Log out of the Speech Contest System  ********" << endl;
	cout << "**********************************************************" << endl;
	cout << endl;

}

void SpeechManager::exitSystem()
{
	cout << "Exit successfully!" << endl;
	system("pause");
	exit(0);
}

void SpeechManager::init_Speech()
{
	this->v1.clear();
	this->v2.clear();
	this->vWinner.clear();
	this->m_Contestant.clear();
	this->m_roundCount = 1;
	this->m_Record.clear();
}

void SpeechManager::creatContestant()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "Cont_";
		name += nameSeed[i];
		//create a contestant
		Contestant ct;
		ct.m_Name = name;
		for (int j = 0; j < 2; j++)
		{
			ct.m_Score[j] = 0;
		}
		//insert IDs of 12 contestants to v1
		this->v1.push_back(i + 10001);
		//insert ID and constant into map
		this->m_Contestant.insert(make_pair(i + 10001, ct));

	}

}

void SpeechManager::startContest()
{		
	for (int i = 0; i < 2; i++)
	{
		this->setGroup();//1. Random grouping
		this->speechContest();//2. contest begins
		this->showResult();//3. show contest result
		this-> m_roundCount++;

	}

	//4. save the result of the 2nd round
	this->saveRecord();
	//reset contest and load records
	this->init_Speech();
	this->creatContestant();
	this->loadRecord();
	cout << "The whole contest ended!" << endl;
	system("pause");
	system("cls");
}

void SpeechManager::setGroup()
{
	if (this->m_roundCount == 1)
	{
		cout << "---------------------------------------------------------------------------------------" << endl;
		cout << "The 1st round: contestants are assigned into two groups according to the following order. " << endl;
		
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << "  ";
		}
		cout << endl;

	}
	else
	{
		cout << "---------------------------------------------------------------------------------------" << endl;
		cout << "The 2nd round: contestants are assigned into two groups according to the following order. " << endl;
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << "  ";
		}

		cout << endl;
	}
	
	system("pause");
}

void SpeechManager::speechContest()
{
	vector<int>v_sct;//current contestants 
	if (m_roundCount == 1)
	{
		v_sct = v1;		
		cout << "----------------------------The 1st round of contest begins!---------------------------" << endl;
		//cout << "Summary of Scores" << endl;
	}
	else
	{
		v_sct = v2;		
		cout << "----------------------------The 2nd round of contest begins!---------------------------" << endl;
		//cout << "Summary of Scores" << endl;
	}

	int cont_num = 0;//number of contestants being scored

	//create a temp container to store 2 groups of scores,key = score, value = ID,and sort by score in a decreasing trend.
	multimap<double, int, greater<double>> groupScore; 
	                                                 
	for (vector<int>::iterator it = v_sct.begin(); it != v_sct.end(); it++)
	{
		cont_num++;//update the number of contestant having been scored
		deque<double> d;//use deque to store scores 
		//cout << *it << " " << this->m_Contestant[*it].m_Name <<":  ";
		for (int i = 0; i < 10; i++)//each contestant is scored by 10 judges
		{
			double score = (rand() % 401 + 600) / 10.f; //random scores double 0~100
			//cout << score << "\t";
			d.push_back(score);
		}
		
		sort(d.begin(), d.end(), greater<double>());//sort in a decreasing trend
		d.pop_back();//remove the lowest score
		d.pop_front();//remove the highest score
		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double ave_score = sum /(double)d.size();		
		this->m_Contestant[*it].m_Score[m_roundCount-1] = ave_score;//store the ave_score in map<int, Contestant> m_Contestant; *it=contestant ID.
		//cout << "AVE: " << ave_score;
		//cout << endl;
		groupScore.insert(make_pair(ave_score, *it));//have been sorted by scores
		
		if (cont_num % 6 == 0)//6 contestants in each group, num = 6 1st group, num = 12 2nd group
		{
			
			cout << "The Ranking of Group " << cont_num/6 << ": " << endl;					
				
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{

				cout<<"No. "<<it->second <<"   Name: "<<this->m_Contestant[it->second].m_Name <<"   Score: "
					<< this->m_Contestant[it->second].m_Score[this->m_roundCount-1];//m_score[2]//two rounds of contest
				cout << endl;
			}

			//get contestants ranked top 3 
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
			{
				if (m_roundCount == 1)//the 1st round
				{
					v2.push_back((*it).second);//store IDs of top 3 contestants in each group in v2
					//cout << "The 1st round of contest ended!" << endl;
				}
				else//the 2nd round
				{
					vWinner.push_back((*it).second);//store IDs of top 3 contestants in vWinner
					//cout << "The 2nd round of contest ended!" << endl;
				}
			}
			groupScore.clear();//make sure the container is empty when it begins to store the 2nd group 
			cout << endl;
		}
	}
	if (m_roundCount == 1)
	{
		cout << "----------------------------The 1st round of contest ended!----------------------------" << endl;		
	}
	else
	{		
		cout << "----------------------------The 2nd round of contest ended!----------------------------" << endl;		
	}

	
	    
	system("pause");
}

void SpeechManager::showResult()
{
	if (m_roundCount == 1)
	{
		cout << "------------------------------- Results of the 1st Round ------------------------------" << endl;
		cout << "The following 6 contestants are promoted to the 2nd round:" << endl;
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << "No. " << *it << "  Name:" << m_Contestant[*it].m_Name << "  Score:" << m_Contestant[*it].m_Score[this->m_roundCount - 1] << endl;
		}
	}
	else 
	{
		cout << "------------------------------- Results of the 2nd Round ------------------------------" << endl;
		cout << "The top 3 contestants in the 2nd round are shown below: " << endl;		
		for (vector<int>::iterator it = vWinner.begin(); it != vWinner.end(); it++)
		{
			cout << "No. " << *it << "  Name:" << m_Contestant[*it].m_Name << "  Score:" << m_Contestant[*it].m_Score[this->m_roundCount - 1] << endl;
		}
		cout << "Congratuation! They are awarded the prize of best contestants!" << endl;
	}
	
	cout << endl;
	system("pause");
	system("cls");	
	
	this->showMenu();
}

void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("SpeechContest.csv", ios::out | ios::app);
	//write the information of 3 winners in the csv file
	for (vector<int>::iterator it = vWinner.begin(); it != vWinner.end(); it++)
	{
		ofs << *it << "," << m_Contestant[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "Records saved succesessfully!" << endl;
	this->FileIsEmpty = false;//update the status of file
		
}

void SpeechManager::loadRecord()
{
	ifstream ifs("SpeechContest.csv", ios::in);
	if (!ifs.is_open()) //fail to open file
	{
		this->FileIsEmpty = true;
		//cout << "Record File does not exsit!" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;//read one char to check whether the file is empty
	if (ifs.eof())//if the end of file reached when reading ch, the file is empty
	{
		//cout << "Record file is empty!" << endl;
		ifs.close();
		return;
	}
	//file is not empty
	this->FileIsEmpty = false;
	ifs.putback(ch);//put ch back to restore the record file

	//read the content of record file
	string data;
	int index = 0;//number of contests
	
	while (ifs >> data)//read 1 line of the file into data
	{
		//cout << data << endl;
		vector<string> v; //store the 6 string in each record
		
		int pos = -1;//store the position of ","
		int start = 0;

		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				break;
			}
			string temp = data.substr(start, pos - start);
			//cout << temp <<endl;
			v.push_back(temp);
			start = pos + 1; //update the start position after each finding 
			
		}
		this->m_Record.insert(make_pair(index, v));
		index++; 		
	}
	
	
	//for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++)
	//{

		//cout << it->first << "  The 1st prize: No. " << it->second[0] << " Score " << endl;//it->second[1] << endl;
		//cout << it->second [1] << endl;
	//}
}

void SpeechManager::showRecord()
{
	if (this->FileIsEmpty)
	{
		cout << "File does not exist or is empty!" << endl;
	}
	else
	{   
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			switch (i)
			{
			case 0:
				cout << "Records of the 1st speech contest: " << endl;
				break;
			case 1:
				cout << "Records of the 2nd speech contest: " << endl;
				break;
			case 2:
				cout << "Records of the 3rd speech contest: " << endl;
				break;
			default:
				cout << "Records of the " << i + 1 << "th speech contest: " << endl;
				break;
			}
			cout << "***"<<this->m_Record.size() <<"***"<< endl;
			cout << "The 1st prize: NO. " << this->m_Record[i][0] << "  Score " << this->m_Record[i][1] << endl;
			cout << "The 2nd Prize: NO. " << this->m_Record[i][2] << "  Score " << this->m_Record[i][3] << endl;
			cout << "The 3rd Prize: NO. " << this->m_Record[i][4] << "  Score " << this->m_Record[i][5] << endl;
			cout << endl;
		}
	}
	
	system("pause");
	system("cls");
}

void SpeechManager::clearRecord()
{
	cout << "Are you sure to clear all records?" << endl;
	cout << "1. Yes, continue" << endl;
	cout << "2. No, return" << endl;
	int choice = 0;
	cin >> choice;
	if (choice == 1)
	{
		ofstream ofs("SpeechContest.csv", ios::trunc);
		ofs.close();
		this->init_Speech();
		this->creatContestant();
		this->loadRecord();
		cout << "Records cleared succesessfully!" << endl;
	}
	system("pause");
	system("clear");
}


SpeechManager::~SpeechManager()
{
}