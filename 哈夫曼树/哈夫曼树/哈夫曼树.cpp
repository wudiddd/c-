#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define ERROR 0
#define OK 0
int counter = 0;
typedef struct Node{
	int Weight;                //Ȩֵ
	int parent;                //���ڵ����ţ�Ϊ-1���Ǹ��ڵ�
	int lchild, rchild;        //���Һ��ӽڵ����ţ�Ϊ-1����Ҷ�ӽڵ�
}HTNode, *HuffmanTree;//�����洢�շ������е����нڵ�

typedef struct HuffmanCode {
	char hc[10];
	HuffmanCode * next;
}HuffmanCode;  //�����洢ÿ��Ҷ�ӽڵ�ĺշ�������
//���ݸ�����n��Ȩֵ����һ�úշ�����,wet�д��n��Ȩֵ
int Min(HuffmanTree HT, int num)
{
	int i = 0;
	int Min;        //�������Weight��С��parentΪ-1��Ԫ�ص����
	int Min_Weight; //�������Weight��С��parentΪ-1��Ԫ�ص�Weightֵ
	//�Ƚ���һ��parentΪ-1��Ԫ�ص�Weightֵ����Min_Weight,�����Ժ�Ƚ��á�
	//ע�⣬���ﲻ�ܰ���һ�����������ֱ�ӽ�HT[0].Weight����Min_Weight��
	//��Ϊ���HT[0].Weight��ֵ�Ƚ�С����ô�ڵ�һ�ι��������ʱ�ͻᱻѡ�ߣ�
	//��������ÿһ��ѡ����СȨֵ����������ıȽϻ�������HT[0].Weight��ֵ�������жϣ�
	//�����ֻ��ٴν���ѡ�ߣ��Ӷ������߼��ϵĴ���
	while (HT[i].parent != -1)
		i++;
	Min_Weight = HT[i].Weight;
	Min = i;
	//ѡ��Weight��С��parentΪ-1��Ԫ�أ���������Ÿ���Min
	for (; i < num; i++)
	{
		if (HT[i].Weight < Min_Weight && HT[i].parent == -1)
		{
			Min_Weight = HT[i].Weight;
			Min = i;
		}
	}
	//ѡ��Weight��С��Ԫ�غ󣬽���parent��1��ʹ����һ�αȽ�ʱ�����ų����⡣
	HT[Min].parent = 1;
	return Min;
}

void Choose_Minium(HuffmanTree HT, int num, int &Min1, int &Min2)
{
	Min1 = Min(HT, num);
	Min2 = Min(HT, num);
}

HuffmanTree Create_HuffmanTree(int *wet, int num)
{
	//һ����num��Ҷ�ӽڵ�ĺշ���������2n-1���ڵ�
	int total = 2 * num - 1;
	int i;
	HuffmanTree HT = (HuffmanTree)malloc(total * sizeof(HTNode));
	if (!HT)
	{
		printf_s("Sorry!HuffmanTree malloc failed!");
		system("pause");
		exit(ERROR);
	}
	//���³�ʼ�����ȫ����-1��ʾ��
	//�����ڱ��뺯���н���ѭ���ж�parent��lchild��rchild�����ʱ��
	//������HT�����е��κ�һ���±����
	//HT[0],HT[1]...HT[n-1]�д����Ҫ�����n��Ҷ�ӽڵ�
	HuffmanTree ht = HT;
	for (i = 0; i < num; i++)
	{
		ht->parent = -1;
		ht->lchild = -1;
		ht->rchild = -1;
		ht->Weight = *wet;
		wet++;
		ht++;
	}
	//HT[n],HT[n+1]...HT[2n-2]�д�ŵ����м乹�����ÿ�ö������ĸ��ڵ�
	for (; i < total; i++, ht++)
	{
		ht->parent = -1;
		ht->lchild = -1;
		ht->rchild = -1;
		ht->Weight = 0;
	}
	int Min1, Min2; //��������ÿһ��ѡ��������Weight��С��parentΪ0�Ľڵ�
	//ÿһ�ֱȽϺ�ѡ���Min1��Min2����һ�ζ�����,��󹹳�һ�úշ�����
	for (i = num; i < total; i++)
	{
		Choose_Minium(HT, i, Min1, Min2);
		HT[Min1].parent = i;
		HT[Min2].parent = i;
		//�������Ӻ��Һ��ӿ��Է����������ɵ�Ҳ��һ�úշ�������ֻ�����õı��벻ͬ
		HT[i].lchild = Min1;
		HT[i].rchild = Min2;
		HT[i].Weight = HT[Min1].Weight + HT[Min2].Weight;
	}
	return HT;
}

//���������е��õ���Choose_Minium��������������ʾ�Ӽ�����ѡ��������С�Ķ�����
//��HT�����ǰk��Ԫ����ѡ��Weight��С��parentΪ-1���������ֱ�����ű�����Min1��Min2��
//������õ���Min��������
//��HT�����ǰk��Ԫ����ѡ��Weight��С��parentΪ-1��Ԫ�أ�������Ԫ�ص���ŷ���
//��Ҷ�ӽڵ㵽���ڵ�������շ�����HT��n��Ҷ�ӽڵ�ĺշ������룬��������HC��

HuffmanCode* HuffmanCoding(HuffmanTree HT, HuffmanCode* &HC, int NUM)	//ȥ��&����
{
	HuffmanCode *p, *q = NULL;
	char code[100];
	int i, current, father;
	//��������ָ��ÿ���շ������봮��ָ��
	HC = (HuffmanCode*)malloc(sizeof(HuffmanCode));
	if (!HC)
	{
		printf_s("Sorry!HuffmanCode malloc failed!");
		system("pause");
		exit(ERROR);
	}
	p = HC;
	for (int i = 0; i <= NUM; i++)
	{
		q = (HuffmanCode*)malloc(sizeof(HuffmanCode));
		if (!p)
		{
			printf_s("Sorry!p malloc failed!");
			system("pause");
			exit(ERROR);
		}
		q->next = NULL;
		p->next = q;
		p = q;
	}
	p = HC;
	//��ÿ���ַ���Ӧ�ĺշ�������
	for (i = 0; i < NUM; i++)
	{
		current = i;							  //�жϵ�ǰ���ʵĽڵ�
		father = HT[i].parent;					  //��ǰ�ڵ�ĸ��ڵ�
		//��Ҷ�ӽڵ�����շ�����ֱ�����ڵ�
		printf_s("%d\t", HT[i].Weight);
		while (father != -1)
		{
			if (HT[father].lchild == current)    //��������ӣ������Ϊ'0'
			{
				code[counter] = '0';
				printf_s("%c", code[counter++]);
			}
			else                                //������Һ��ӣ������Ϊ'1'       
			{
				code[counter] = '1';
				printf_s("%c", code[counter++]);
			}
			current = father;
			father = HT[father].parent;
		}
		printf_s("\n");
		p = p->next;
	}
	return HC;
}

int main()
{
	HuffmanTree HT;
	HuffmanCode* HC;
	int NUM;
	int wet[100];
	printf_s("һ���ж��ٸ���:\n");
	scanf_s("%d", &NUM);
	printf_s("����������Ȩ��:\n");
	for (int i = 0; i < NUM; i++)
	{
		scanf_s("%d", &wet[i]);
	}
	printf_s("����������Ϊ:\n");
	HT = Create_HuffmanTree(wet, NUM);
	HC = HuffmanCoding(HT, HC, NUM);
	system("pause");
	return OK;
}


