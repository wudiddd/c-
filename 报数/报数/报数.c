#include<stdio.h>
#include<stdlib.h>

typedef struct cirlist{
	int data;
	struct cirlist *next;
}CirNode, *Cirlist;

Cirlist CreateList(Cirlist L, int n)
{
	Cirlist p = NULL, s;
	L = (Cirlist)malloc(sizeof(CirNode));
	L->next = L;
	s = L;
	for (int i = 0; i < n; i++)
	{
		p = (Cirlist)malloc(sizeof(CirNode));
		s->next = p;
		s = p;
		p->data = i + 1;
	}
	p->next = L;
	return L;
}
void FindDel(Cirlist L, int n, int m, int k)
{
	Cirlist p = L->next, q = L;
	int i, j;
	for (i = 1; i < m; i++)
	{
		p = p->next;
	}
	for (i = 0; i < n; i++)
	{
		for (j = 1; j < k; j++)
		{
			q = p;
			p = p->next;
			if (p == L)
			{
				q = p;
				p = p->next;
			}
		}
		printf("��%d������������%d��\n", i + 1, p->data);
		q->next = p->next;
		free(p);
		p = q->next;
		if (p == L)
		{
			q = p;
			p = p->next;
		}
	}
}

void main()
{
	Cirlist L = NULL;
	int n, m, k;
	printf("�������ܲ���������\nm=");
	scanf("%d", &n);
	L = CreateList(L, n);
	printf("��m��ʼ����\nm=");
	scanf("%d", &m);
	printf("����k����\nk=");
	scanf("%d",&k);
	FindDel(L, n, m, k);
	system("pause");
}
