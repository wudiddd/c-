#include <iostream>
using namespace std;

class vehicle
{
public:
	vehicle(int wh, int we) :wheel(wh), weight(we){};
virtual void  get()
	{
		cout << "���������г�����������" << endl<<endl;
	}
protected:
	int wheel;  //������
	int weight; //����
};

class bicycle :virtual public vehicle  //���г���
{
public:
	bicycle(int wh,int we,int he) :vehicle(wh,we),height(he){}
	void get()
	{
		cout << "���г��ĳ�����Ϊ��" << wheel << endl;
		cout << "���г�������Ϊ��" << weight << endl;
		cout << "���г��ĸ߶�Ϊ��" << height << endl<<endl;
	}
protected:
	int height;
}; 

class automobile :virtual public vehicle  //������
{
public:
	automobile(int wh, int we,  int se) :vehicle(wh, we), seats(se){}
	 void get()
	{ 
		cout << "�����ĳ�����Ϊ��" << wheel << endl;
		cout << "����������Ϊ��" << weight << endl;
		cout << "��������λ��Ϊ��" << seats << endl<<endl;
	}
protected:
	int seats;
};

class motorcycle :virtual public bicycle,virtual public automobile
{
public:
	motorcycle(int wh, int we, int he, int se, int sp) :vehicle(wh, we), bicycle(wh,we,he), automobile(wh,we,se), speed(sp){}
	void get()
	{
		cout << "Ħ�г��ĳ�����Ϊ��" << wheel << endl;
		cout << "Ħ�г�������Ϊ��" << weight << endl;
		cout << "Ħ�г��ĸ߶�Ϊ��" << height << endl;
		cout << "Ħ�г�����λ��Ϊ��" << seats << endl;
		cout << "Ħ�г����ٶ�Ϊ��" << speed << endl;
	}
protected:
	int speed;
};