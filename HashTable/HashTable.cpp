// HashTable.cpp : 定义控制台应用程序的入口点。
#include"iostream"
#include<math.h>
using namespace std;

struct HashTable;
struct ListNote;
typedef struct HashTable* HashTbl;
typedef struct ListNote* Position;
typedef Position List;
int Hash(int key, int tablesize);
int NextPrime(int x);
HashTbl InitalizeTable(int TableSize);
void DestroyTable(HashTbl H);
Position Find(int key, HashTbl H);
void Insert(int key, HashTbl H);
void Delete(int key, HashTbl H);

struct ListNote
{
	int element;
	Position next;
};
struct HashTable
{
	int TableSize;
	Position* TheList;
};
int Hash(int key, int tablesize)
{
	return key%tablesize;
}
int NextPrime(int x)
{
	int flag;
	while (1)
	{
		flag = 0;
		int n = sqrt((float)x);
		for (int i = 2; i <= n; i++)
		{
			if (x%i == 0)
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
			return x;
		else
			x++;
	}
}
HashTbl InitalizeTable(int TableSize)
{
	if (TableSize <= 0)
	{
		cout << "" << endl;
		return NULL;
	}
	HashTbl table = (HashTbl)malloc(sizeof(struct HashTable));
	if (table == NULL)
		cout << "分配失败！" << endl;
	table->TableSize = NextPrime(TableSize);
	table->TheList = (Position*)malloc(sizeof(List)*table->TableSize);
	if (table->TheList == NULL)
		cout << "分配失败！" << endl;
	table->TheList[0] = (Position)malloc(table->TableSize*sizeof(struct ListNote));
	if (table->TheList[0] == NULL)
		cout << "分配失败！" << endl;
	for (int i = 0; i < table->TableSize; i++)
	{
		table->TheList[i] = table->TheList[0] + i;
		table->TheList[i]->next = NULL;
	}
	return table;
}
Position Find(int key, HashTbl H)
{
	Position p;
	List L = H->TheList[Hash(key, H->TableSize)];
	p = L->next;
	if (p == NULL)
		return L;
	else
		return p;
}
void Insert(int key, HashTbl H)
{
	Position p, NewCell;
	p = Find(key, H);
	if (p->element != key)
	{
		NewCell = (Position)malloc(sizeof(struct ListNote));
		if (NewCell == NULL)
			cout << "分配失败！" << endl;
		else
		{
			p = H->TheList[Hash(key, H->TableSize)];
			NewCell->next = p->next;
			p->next = NewCell;
			NewCell->element = key;
		}
	}
	else
	{
		cout << "没有该值！" << endl;
	}	
}
void Delete(int key, HashTbl H)
{
	Position p, NewCell;
	p = Find(key, H);
	if (p->element == key)
	{
		NewCell = H->TheList[Hash(key, H->TableSize)];
		while (NewCell->next != p)
			NewCell = NewCell->next;
		NewCell->next = p->next;
		free(p);
	}
	else
	{
		cout << "没有该值！"<<endl;
	}
}
int main()
{
	HashTbl table = InitalizeTable(10);
	Position p = NULL;
	p = Find(10, table);
	cout << p->element << endl;
	Insert(55, table);
	Insert(90, table);
	Insert(35, table);
	Insert(33, table);
	p = Find(55, table);
	cout << p->element<< endl;
	p = Find(33, table);
	cout << p->element << endl;
	Delete(33, table);
	Delete(44, table);
	system("pause");
	return 0;
}