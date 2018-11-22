#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define ERROR 0
#define OK 0
int counter = 0;
typedef struct Node{
	int Weight;                //权值
	int parent;                //父节点的序号，为-1的是根节点
	int lchild, rchild;        //左右孩子节点的序号，为-1的是叶子节点
}HTNode, *HuffmanTree;//用来存储赫夫曼树中的所有节点

typedef struct HuffmanCode {
	char hc[10];
	HuffmanCode * next;
}HuffmanCode;  //用来存储每个叶子节点的赫夫曼编码
//根据给定的n个权值构造一棵赫夫曼树,wet中存放n个权值
int Min(HuffmanTree HT, int num)
{
	int i = 0;
	int Min;        //用来存放Weight最小且parent为-1的元素的序号
	int Min_Weight; //用来存放Weight最小且parent为-1的元素的Weight值
	//先将第一个parent为-1的元素的Weight值赋给Min_Weight,留作以后比较用。
	//注意，这里不能按照一般的做法，先直接将HT[0].Weight赋给Min_Weight，
	//因为如果HT[0].Weight的值比较小，那么在第一次构造二叉树时就会被选走，
	//而后续的每一轮选择最小权值构造二叉树的比较还是先用HT[0].Weight的值来进行判断，
	//这样又会再次将其选走，从而产生逻辑上的错误。
	while (HT[i].parent != -1)
		i++;
	Min_Weight = HT[i].Weight;
	Min = i;
	//选出Weight最小且parent为-1的元素，并将其序号赋给Min
	for (; i < num; i++)
	{
		if (HT[i].Weight < Min_Weight && HT[i].parent == -1)
		{
			Min_Weight = HT[i].Weight;
			Min = i;
		}
	}
	//选出Weight最小的元素后，将其parent置1，使得下一次比较时将其排除在外。
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
	//一棵有num个叶子节点的赫夫曼树共有2n-1个节点
	int total = 2 * num - 1;
	int i;
	HuffmanTree HT = (HuffmanTree)malloc(total * sizeof(HTNode));
	if (!HT)
	{
		printf_s("Sorry!HuffmanTree malloc failed!");
		system("pause");
		exit(ERROR);
	}
	//以下初始化序号全部用-1表示，
	//这样在编码函数中进行循环判断parent或lchild或rchild的序号时，
	//不会与HT数组中的任何一个下标混淆
	//HT[0],HT[1]...HT[n-1]中存放需要编码的n个叶子节点
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
	//HT[n],HT[n+1]...HT[2n-2]中存放的是中间构造出的每棵二叉树的根节点
	for (; i < total; i++, ht++)
	{
		ht->parent = -1;
		ht->lchild = -1;
		ht->rchild = -1;
		ht->Weight = 0;
	}
	int Min1, Min2; //用来保存每一轮选出的两个Weight最小且parent为0的节点
	//每一轮比较后选择出Min1和Min2构成一课二叉树,最后构成一棵赫夫曼树
	for (i = num; i < total; i++)
	{
		Choose_Minium(HT, i, Min1, Min2);
		HT[Min1].parent = i;
		HT[Min2].parent = i;
		//这里左孩子和右孩子可以反过来，构成的也是一棵赫夫曼树，只是所得的编码不同
		HT[i].lchild = Min1;
		HT[i].rchild = Min2;
		HT[i].Weight = HT[Min1].Weight + HT[Min2].Weight;
	}
	return HT;
}

//上述代码中调用到了Choose_Minium（）函数，它表示从集合中选出两个最小的二叉树
//从HT数组的前k个元素中选出Weight最小且parent为-1的两个，分别将其序号保存在Min1和Min2中
//这里调用到的Min（）函数
//从HT数组的前k个元素中选出Weight最小且parent为-1的元素，并将该元素的序号返回
//从叶子节点到根节点逆向求赫夫曼树HT中n个叶子节点的赫夫曼编码，并保存在HC中

HuffmanCode* HuffmanCoding(HuffmanTree HT, HuffmanCode* &HC, int NUM)	//去掉&试试
{
	HuffmanCode *p, *q = NULL;
	char code[100];
	int i, current, father;
	//用来保存指向每个赫夫曼编码串的指针
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
	//求每个字符对应的赫夫曼编码
	for (i = 0; i < NUM; i++)
	{
		current = i;							  //判断当前访问的节点
		father = HT[i].parent;					  //当前节点的父节点
		//从叶子节点遍历赫夫曼树直到根节点
		printf_s("%d\t", HT[i].Weight);
		while (father != -1)
		{
			if (HT[father].lchild == current)    //如果是左孩子，则编码为'0'
			{
				code[counter] = '0';
				printf_s("%c", code[counter++]);
			}
			else                                //如果是右孩子，则编码为'1'       
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
	printf_s("一共有多少个数:\n");
	scanf_s("%d", &NUM);
	printf_s("请依次输入权重:\n");
	for (int i = 0; i < NUM; i++)
	{
		scanf_s("%d", &wet[i]);
	}
	printf_s("霍夫曼编码为:\n");
	HT = Create_HuffmanTree(wet, NUM);
	HC = HuffmanCoding(HT, HC, NUM);
	system("pause");
	return OK;
}


