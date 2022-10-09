#include"libOne.h"
#include"KUSAMURA.h"
void gmain()
{
	window(800, 800);
	KUSAMURA kusamura;
	while (notQuit)
	{
		clear(0,60,120);
		kusamura.chousa();
		kusamura.miseru();
	}
}
