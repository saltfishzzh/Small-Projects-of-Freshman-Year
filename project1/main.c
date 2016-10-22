#include "miner.h" 

int main()
{
    int x,y,xx=10,yy=10,buttons;  /* (x,y)鼠标当前位置 (xx,yy)鼠标前一位置 */
    x_max=639;
	y_max=479;
	initGraph();  /*初始化图形显示方式*/
	cartoon();
    Init_Windows();
    do {
        Init_Game();
        xmin=2;
	    xmax=x_max-1;
	    ymin=8;
	    ymax=y_max-2;
        if(init(xmin,xmax,ymin,ymax)==0 )	/*	调用init函数对鼠标器初始化*/
    	{
    		printf("Mouse or Mouse Driver Absent,P1ease install!");    		
            delay(5000);
            exit(1);
        }
    	x=10;y=10;
    	cursor(x,y);	/*	置十字光标在屏幕中心。	*/
    	do {
    		Print_Time();
    		draw_face(1);
    	    newxy(&x,&y,&buttons);
    	    if(checkWin()) gameRes = 1;
    	} while(!gameRes);
    	if (gameRes==1) 
			Update_Record(); 
    } while (!confirm(gameRes));
    end_music();
    delay(500);
    system("CLS"); 
    return 0;
}
/*------------------------------------------ 文件main.c结束------------------------------------------*/
