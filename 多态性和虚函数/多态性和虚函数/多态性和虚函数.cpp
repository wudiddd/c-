#include"dtxhxhs.h"

int main()
{
	Circle a(6);
	Rectangle b(4,5);
	Triangle c(3, 4, 5);
	shap *q;
	q = &a;
	q->area();
	q = &b;
	q->area();
	q = &c;
	q->area();
	system("pause");
	return 0;
}