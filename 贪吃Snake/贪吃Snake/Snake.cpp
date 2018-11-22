#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>//Sleep()
#include <conio.h> //getch()
#include <time.h>//�����
#include <mmsystem.h>//����������Ҫ
#pragma comment (lib,"winmm.lib")


#define WIDTH 640
#define HEIGHT 480
#define MAX 220  //���


typedef struct SNAKE //�����һ���ڵ�
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
	int flag = 0;//û��ʳ��
	int life = 0;//�߻���

}Food;

Snake s, *head = &s;
Food f, *food = &f;
IMAGE backImg;
MOUSEMSG msg = { 0 };

int score = 0;
int grade = 1;
int ch;  //�ߵķ���
int n = 0;//�߳�ʳ��ĸ���
int speed = 140;//�ߵ��ٶ�
int c;//��������


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

//------------------------��ӭ����--------------------
void welcome()
{
	mciSendString(L"open D:\\C����\\̰���߸���\\˦�и�.mp3 ", NULL, 0, NULL);
	mciSendString(L"play D:\\C����\\̰���߸���\\˦�и�.mp3 repeat", 0, 0, 0);
	//����ͼƬ,�ӵ�backImg����
	loadimage(&backImg, L".\\image\\1.jpg", 640, 480);
	//���ͼƬ
	putimage(0, 0, &backImg);


	setbkmode(TRANSPARENT); //���ñ������Ϊ ͸��
	settextstyle(50, 0, L"RAVIE"); //����������

	while (1)
	{
		msg = GetMouseMsg();// ��ȡ������Ϣ


		//����λ��
		if (msg.x >= 255 && msg.x < 420 && msg.y >= 180 && msg.y < 230)
		{
			settextcolor(RGB(222, 0, 0));
			outtextxy(255, 180, L"��ʼ��Ϸ");
		}
		else
		{
			settextcolor(RGB(222, 200, 200));//����������ɫ
			outtextxy(255, 180, L"��ʼ��Ϸ");//�������
		}
		switch (msg.uMsg) //��ȡ�����Ϣ
		{
		case WM_LBUTTONDOWN:  //�������
			if (msg.x >= 255 && msg.x < 420 && msg.y >= 180 && msg.y < 230)
			{
				return;
			}
		default:
			break;
		}
	}

}

//---------------------������ͼ-----------------------
void creatMap()
{
	cleardevice();
	//initgraph(640, 480);

	//loadimage(&backImg, L".\\image\\2.jpg", 640, 480);// ---------ֻҪ����ͼƬ���ٶȾͲ��ܸı�------------------
	//putimage(0, 0, &backImg);
	for (int i = 0; i < 640; i++)
	{
		setlinecolor(HSLtoRGB(float(i), 1, 0.25));//HLS��ɫģ�ͣ�H��ɫ�࣬������float���ͣ�S���Ͷȣ�L������
		line(i, 0, i, 479);// ����ɫ����
	}
	setbkmode(TRANSPARENT); //���ñ������Ϊ ͸��
	setfillcolor(BROWN);
	int i, j;
	for (i = 0; i < 480; i += 10)//��ӡ���±߿�
	{

		fillrectangle(i, 0, i + 10, 10);
		fillrectangle(i, 470, i + 10, 480);
	}

	for (j = 1; j < 47; j++)
	{
		for (i = 0; i < 480; i += 470)//��ӡ���ұ߿�
		{
			fillrectangle(i, j * 10, i + 10, (j + 1) * 10);
		}
	}
}

//------------------��ʼ������------------------------
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

//--------------------��Ϸ��ʼ��---------------------------
void GameInit()
{
	srand((unsigned)time(NULL));
	cleardevice();
	//��ʼ������
	head->x = (480 / 4 + rand() % 480 / 2) / 10 * 10;
	head->y = (HEIGHT / 4 + rand() % HEIGHT / 2) / 10 * 10;
	head->next = NULL;
	head->prior = NULL;
	ch = dir();
}

//-------------------�ļ��洢-----------------------
int write()
{
	FILE *fp;
	if ((fp = fopen("score.txt", "r")) == NULL)
	{
		printf("���ļ�����");
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
		printf("���ļ�����");
		return 0;
	}
	fprintf(fp, "���� ��%d", score);
	fclose(fp);
	return score;
}
 
//---------------------���ƶ�-------------------------
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

//--------------------�����ı䷽��-------------------
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

//------------�������ʳ����ܳ����������ϣ�----------------
void creatfood()
{
	food->x = ((rand() % 46) + 1) * 10;
	food->y = ((rand() % 46) + 1) * 10;
	//----------��ֹʳ�������������----
	Snake *p = head;
	while (p != NULL)
	{
		if (p->x == food->x&&p->y == food->y)
			creatfood();
		p = p->next;
	}
	food->flag = 1;
}

//-----------------------�����ߺ�ʳ��----------------------
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

//---------------------��ʳ�������ʳ��-----------------------
void eatfood()
{
	Snake *p = head;
	Snake *q = (Snake *)malloc(sizeof(Snake));
	q->next = NULL;
	if (head->x == food->x&&head->y == food->y)
	{
		mciSendString(L"close D:\\C����\\̰���߸���\\food.wav", 0, 0, 0);
		mciSendString(L"open D:\\C����\\̰���߸���\\food.wav ", NULL, 0, NULL);
		mciSendString(L"play D:\\C����\\̰���߸���\\food.wav", 0, 0, 0);
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

//-------------------ҧ�Լ�------------------------------
int biteself()
{
	Snake *p = head->next;
	while (p != NULL)
	{
		if (head->x == p->x&&head->y == p->y)
		{
			
			mciSendString(L"open D:\\C����\\̰���߸���\\end.wav ", NULL, 0, NULL);
			mciSendString(L"play D:\\C����\\̰���߸���\\end.wav", 0, 0, 0);
			return 1;
		}
		p = p->next;
	}
	return 0;
}

//------------------------ײǽ--------------------------
int cannotcrosswall()
{
	if (head->x < 10 || head->x >= 470 || head->y < 10 || head->y >= 470)
	{		
		mciSendString(L"open D:\\C����\\̰���߸���\\end.wav ", NULL, 0, NULL);
		mciSendString(L"play D:\\C����\\̰���߸���\\end.wav", 0, 0, 0);
		return 1;
	}
	return 0;
}

//---------------------��Ϸ����-----------------------
int endgame()
{
	 if (cannotcrosswall() == 1)
	{
		cleardevice();
		loadimage(&backImg, L".\\image\\2.jpg", 640, 480);
		putimage(0, 0, &backImg);
		TCHAR s[10];
		setcolor(WHITE);
		settextstyle(35, 18, L"Calibri"); //����������
		_stprintf(s, _T("score:%d"), score);
		outtextxy(240, 120, s);
		_stprintf(s, _T("grade:%d"), grade);
		outtextxy(240, 150, s);
		outtextxy(240, 220, L"��Ϸ����");
		outtextxy(240, 260, L"(ײ��ǽ��)");
		mciSendString(L"close D:\\C����\\̰���߸���\\˦�и�.mp3", 0, 0, 0);
		read();
		return 1;
	}
	 else if (biteself() == 1)
	 {
		 cleardevice();
		 loadimage(&backImg, L".\\image\\2.jpg", 640, 480);
		 putimage(0, 0, &backImg);
		 setbkmode(TRANSPARENT); //���ñ������Ϊ ͸��
		 TCHAR s[10];
		 setcolor(WHITE);
		 settextstyle(35, 18, L"Calibri"); //����������
		 _stprintf(s, _T("score:%d"), score);
		 outtextxy(240, 120, s);
		 _stprintf(s, _T("grade:%d"), grade);
		 outtextxy(240, 150, s);
		 outtextxy(240, 220, L"��Ϸ����");
		 outtextxy(240, 260, L"ҧ���Լ���");
		 mciSendString(L"close D:\\C����\\̰���߸���\\˦�и�.mp3", 0, 0, 0);
		 read();
		 return 1;
	 }

	 else
		 return 0;
	
}

//----------------------��ӡ�˵���Ϣ--------------------------
void printfmessge()
{
	TCHAR s[10];
	setcolor(WHITE);
	settextstyle(35, 18, L"Calibri"); //����������
	_stprintf(s, _T("score:%d"), score);
	outtextxy(500, 30, s);
	settextstyle(35, 20, L"Calibri");
	_stprintf(s, _T("grade:%d"), grade);
	outtextxy(500, 80, s);
	settextstyle(0, 0, L"Calibri");
	_stprintf(s, _T("��ʳ�����:%d"), n);
	outtextxy(500, 130, s);
	settextstyle(0, 0, L"����");
	outtextxy(520, 200, L"����˵����");
	outtextxy(490, 250, L"1.ʹ�á�������");
	outtextxy(490, 285, L"  ���Ʒ���");
	outtextxy(490, 315, L"2.�ո����ͣ:");
	outtextxy(490, 355, L"3.ESC���˳���Ϸ");
	outtextxy(490, 395, L"4.һ��ʳ���5��");
	outtextxy(490, 425, L"ÿ5��ʳ����һ��");
}

int main()
{
	int flag = 0;
	initgraph(640, 480);
	welcome();
	BeginBatchDraw();//����������ͼģʽ
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
			FlushBatchDraw();//��ͼ
			Sleep(speed);
		}

		if (endgame() == 1)break;
		c = getch();
		if (c == 27)//�˳���Ϸ
		{
			return 0;
		}
		if (c == 32)// ��ͣ��Ϸ
		{
			mciSendString(L"pause D:\\C����\\̰���߸���\\˦�и�.mp3", 0, 0, 0);
			getch();
			mciSendString(L"resume D:\\C����\\̰���߸���\\˦�и�.mp3", 0, 0, 0);
		}
		
		changedir();
	}
	EndBatchDraw();//����������ͼ
	getchar();
	closegraph();
}