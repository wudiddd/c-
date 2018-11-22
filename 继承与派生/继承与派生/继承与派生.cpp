#include "jcyps1.h"

int main()
{
	vehicle a(2, 100);
	bicycle b(2, 20,1);
	automobile c(4, 100, 5);
	motorcycle d(2, 50, 1, 3, 90);
	vehicle *p[4] = {&a,&b,&c,&d};
	for (int i = 0; i < 4; i++)
	{
		p[i]->get();
	}
	system("pause");
} 