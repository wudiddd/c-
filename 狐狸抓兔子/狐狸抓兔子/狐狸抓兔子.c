#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define N 10
#define TIME 1000

typedef struct List
{
	int date;
	int cur;
	struct List *next;
}list;
list *head = NULL;

void CreatList()
{
	list *p=NULL , *q = NULL;
	int j=1;
	for (int i = 0; i < N; i++)
	{
		q = (list*)malloc(sizeof(list));
		if (head == NULL)
		{
			head = q;
			p = q;
		}
		else
		{
			p->next= q;
			p = q;
		}
		p->cur = j;
		p->date = 1;
		j++;
	}
	p->next = head;
}



void CatchRabbit()
{
	int i, j ;
	list *p;
	p = head;
	head->date = 0;
	for (i = 2; i <=TIME; i++)
	{
		j = 0;
		while(j < i)
		{
			
			j++;
			p = p->next;
			
		}
		p->date = 0;
	}

}

void Rabbit()
{
	list *p;
	p = head;
	for (int i = 0; i < N; i++)
	{
		if (p->date == 1)
		{
			printf("%d\t", p->cur);
			p = p->next;
		}
		else
		{
			p = p->next;
		}
	}
}

void main()
{
	CreatList();
	CatchRabbit();
	Rabbit();
	system("pause");
}