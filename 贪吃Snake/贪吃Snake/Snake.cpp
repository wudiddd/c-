#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>//Sleep()
#include <conio.h> //getch()
#include <time.h>//随机数
#include <mmsystem.h>//播放音乐需要
#pragma comment (lib,"winmm.lib")


#define WIDTH 640
#define HEIGHT 480
#define MAX 220  //蛇最长


typedef struct SNAKE //蛇身的一个节点
{
	int x;
	int y;
	struct SNAKE *next;
	struct SNAKE *prior;
}Snake;


typedef struct FOOD
{
	int x;
	int y;
	int flag = 0;//没有食物
	int life = 0;//蛇活着

}Food;

Snake s, *head = &s;
Food f, *food = &f;
IMAGE backImg;
MOUSEMSG msg = { 0 };

int score = 0;
int grade = 1;
int ch;  //蛇的方向
int n = 0;//蛇吃食物的个数
int speed = 140;//蛇的速度
int c;//按键方向


void welcome();
void creatMap();
char dir();
void GameInit();
int write();
int read();
void snakemove();
void changedir();
void creatfood();
void drawsnakefood();
void eatfood();
int biteself();
int cannotcrosswall();
int endgame();
void printfmessge();

//------------------------欢迎界面--------------------
void welcome()
{
	mciSendString(L"open D:\\C语言\\贪吃蛇歌曲\\甩葱歌.mp3 ", NULL, 0, NULL);
	mciSendString(L"play D:\\C语言\\贪吃蛇歌曲\\甩葱歌.mp3 repeat", 0, 0, 0);
	//加载图片,加到backImg里面
	loadimage(&backImg, L".\\image\\1.jpg", 640, 480);
	//输出图片
	putimage(0, 0, &backImg);


	setbkmode(TRANSPARENT); //设置背景风格为 透明
	settextstyle(50, 0, L"RAVIE"); //设置字体风格

	while (1)
	{
		msg = GetMouseMsg();// 获取鼠标的消息


		//鼠标的位置
		if (msg.x >= 255 && msg.x < 420 && msg.y >= 180 && msg.y < 230)
		{
			settextcolor(RGB(222, 0, 0));
			outtextxy(255, 180, L"开始游戏");
		}
		else
		{
			settextcolor(RGB(222, 200, 200));//设置字体颜色
			outtextxy(255, 180, L"开始游戏");//输出文字
		}
		switch (msg.uMsg) //获取鼠标信息
		{
		case WM_LBUTTONDOWN:  //按下左键
			if (msg.x >= 255 && msg.x < 420 && msg.y >= 180 && msg.y < 230)
			{
				return;
			}
		default:
			break;
		}
	}

}

//---------------------创建地图-----------------------
void creatMap()
{
	cleardevice();
	//initgraph(640, 480);

	//loadimage(&backImg, L".\\image\\2.jpg", 640, 480);// ---------只要加载图片，速度就不能改变------------------
	//putimage(0, 0, &backImg);
	for (int i = 0; i < 640; i++)
	{
		setlinecolor(HSLtoRGB(float(i), 1, 0.25));//HLS颜色模型，H是色相，必须是float类型，S饱和度，L是亮度
		line(i, 0, i, 479);// 渐变色背景
	}
	setbkmode(TRANSPARENT); //设置背景风格为 透明
	setfillcolor(BROWN);
	int i, j;
	for (i = 0; i < 480; i += 10)//打印上下边框
	{

		fillrectangle(i, 0, i + 10, 10);
		fillrectangle(i, 470, i + 10, 480);
	}

	for (j = 1; j < 47; j++)
	{
		for (i = 0; i < 480; i += 470)//打印左右边框
		{
			fillrectangle(i, j * 10, i + 10, (j + 1) * 10);
		}
	}
}

//------------------初始化方向------------------------
char dir()
{
	int i;
	i = rand() % 4;
	if (i == 0)
	{
		ch = 72;
	}
	if (i == 1)
	{
		ch = 75;
	}
	if (i == 2)
	{
		ch = 77;
	}
	if (i == 3)
	{
		ch = 80;
	}
	return ch;
}

//--------------------游戏初始化---------------------------
void GameInit()
{
	srand((unsigned)time(NULL));
	cleardevice();
	//初始化数据
	head->x = (480 / 4 + rand() % 480 / 2) / 10 * 10;
	head->y = (HEIGHT / 4 + rand() % HEIGHT / 2) / 10 * 10;
	head->next = NULL;
	head->prior = NULL;
	ch = dir();
}

//-------------------文件存储-----------------------
int write()
{
	FILE *fp;
	if ((fp = fopen("score.txt", "r")) == NULL)
	{
		printf("打开文件有误");
		return 0;
	}
	fscanf(fp,"%d",&score);
	fclose(fp);
	return score;
}

int read()
{
	FILE *fp;
	if ((fp = fopen("score.txt", "w")) == NULL)
	{
		printf("打开文件有误");
		return 0;
	}
	fprintf(fp, "分数 ：%d", score);
	fclose(fp);
	return score;
}
 
//---------------------蛇移动-------------------------
void snakemove()
{
	Snake *p = head;
	while (p->next != NULL)
	{
		p = p->next;
	}
	while (p->prior != NULL)
	{
		p->x = p->prior->x;
		p->y = p->prior->y;
		p = p->prior;
	}

	if (ch == 72)
		head->y -= 10;
	if (ch == 75)
		head->x -= 10;
	if (ch == 77)
		head->x += 10;
	if (ch == 80)
		head->y += 10;
	if (ch == 27)
		return;
}

//--------------------按键改变方向-------------------
void changedir()
{
	switch (c)
			{
			case 72:
				if (ch != 80)
					ch = 72;
				break;
			case 75:
				if (ch != 77)
					ch = 75;
				break;
			case 77:
				if (ch != 75)
					ch = 77;
				break;
			case 80:
				if (ch != 72)
					ch = 80;
				break;
			default:
				break;			
		}	
}

//------------随机生成食物（不能出现在蛇身上）----------------
void creatfood()
{
	food->x = ((rand() % 46) + 1) * 10;
	food->y = ((rand() % 46) + 1) * 10;
	//----------防止食物出现在蛇身上----
	Snake *p = head;
	while (p != NULL)
	{
		if (p->x == food->x&&p->y == food->y)
			creatfood();
		p = p->next;
	}
	food->flag = 1;
}

//-----------------------画出蛇和食物----------------------
void drawsnakefood()
{

	Snake *p = head;
	while (p != NULL)
	{
		if (p == head)
		{
			setlinecolor(BLACK);
			setfillcolor(BROWN);
			fillrectangle(p->x, p->y, p->x + 10, p->y + 10);
		}
		else
		{
			setfillcolor(GREEN);
			fillrectangle(p->x, p->y, p->x + 10, p->y + 10);
		}
		p = p->next;
	}
	setfillcolor(GREEN);
	fillrectangle(food->x, food->y, food->x + 10, food->y + 10);
}

//---------------------吃食物，并生成食物-----------------------
void eatfood()
{
	Snake *p = head;
	Snake *q = (Snake *)malloc(sizeof(Snake));
	q->next = NULL;
	if (head->x == food->x&&head->y == food->y)
	{
		mciSendString(L"close D:\\C语言\\贪吃蛇歌曲\\food.wav", 0, 0, 0);
		mciSendString(L"open D:\\C语言\\贪吃蛇歌曲\\food.wav ", NULL, 0, NULL);
		mciSendString(L"play D:\\C语言\\贪吃蛇歌曲\\food.wav", 0, 0, 0);
		while (p->next != NULL)
		{
			p = p->next;
		}
		p->next = q;
		q->prior = p;
		score += 10;
		n++;
		food->flag = 0;
		if (n % 5 == 0)
		{
			grade++;
			speed -= 20;
			if (speed == 20)
				speed = 100;
		}
	}
	if (food->flag == 0)
	{
		creatfood();
	}
}

//-------------------咬自己------------------------------
int biteself()
{
	Snake *p = head->next;
	while (p != NULL)
	{
		if (head->x == p->x&&head->y == p->y)
		{
			
			mciSendString(L"open D:\\C语言\\贪吃蛇歌曲\\end.wav ", NULL, 0, NULL);
			mciSendString(L"play D:\\C语言\\贪吃蛇歌曲\\end.wav", 0, 0, 0);
			return 1;
		}
		p = p->next;
	}
	return 0;
}

//------------------------撞墙--------------------------
int cannotcrosswall()
{
	if (head->x < 10 || head->x >= 470 || head->y < 10 || head->y >= 470)
	{		
		mciSendString(L"open D:\\C语言\\贪吃蛇歌曲\\end.wav ", NULL, 0, NULL);
		mciSendString(L"play D:\\C语言\\贪吃蛇歌曲\\end.wav", 0, 0, 0);
		return 1;
	}
	return 0;
}

//---------------------游戏结束-----------------------
int endgame()
{
	 if (cannotcrosswall() == 1)
	{
		cleardevice();
		loadimage(&backImg, L".\\image\\2.jpg", 640, 480);
		putimage(0, 0, &backImg);
		TCHAR s[10];
		setcolor(WHITE);
		settextstyle(35, 18, L"Calibri"); //设置字体风格
		_stprintf(s, _T("score:%d"), score);
		outtextxy(240, 120, s);
		_stprintf(s, _T("grade:%d"), grade);
		outtextxy(240, 150, s);
		outtextxy(240, 220, L"游戏结束");
		outtextxy(240, 260, L"(撞到墙了)");
		mciSendString(L"close D:\\C语言\\贪吃蛇歌曲\\甩葱歌.mp3", 0, 0, 0);
		read();
		return 1;
	}
	 else if (biteself() == 1)
	 {
		 cleardevice();
		 loadimage(&backImg, L".\\image\\2.jpg", 640, 480);
		 putimage(0, 0, &backImg);
		 setbkmode(TRANSPARENT); //设置背景风格为 透明
		 TCHAR s[10];
		 setcolor(WHITE);
		 settextstyle(35, 18, L"Calibri"); //设置字体风格
		 _stprintf(s, _T("score:%d"), score);
		 outtextxy(240, 120, s);
		 _stprintf(s, _T("grade:%d"), grade);
		 outtextxy(240, 150, s);
		 outtextxy(240, 220, L"游戏结束");
		 outtextxy(240, 260, L"咬到自己了");
		 mciSendString(L"close D:\\C语言\\贪吃蛇歌曲\\甩葱歌.mp3", 0, 0, 0);
		 read();
		 return 1;
	 }

	 else
		 return 0;
	
}

//----------------------打印菜单信息--------------------------
void printfmessge()
{
	TCHAR s[10];
	setcolor(WHITE);
	settextstyle(35, 18, L"Calibri"); //设置字体风格
	_stprintf(s, _T("score:%d"), score);
	outtextxy(500, 30, s);
	settextstyle(35, 20, L"Calibri");
	_stprintf(s, _T("grade:%d"), grade);
	outtextxy(500, 80, s);
	settextstyle(0, 0, L"Calibri");
	_stprintf(s, _T("吃食物个数:%d"), n);
	outtextxy(500, 130, s);
	settextstyle(0, 0, L"宋体");
	outtextxy(520, 200, L"操作说明：");
	outtextxy(490, 250, L"1.使用↑↓←→");
	outtextxy(490, 285, L"  控制方向");
	outtextxy(490, 315, L"2.空格键暂停:");
	outtextxy(490, 355, L"3.ESC键退出游戏");
	outtextxy(490, 395, L"4.一个食物加5分");
	outtextxy(490, 425, L"每5个食物升一级");
}

int main()
{
	int flag = 0;
	initgraph(640, 480);
	welcome();
	BeginBatchDraw();//开启批量绘图模式
	GameInit();
	while (1)
	{

		while (!kbhit())
		{
			cleardevice();
			snakemove();
			creatMap();
			drawsnakefood();
			eatfood();
			printfmessge();
			if (endgame()) break ;
			FlushBatchDraw();//绘图
			Sleep(speed);
		}

		if (endgame() == 1)break;
		c = getch();
		if (c == 27)//退出游戏
		{
			return 0;
		}
		if (c == 32)// 暂停游戏
		{
			mciSendString(L"pause D:\\C语言\\贪吃蛇歌曲\\甩葱歌.mp3", 0, 0, 0);
			getch();
			mciSendString(L"resume D:\\C语言\\贪吃蛇歌曲\\甩葱歌.mp3", 0, 0, 0);
		}
		
		changedir();
	}
	EndBatchDraw();//结束批量绘图
	getchar();
	closegraph();
}