#include "miner.h" 

int main()
{
    int x,y,xx=10,yy=10,buttons;  /* (x,y)��굱ǰλ�� (xx,yy)���ǰһλ�� */
    x_max=639;
	y_max=479;
	initGraph();  /*��ʼ��ͼ����ʾ��ʽ*/
	cartoon();
    Init_Windows();
    do {
        Init_Game();
        xmin=2;
	    xmax=x_max-1;
	    ymin=8;
	    ymax=y_max-2;
        if(init(xmin,xmax,ymin,ymax)==0 )	/*	����init�������������ʼ��*/
    	{
    		printf("Mouse or Mouse Driver Absent,P1ease install!");    		
            delay(5000);
            exit(1);
        }
    	x=10;y=10;
    	cursor(x,y);	/*	��ʮ�ֹ������Ļ���ġ�	*/
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
/*------------------------------------------ �ļ�main.c����------------------------------------------*/
