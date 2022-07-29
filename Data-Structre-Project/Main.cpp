#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <utility>
#include <algorithm>

#include "Customer.h"
#include "B_Tree_Customer.h"
#include "HashTable.h"
#include "Heap.h"

using namespace std;

const int MaxN = 101010;

Customer* ListOfCustomers[MaxN];
Customer* RICHEST = NULL;
BTree* DataBase = new BTree(3);
MinHeap* FreeIDs = new MinHeap(MaxN);
HashTable* NameTable = new HashTable();

void REGISTER(string fName, string lName, int val)
{
	if(NameTable->registered_check(fName+lName))
	{
		cout<<"Failed to register!\n\tAccount with the same name is already registered!"<<endl;
	}
	else
	{
		Customer* temp = new Customer();
		temp->id = FreeIDs->pop_minimum();
		temp->name = fName;
		temp->lastname = lName;
		temp->asset = val;
		ListOfCustomers[temp->id] = temp;
		DataBase->insert(temp);
		NameTable->add(fName+lName);
		cout<<"Registeration Successfull!,\n\t"<<temp->name<<" "<<temp->lastname<<" "<<temp->id<<" "<<temp->asset<<endl;
	}
	return;
}

void DELETE(int user_id)
{
	Customer* current = ListOfCustomers[user_id];
	if (current == NULL)
	{
		cout<<"Deletion Failed!\n\tNo user find with given id."<<endl;
	}
	else
	{
		current->active_state = false;
		ListOfCustomers[current->id] = NULL;
		NameTable->deactive((current->name+current->lastname));
		FreeIDs->insert_item(current->id);
		DataBase->remove(current);
		cout<<"Deletion Successfull!"<<endl;
	}
}

vector<string> split(string line)
{
	vector<string> res;
	string word = "";
	for(int i = 0; i < line.size(); i++)
	{
		if (line[i] == ' ')
		{
			res.push_back(word);
			word = "";
		}
		else 
		{
			word = word + line[i];
		}
	}
	if(word != "")
		res.push_back(word);
	return res;
}

void handle(string line)
{

	vector<string> inp = split(line);
	if(inp.empty())
		return;
	else if(inp[0] == "REGISTER")
	{
		if(inp.size() != 4)
		{
			cout<<"Bad Request !(REGISTER)"<<endl;
			return;
		}
		else
		{
			REGISTER(inp[1], inp[2], stoi(inp[3]));
			RICHEST = DataBase->getRichest();
		}
	}
	else if (inp[0] == "SEARCH")
	{
		if(inp.size() != 2 and inp.size() != 3)
		{
			cout<<"Bad Request !(SEARCH)"<<endl;
			return;
		}
		else
		{
			if(inp[1] == "RICHEST")
			{
				if (RICHEST == NULL)
				{
					cout<<"Failed to find the richest,\n\tNo customer found!"<<endl;
				}
				else
				{
					cout<<"The richest one is : "<<RICHEST->name<<" "<<RICHEST->lastname<<" "<<RICHEST->id<<" "<<RICHEST->asset<<endl;
				}
			}
			else if(inp[1] == "GT")
			{
				int cnt = 0;
				string res = "Customers with assets greater than (or equal to) "+inp[2]+" are : \n";
				for(int i = 0; i < MaxN; i++)
				{
					if(ListOfCustomers[i] != NULL)
					{
						if(ListOfCustomers[i]->asset >= stoi(inp[2]) and ListOfCustomers[i]->active_state == true)
						{
							string temp = "\t"+ListOfCustomers[i]->name+" "+ListOfCustomers[i]->lastname+" "+to_string(ListOfCustomers[i]->id)+" "+to_string(ListOfCustomers[i]->asset)+"\n";
							res += temp;
							cnt++;
						}
					}
				}
				if(cnt == 0)
				{
					cout<<"Failed to find anyone!,\n\tThere is not anyone with assets more than the value you asked."<<endl;
				}
				else
				{
					cout<<res<<endl;
				}
			}
			else if(inp[1] == "MINUS")
			{
				int cnt = 0;
				string res = "Customers with minus assets are : \n";
				for(int i = 0; i < MaxN; i++)
				{
					if(ListOfCustomers[i] != NULL)
					{
						if(ListOfCustomers[i]->asset < 0 and ListOfCustomers[i]->active_state)
						{
							string temp = "\t"+ListOfCustomers[i]->name+" "+ListOfCustomers[i]->lastname+" "+to_string(ListOfCustomers[i]->id)+" "+to_string(ListOfCustomers[i]->asset)+"\n";
							res += temp;
							cnt++;
						}
					}
				}
				if(cnt == 0)
				{
					cout<<"Success !,\n\tThere is not any customer with minus asset."<<endl;
				}
				else
				{
					cout<<res<<endl;
				}
			}
			else
			{
				Customer* search_res = ListOfCustomers[stoi(inp[1])];
				if(search_res == NULL)
				{
					cout<<"Failed to find!\n\tNo user find with given id."<<endl;
				}
				else
				{
					cout<<"User Found : "<<search_res->name<<" "<<search_res->lastname<<" "<<search_res->asset<<endl;
				}
			}
		}
	}
	else if (inp[0] == "DELETE")
	{
		if(inp.size() != 2)
		{
			cout<<"Bad Request !(DELETE)"<<endl;
			return;
		}
		else
		{
			if(inp[1] == "MINUS")
			{
				int cnt = 0;
				for(int i = 0; i < MaxN; i++)
				{
					if(ListOfCustomers[i] != NULL)
					{
						if(ListOfCustomers[i]->asset < 0 and ListOfCustomers[i]->active_state)
						{
							ListOfCustomers[i]->active_state = false;
							NameTable->deactive((ListOfCustomers[i]->name+ListOfCustomers[i]->lastname));
							FreeIDs->insert_item(ListOfCustomers[i]->id);
							DataBase->remove(ListOfCustomers[i]);
							ListOfCustomers[i] = NULL;
							cnt++;
						}
					}
				}
				cout<<cnt<<" number of customers deletet successfully!"<<endl;
			}
			else
			{
				DELETE(stoi(inp[1]));
			}
			RICHEST = DataBase->getRichest();
		}
	}
	else if (inp[0] == "CHANGE")
	{
		if(inp.size() != 3)
		{
			cout<<"Bad Request !(CHANGE)"<<endl;
			return;
		}
		else
		{
			int user_id = stoi(inp[1]);
			int val = stoi(inp[2]);

			Customer* current = ListOfCustomers[user_id];
			if (current == NULL)
			{
				cout<<"Change Failed!\n\tNo user find with given id."<<endl;
			}
			else
			{
				DataBase->remove(current);
				cout<<"Change Successfull,\n\t"<<current->name<<" "<<current->lastname<<" "<<current->id<<" "<<current->asset<<" Changed to -> "<<current->asset+val<<endl;
				current->asset = current->asset+val;
				DataBase->insert(current);
				RICHEST = DataBase->getRichest();
			}
		}
	}
	else if (inp[0] == "REWARD")
	{
		vector< pair<int,int> > nominates;
		int cnt = 0;
		for(int i = 0; i < MaxN; i++)
		{
			if(ListOfCustomers[i] != NULL and ListOfCustomers[i]->active_state != false)
			{
				nominates.push_back(make_pair(ListOfCustomers[i]->asset, ListOfCustomers[i]->id));
				cnt++;
			}
		}
		sort(nominates.begin(), nominates.end());
		float mean = 0;
		for(int i = 0; i < cnt/10 ; i++)
		{
			mean += nominates[i].first;
		}
		if(cnt/10 != 0)
		{
			mean = mean/(cnt/10);
		}
		int prize = 9999999;
		for(int i = 0; i < nominates.size()-1; i++)
		{
			prize = min(prize, nominates[i+1].first-nominates[i].first);
		}
		int positives = 0;
		while(positives <= nominates.size() and nominates[nominates.size()-1-positives].first >= 0)
		{
			positives ++;
		}
		if(prize < mean or positives < 1)
		{
			cout<<"REWARD Failed!\n\tThe prize amount was lower than the mean of tenth percentile or no one is positive !"<<endl;
		}
		else
		{
			int loc = rand()% ((positives * (positives-1)) / 2);
			int winner_pos = 0;
			while(loc > 0)
			{
				loc -= winner_pos;
				winner_pos ++;
			}
			Customer* winner = ListOfCustomers[nominates[nominates.size() - winner_pos].second];
			DataBase->remove(winner);
			cout<<"REWARD Successfull,\n\t"<<"WINNER : "<<winner->name<<" "<<winner->lastname<<" "<<winner->id<<" "<<winner->asset<<" Changed to -> "<<winner->asset+prize<<endl;
			winner->asset = winner->asset+prize;
			DataBase->insert(winner);
			RICHEST = DataBase->getRichest();
		}
	}
	return;
}

void load()
{
	string line;
	ifstream fin;
	fin.open("DB.txt");
	cout<<"******************************************\n\tLoad log begin : \n******************************************"<<endl;
	while (fin) 
	{
		getline(fin, line);
		handle(line);
	}
	fin.close();
	cout<<"******************************************\n\t End of load log \n******************************************"<<endl;
	cout<<"Load Successfully!"<<endl;
	return;
}

void save()
{
	ofstream fout;
	string line;
	fout.open("DB.txt", ios::app);
	ifstream fin;
	fin.open("CommandsLog.txt");
	while(fin)
	{
		getline(fin, line);
		fout << line << endl;
	}
	fin.close();
	fout.close();
	cout<<"Saved Successfully!"<<endl;
	remove("CommandsLog.txt");
	return;
}

int main()
{	
	for(int i = 0; i < 100000; i++)
	{
		FreeIDs->insert_item(i);
	}
	string line;
	ofstream fout;
	fout.open("CommandsLog.txt");
	getline(cin, line);
	while(line != "-1" and line != "exit")
	{
		if(line == "LOAD")
			load();
		else if(line == "REMOVE")
			remove("DB.txt");
		else if(line == "SAVE")
		{
			fout.close();
			save();
			fout.open("CommandsLog.txt");
		}
		else
		{
			fout << line << endl;
			handle(line);
		}
		getline(cin, line);
	}
	fout.close();
	cout<<"All Done!\n Note : All commands after last save have been saved at \"CommandsLog.txt\" !"<<endl;
	return 0;
}
