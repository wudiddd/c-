#include<stdio.h> 
#include<malloc.h> 
#include<stdlib.h> 
#include<conio.h> 

#define STACKINCREAMENT 10 
#define STACK_INIT_SIZE 100 

#define OK 1 
#define ERROR 0 
typedef int status;
typedef char SElemtype;

typedef struct
{
	SElemtype *base;
	SElemtype *top;
	status stacksize;
}sqstack;

status Init(sqstack *s)
{
	s->base = (SElemtype *)malloc(STACK_INIT_SIZE*sizeof(SElemtype));
	if (!s->base) exit(0);
	s->top = s->base;
	s->stacksize = STACK_INIT_SIZE;
	return OK;
}

status push(sqstack *s, SElemtype e)
{
	if (s->top - s->base >= s->stacksize)
	{
		s->base = (SElemtype *)realloc(s->base, (s->stacksize + STACKINCREAMENT)*sizeof(SElemtype));
		if (!s->base)exit(0);
		s->top = s->base + s->stacksize;
		s->stacksize += STACKINCREAMENT;
	}
	*s->top++ = e;
	return OK;
}
status pop(sqstack *s, SElemtype *e)
{
	if (s->top == s->base) return ERROR;
	*e = *--s->top;
	return OK;
}

status stackempty(sqstack *s)
{
	if (s->top == s->base)
		return OK;
	return ERROR;
}

status Gettop(sqstack *s, SElemtype e)
{
	if (s->top == s->base) return ERROR;
	e = *(s->top - 1);
	return OK;
}


status clearstack(sqstack *s)
{
	if (s->top == s->base) return ERROR;
	s->top = s->base;
	return OK;
}
status count(sqstack *s, char *str)
{
	int i=0,flag = 0;
	SElemtype e;
	while (str[i] != '\0')
	{
		switch (str[i])
		{
		case '(':push(s, str[i]); break;
		case '[':push(s, str[i]); break;
		case '{':push(s, str[i]); break;
		case ')':{pop(s, &e); if (e != '(') flag = 1; }break;
		case ']':{pop(s, &e); if (e != '[')flag = 1; }break;
		case '}':{pop(s, &e); if (e != '{') flag = 1; }break;
		default:break;
		}
		if (flag)break;
		i++;
	}
	if (!flag&&stackempty(s))
	{
		printf("括号匹配!\n");
		return ERROR;
	}
	else
		printf("括号不匹配!\n");
	return OK;
}
void main()
{
	char str[100] ;
	sqstack s;
	Init(&s);
	printf("请输入括号:\n");
	scanf("%s", str);
	count(&s, str);
	system("pause");
}
