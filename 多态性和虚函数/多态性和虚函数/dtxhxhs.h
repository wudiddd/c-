# include<iostream>
//#include<math.h>
using namespace std;

class shap
{
public:
	virtual void area() = 0;
};

class Circle :public shap
{
public:
	Circle(int ra) :radius(ra){};
	void area()
	{
		double area;
		area = 3.14159*radius*radius;
		cout << "Բ�����Ϊ��" << area << endl;
		//return area;
	}
private:
	int radius;
};

class Rectangle:public shap
{
public:
	Rectangle(int le, int wi) :length(le), width(wi){};
	void area()
	{
		int area;
		area = length*width;
		cout << "���ε����Ϊ��" << area << endl;
		//return area;
	}
private:
	int length;
	int width;
};

class Triangle :public shap
{
public:
	Triangle(int l1, int l2, int l3) :length1(l1), length2(l2), length3(l3){};
	void area()
	{
		double area, p;
		p = 1 / 2 * (length1 + length2 + length3);
		area = sqrt(p*(p - length1)*(p - length2)*(p - length3));
		cout << "�����ε����Ϊ��" << area<<endl;
		//return area;
	}
private:
	int length1;
	int length2;
	int length3;
};