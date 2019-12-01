#include "DynamicHashTable.h"
#include <cstdio>
#include <iostream>
#include <time.h>
#include <conio.h>

using namespace std;

int main(){

	srand((unsigned)time(NULL));

	DynamicHashTable hashTable;

	hashTable.PrintHashTable();	

	int keyPressed = -1;
	int status;
	int row = -1;

	cout << endl << "Row: " << hashTable.GetKeyFromCursor() << " Value: " << hashTable.GetCurrentCursorInfo() << endl;

	while(keyPressed != 27) //ESC key
	{
		if(_kbhit())
		{
			keyPressed = (int)_getch();
			if(keyPressed == 224)
			{
				keyPressed = (int)_getch();
				switch(keyPressed)
				{
				case 75: //left arrow
					status = hashTable.GetPrevCell();
					if (status == 0){
						hashTable.PrintHashTable();
						cout << endl << "Row: " << hashTable.GetKeyFromCursor() << " Value: " << hashTable.GetCurrentCursorInfo() << endl;
					}
					else if (status == 1){
						hashTable.PrintHashTable();
						cout << endl << "Row: " << hashTable.GetKeyFromCursor() << " Value: " << hashTable.GetCurrentCursorInfo() << " Reached end of row!!" << endl; 
					}
					else if (status == -1){
						cout << endl << "Unknown error!!! Program will terminate!" << endl;
						return -1;
					}
					break;
				case 77: //right arrow		
					status = hashTable.GetNextCell();
					if (status == 0){
						hashTable.PrintHashTable();
						cout << endl << "Row: " << hashTable.GetKeyFromCursor() << " Value: " << hashTable.GetCurrentCursorInfo() << endl;
					}
					else if (status == 1){
						hashTable.PrintHashTable();
						cout << endl << "Row: " << hashTable.GetKeyFromCursor() << " Value: " << hashTable.GetCurrentCursorInfo() << " Reached end of row!!" << endl; 
					}
					else if (status == -1){
						cout << endl << "Unknown error!!! Program will terminate!" << endl;
						return -1;
					}
					break;
				case 72: //up arrow
					row = hashTable.GoDownRow();
					hashTable.PrintHashTable();
					cout << endl << "Row: " << row << " Value: " << hashTable.GetCurrentCursorInfo() << endl;
					break;
				case 80: // down arrow
					row = hashTable.GoUpRow();					
					hashTable.PrintHashTable();
					cout << endl << "Row: " << row << " Value: " << hashTable.GetCurrentCursorInfo() << endl;
					break;
				}
			}
			if(keyPressed == 112) //P
			{
				hashTable.PrintHashTable();
				cout << endl << "Row: " << hashTable.GetKeyFromCursor() << " Value: " << hashTable.GetCurrentCursorInfo() << endl;
			}
		}
	}

	return 0;
}