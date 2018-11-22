#include <iostream>
using namespace std;

class vehicle
{
public:
	vehicle(int wh, int we) :wheel(wh), weight(we){};
virtual void  get()
	{
		cout << "车的属性有车轮数、重量" << endl<<endl;
	}
protected:
	int wheel;  //车轮数
	int weight; //重量
};

class bicycle :virtual public vehicle  //自行车类
{
public:
	bicycle(int wh,int we,int he) :vehicle(wh,we),height(he){}
	void get()
	{
		cout << "自行车的车轮数为：" << wheel << endl;
		cout << "自行车的重量为：" << weight << endl;
		cout << "自行车的高度为：" << height << endl<<endl;
	}
protected:
	int height;
}; 

class automobile :virtual public vehicle  //汽车类
{
public:
	automobile(int wh, int we,  int se) :vehicle(wh, we), seats(se){}
	 void get()
	{ 
		cout << "汽车的车轮数为：" << wheel << endl;
		cout << "汽车的重量为：" << weight << endl;
		cout << "汽车的座位数为：" << seats << endl<<endl;
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
		cout << "摩托车的车轮数为：" << wheel << endl;
		cout << "摩托车的重量为：" << weight << endl;
		cout << "摩托车的高度为：" << height << endl;
		cout << "摩托车的座位数为：" << seats << endl;
		cout << "摩托车的速度为：" << speed << endl;
	}
protected:
	int speed;
};