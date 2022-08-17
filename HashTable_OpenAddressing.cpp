#include <iostream>
#include <string>
using namespace std;

const int initialSize = 12289;

class Entry
{
public:
	int key;
	int val;
	Entry(int k, int v)
	{
		this->key = k;
		this->val = v;
	}
};

class HashTable
{
public:
	int size;
	int filled;
	Entry** data;
	HashTable()
	{
		this->filled = 0;
		this->size = initialSize;
		this->data = new Entry* [initialSize];
		for(int i = 0; i < initialSize; i++)
		{
			this->data[i] = NULL;
		}
	}
	
	void resize()
	{
		
		int table[size];
		for(int i = 0; i < size; i++)
			table[i] = data[i]->val;
		this->size = (size * 2);
		this->data = new Entry* [size];
		for(int i = 0; i < size; i++)
		{
			insert(table[i]);
		} 
	}

	void check()
	{
		if(filled == size-1)
			resize();
	}

	void insert(int x)
	{
		check();

		int hash = (x%size); // hashing is implimented implicitly by choosing proper sizes
		int pos = hash;
		while((data[pos] != NULL) and ((data[pos] != 0)))
		{
			pos+=1;
			pos%=size;
		}
		data[pos] = new Entry(hash,x);
	}

	int search(int x)
	{
		int hash = (x%size);
		int pos = hash;
		while((data[pos] != NULL) && (data[pos]->val != x))
		{
			pos+=1;
			pos%=size;
		}
		if(data[pos] == NULL)
		{
			cout<<"not found"<<endl;
			return -1;
		}
		else
		{
			return pos;
		}
	}

	void del(int x)
	{
		int pos = search(x);
		if(pos != -1)
		{
			data[pos] = 0;
		}
	}
};

int main()
{
	HashTable* T = new HashTable();
	cout<<"inserting 1"<<endl;
	T->insert(1);
	cout<<"done"<<endl;
	cout<<"inserting 2"<<endl;
	T->insert(2);
	cout<<"done"<<endl;
	cout<<"inserting 3"<<endl;
	T->insert(3);
	cout<<"done"<<endl;

	cout<<"searching for 10"<<endl;
	T->search(10);

	cout<<"searching for 3"<<endl;
	cout<<"item is at position "<<T->search(3)<<endl;

	cout<<"deleting 1"<<endl;
	T->del(1);
	cout<<"done"<<endl;

	cout<<"searching for 1"<<endl;	
	T->search(1);
	return 0;
}
