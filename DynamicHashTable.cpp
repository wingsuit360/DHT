#include "DynamicHashTable.h"
#include <cstdio>
#include <iostream>

using namespace std;

DynamicHashTable::DynamicHashTable()
{
	InitHashTable();
	for(int i = 0; i < 50; i++)
	{
		Insert(random(101,10000));
	}
	SortTable();
	cursor = hashTable[0];
}

DynamicHashTable::~DynamicHashTable()
{
	DealocateHashTable();
}

int DynamicHashTable::Hash(int info)
{
	return info%TABLESIZE;
}

void DynamicHashTable::InitHashTable()
{
	for (int i = 0; i < TABLESIZE; i++)
	{
		hashTable[i] = NULL;
	}
}

void DynamicHashTable::DealocateHashTable()
{
	for (int i = 0; i < TABLESIZE; i++)
	{
		while(hashTable[i] != NULL)
		{
			entry = hashTable[i];
			hashTable[i] = hashTable[i]->nextCell;
			delete entry;
		}
		delete hashTable[i];
	}
}

//Inserts info and returns hash table key to where inserted.
int DynamicHashTable::Insert(int info)
{
	int key = Hash(info);

	entry = new HashCell;
	entry->nextCell = NULL;
	entry->prevCell = NULL;

	if (hashTable[key] == NULL)
	{
		entry->info = info;
		hashTable[key] = entry;
		hashTable[key]->prevCell = NULL;
	}
	else
	{
		entry->info = info;
		hashTable[key]->prevCell = entry;
		entry->nextCell = hashTable[key];
		hashTable[key] = entry;
		hashTable[key]->prevCell = NULL;
	}	

	return key;
}

//Deletes info from hash table.
bool DynamicHashTable::Delete(int info)
{
	int key;
	HashCell * cellToDelete = Search(info, key);
	
	if(cellToDelete != NULL && key != -1)
	{
		HashCell * tempCell = hashTable[key];
		while(tempCell->nextCell != cellToDelete)
			tempCell = tempCell->nextCell;
		if(tempCell->nextCell == cellToDelete)
		{
			tempCell->nextCell = cellToDelete->nextCell;
		}
		delete cellToDelete;
		return true;
	}		
	return false;
}

bool DynamicHashTable::Edit(int oldInfo, int newInfo)
{
	int key;
	HashCell * cellToEdit = Search(oldInfo, key);
	
	if(cellToEdit != NULL && key != -1)
	{
		cellToEdit->info = newInfo;
		return true;
	}		
	return false;
}

//Searches for info and returns cell and key from the hash table (cell == NULL, key == -1 if not found).
DynamicHashTable::HashCell * DynamicHashTable::Search(int info, int &key)
{
	key = Hash(info);
	HashCell * cell;

	if(hashTable[key] != NULL)
	{
		cell = hashTable[key];
		while(cell->nextCell != NULL)
		{
			if(cell->info != info)
				cell = cell->nextCell;
			else
				return cell;
		}
	}
	key = -1;
	return NULL;
}

void DynamicHashTable::PrintHashTable()
{
	HashCell * cell;
	system("cls");
	for(int key = 0; key < TABLESIZE; key++)
	{
		cell = hashTable[key];
		if(cell != NULL)
		{
			cout << key << ": " << endl;
		}
		else
			continue;
		cout << "   ";
		while(cell != NULL)
		{
			if (cell == cursor)
				cout << "*" << cell->info << "* -> ";
			else
				cout << cell->info << " -> ";
			cell = cell->nextCell;
		}
		cout << " NULL" << endl;
	}
}

int DynamicHashTable::GetKeyFromCursor()
{
	return Hash(cursor->info);
}

void DynamicHashTable::SortTable()
{
	HashCell * temp1, * temp2;

	for(int key = 0; key < TABLESIZE; key++)
	{
		for (temp1=hashTable[key];temp1!=NULL;temp1=temp1->nextCell)
		{
			for (temp2=hashTable[key];temp2!=NULL;temp2=temp2->nextCell)
			{
				int info1 = temp1->info;
				int info2 = temp2->info;

				if(info1 < info2)
				{
					temp1->info = info2;
					temp2->info = info1;
				}
			}
		}
	}
}

int DynamicHashTable::GetNextCell()
{
	if(cursor->nextCell == NULL)
	{
		return 1;
	}
	else if (cursor->nextCell != NULL)
	{
		cursor = cursor->nextCell;
		return 0;
	}
	return -1;
}

int DynamicHashTable::GetPrevCell()
{
	if(cursor->prevCell == NULL)
	{
		return 1;
	}
	else if (cursor->prevCell != NULL)
	{
		cursor = cursor->prevCell;
		return 0;
	}
	return -1;
}

int DynamicHashTable::GoDownRow()
{
	int key = GetKeyFromCursor() - 1;
	if(key > -1 && key < TABLESIZE)
	{
		cursor = hashTable[key];
		return key;
	}
	else
		return ++key;
}

int DynamicHashTable::GoUpRow()
{
	int key = GetKeyFromCursor() + 1;
	if(key > -1 && key < TABLESIZE)
	{
		cursor = hashTable[key];
		return key;
	}
	else
		return --key;
}

int DynamicHashTable::GetCurrentCursorInfo()
{
	return cursor->info;
}