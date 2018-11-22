#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define STACKINCREAMENT 10  
#define STACK_INIT_SIZE 100 
typedef struct BiTree{
	struct BiTree *lchild = NULL;
	union{
		char ch;
		int num;
	}date;
	struct BiTree *rchild = NULL;
}bitree;
typedef struct
{
	bitree *base;
	bitree *top;
	int stacksize;
}sqstack;//二叉树栈
typedef struct
{
	char *base;
	char *top;
	int stacksize;
}sstr;//字符栈

//初始化栈
void Initsqstack(sqstack *s)
{
	s->base = (bitree *)malloc(STACK_INIT_SIZE * sizeof(bitree));//申请一个大小为STACK_INIT_SIZE*char的空间，把空间的地址给栈底
	if (!s->base)//判断是不是分配成功
		exit(1);
	s->top = s->base;//栈底指针和栈顶指针指向同一个位置，空栈
	s->stacksize = STACK_INIT_SIZE;//栈的大小（长度）=STACK_INIT_SIZE
}
void Initsstr(sstr *s)
{
	s->base = (char *)malloc(STACK_INIT_SIZE * sizeof(char));//申请一个大小为STACK_INIT_SIZE*char的空间，把空间的地址给栈底
	if (!s->base)//判断是不是分配成功
		exit(1);
	s->top = s->base;//栈底指针和栈顶指针指向同一个位置，空栈
	s->stacksize = STACK_INIT_SIZE;//栈的大小（长度）=STACK_INIT_SIZE
}

//压栈
void push(sqstack *s, bitree *e)
{
	if ((s->top - s->base) >= s->stacksize)//栈满追加空间
	{
		s->base = (bitree *)realloc(s->base, (s->stacksize + STACKINCREAMENT) * sizeof(bitree));
		if (!s->base)
			exit(1);
		s->top = s->base + s->stacksize;
		s->stacksize += STACKINCREAMENT;
	}
	*s->top++ = *e;
}

//弹栈
char pop(sqstack *s)
{
	if (s->base == s->top)
	{
		printf("空栈");
		exit(0);
	}
	s->top--;
	char e = s->top->date.ch;
	return e;
}

//取栈顶元素
bitree GetTop(sqstack *s)
{
	bitree e;
	if (s->base == s->top)
	{
		printf("空栈");
		exit(0);
	}
	e = *(s->top - 1);
	return e;
}

//判断空栈
int stackempty(sqstack *s)
{
	if (s->top == s->base)
		return 0;
	return 1;
}

//创建二叉树
bitree CreatBiTree(char a[])
{
	bitree *t, *root = NULL;
	char *p = a;//p指针指向a
	while (*p != '\0')
	{
		int s = 0;
		while (*p >= 48 && *p <= 57)
		{
			s = s * 10 + *p - '0';
			p++;
		}//如果是数字，且是大于10的，将进行字符串到数值的转换
		t = (bitree*)malloc(sizeof(bitree));
		if (s != 0)
		{
			t->date.num = s;
			p--;
		}
		else
		{
			t->date.ch = *p;
		}
		t->rchild = NULL;
		t->lchild = NULL;
		if (root == NULL)
		{
			root = t;
		}
		else if (root->date.num >= 0 && root->date.num <= 1000)//判断根结点的是数据还是字符
		{
			t->lchild = root;
			root = t;
		}
		else if (s != 0)//当前是数字
		{
			bitree *tmp = root;
			while (tmp->rchild != NULL)
			{
				tmp = tmp->rchild;
			}
			tmp->rchild = t;
		}
		else//否则就是运算符
		{
			switch (t->date.ch)
			{
			case '+':case'-'://低级运算符，运算符成为新的根结点，现在的根结点成为左孩子
				t->lchild = root;
				root = t;
				break;
			case'*':case '/'://高级运算符，运算符成为现在根结点的右孩子，以前的有孩子变成运算符的左孩子
				t->lchild = root->rchild;
				root->rchild = t;
			}
		}
		p++;
	}
	return *root;
}

//后序遍历表达式
int hxbl(bitree *root, sstr st)
{
	bitree cur, *pre = NULL;
	sqstack s;
	int n = 0;//累计得出后序表达式中，运算符与数字的个数
	Initsqstack(&s);
	push(&s, root);
	printf("输入表达式的后序表达为：");
	while (stackempty(&s) != 0)
	{
		cur = GetTop(&s);
		if ((cur.rchild == NULL&&cur.lchild == NULL) ||
			(pre != NULL && (pre->date.ch == cur.lchild->date.ch || pre->date.ch == cur.rchild->date.ch)))
			//当没有左右孩子，或者左右孩子已经打印过
		{
			if (cur.date.num >= 0 && cur.date.num <= 1000)
			{
				printf("%d\t", cur.date.num);
				*st.top++ = cur.date.num;
			}
			else
			{
				printf("%c\t", cur.date.ch);
				*st.top++ = cur.date.ch;
			}
			n++;//每进行一次打印，个数+1
			pop(&s);
			pre = (bitree*)malloc(sizeof(bitree));
			*pre = cur;
		}
		else
		{
			if (cur.rchild != NULL)
				push(&s, cur.rchild);
			if (cur.lchild != NULL)
				push(&s, cur.lchild);
		}
	}
	return n;
}
//表达式求值
void bdsqz(sstr st, int n)
{
	char *p = st.base;
	int a[100], i = 0, s = 0;
	//用数组a来存储后序表达式中的数字
	for (int j = 0; j < n; j++)
	{
		if (*p != '+' && *p != '-' && *p != '*' && *p != '/')
		{
			a[i++] = *p;
		}
		else
		{
			switch (*p)
			{
			case '+':
				a[i - 2] = a[i - 1] + a[i - 2];
				s = a[i - 2];
				break;
			case '-':
				a[i - 2] = a[i - 2] - a[i - 1];
				s = a[i - 2];
				break;
			case '*':
				a[i - 2] = a[i - 1] * a[i - 2];
				s = a[i - 2];
				break;;
			case '/':
				a[i - 2] = a[i - 2] / a[i - 1];
				s = a[i - 2];
				break;
			}
			i = i - 1;
		}
		p++;
	}
	printf("\n表达式的值为：%d\n", s);
}
void main()
{
	char a[100];
	int *n;
	printf("请输入表达式（小于100个字符）:");
	scanf("%s", &a);
	bitree root = CreatBiTree(a);
	sstr st;//栈st，字符栈，接收后序表达式
	Initsstr(&st);
	bdsqz(st, hxbl(&root, st));
	system("pause");
}


