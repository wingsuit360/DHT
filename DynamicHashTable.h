#define TABLESIZE 11
#define UPPERBOUND (TABLESIZE - 1)
#define random(min,max) min+(rand()%(int)((max+1)-min))

class DynamicHashTable {

private:
	struct HashCell
	{
		int info;
		struct HashCell * nextCell;
		struct HashCell * prevCell;
	} * hashTable[TABLESIZE], * entry, * cursor;

public:
	DynamicHashTable();	
	virtual ~DynamicHashTable();

public:
	HashCell * Search(int info, int &key);
	bool Delete(int info);
	bool Edit(int oldInfo, int newInfo);
	void PrintHashTable();
	int Insert(int info);
	int GetNextCell();
	int GetPrevCell();
	int GoUpRow();
	int GoDownRow();
	int GetCurrentCursorInfo();
	int GetKeyFromCursor();

private:
	void InitHashTable();
	void DealocateHashTable();
	void SortTable();
	int Hash(int info);
};