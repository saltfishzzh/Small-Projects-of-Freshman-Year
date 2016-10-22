#include "miner.h"

void cartoon()
{
   int x=0, y;
   clrscr();
      for(y=0; y<100; y++)
      {
         draw_bug(x, y);
         delay(10);
         if(kbhit()) // 检测敲键
            goto done;
      }
   done: ;
}
void draw_bug(int x, int y)
{
   int i,j,k,c,len=20;
	cleardevice();
	setbkcolor(10);
	setcolor(4);
	setfillstyle(1, 4);
	for(k=0;k<20;k++){
	for (i = 0; i < 20; i++){
		for (j = 0; j < 20; j++)
		{   
		    c=rand()%100;
			setfillstyle(1, c);
			/*设定每个格子的宽与高*/
			bar( 50+j*len,50+i*len,50+len+j*len,50+len+i*len);
		}
		if(k==0)
		delay(1);
	}
	delay(20);
	}
}

