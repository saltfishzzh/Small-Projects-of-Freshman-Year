#include "miner.h"


char Trans_Num[10];//��������ת�����ַ�������ʱ���� 

clock_t BeginTime;
int TimeCount,LastTime;
int record[Record_Size];

void Paint_Menu_Group(int num)//���ƶ����Ĳ˵������� 
{
	Menu=Menus[num];
	setfillstyle(SOLID_FILL,DARKGRAY);
	//setcolor(BLACK);
	bar(Menu.startx,Menu.starty,Menu.startx+Menu_Length,Menu.starty+Menu_Height); 
	setcolor(WHITE);
	rectangle(Menu.startx,Menu.starty,Menu.startx+Menu_Length,Menu.starty+Menu_Height); 
	outtextxy(Menu.startx+5,Menu.starty+5,Menu.name);
}
 
void Init_Record()
{
	int i;
	for (i=0;i<Record_Size;i++)
		record[i]=INF;
}

void Update_Record()
{
	int i,j,T=(clock()-BeginTime)/CPS;
	for (i=0;i<Record_Size;i++)
	if (T<record[i])
	{
		for (j=Record_Size-1;j>i;j--)
			record[j]=record[j-1];
		record[i]=T;
		break;
	}
	for (i=0;i<Record_Size;i++)
	{
		if (record[i]==INF)
		{
			strcpy(Windows[0].word[i]+5,"N/A");
		}
		else
		{
			itoa(record[i],Trans_Num,10);
			strcpy(Windows[0].word[i]+5,Trans_Num);
		}
	}
}

void Open_Menu_Group(int num)//�򿪲˵��� 
{
	int i;
	if (num<0 || num>=Menu_Cnt) return;
	Menus[num].open=1;
	Menu=Menus[num];
	for (i=0;i<Menu.size;i++)
	{
		//outtextxy(STARTX,STARTY+50*i,"You win the game , play again (Y/N)?");
		//setcolor(BLACK);
		setfillstyle(SOLID_FILL,DARKGRAY);
		bar(Menu.startx,Menu.starty+(i+1)*Menu_Height,Menu.startx+Menu_Length,Menu.starty+(i+2)*Menu_Height); 
		setcolor(WHITE);
		rectangle(Menu.startx,Menu.starty+(i+1)*Menu_Height,Menu.startx+Menu_Length,Menu.starty+(i+2)*Menu_Height);		
		outtextxy(Menu.startx+4,Menu.starty+(i+1)*Menu_Height+4,Menu.option[i]);
	}
}

void Close_Menu_Group(int num)//�رղ˵��� 
{
	int i;
	if (num<0 || num>=Menu_Cnt) return;
	Menus[num].open=0;
	//putimage(0,0,BackGround,COPY_PUT);
	//system("CLS");
	setfillstyle(BLACK,DARKGRAY);
	bar(Menus[0].startx,Menus[0].starty+Menu_Height+1,STARTX+SIZEX*COL,STARTY-1);
	drawTable();
	for (i=0;i<Menu_Cnt;i++)
	    Paint_Menu_Group(i);
}

void Switch_Menu_Group(int num)//�л�ĳ�˵����Ŀ��� 
{
	if (Menus[num].open)
		Close_Menu_Group(num);
	else
		Open_Menu_Group(num);
}

void Init_Windows()
{
	int i;
	memset(Windows,0,sizeof(Windows)); 
	Init_Record();
	strcpy(Windows[0].Title,"Record");
	strcpy(Windows[1].Title,"Help");
	strcpy(Windows[2].Title,"About");
	for (i=0;i<Window_Cnt;i++) 
	{
		Windows[i].startx=STARTX+SIZEX*COL+20;
		Windows[i].starty=STARTY;
		Windows[i].endx=STARTX+SIZEX*COL+240;
		Windows[i].endy=STARTY+SIZEY*ROW;
		Windows[i].open=0; 
	}
	
	/*Init Record Begin*/
	strcpy(Windows[0].word[0],"1.   N/A");
	strcpy(Windows[0].word[1],"2.   N/A");
	strcpy(Windows[0].word[2],"3.   N/A");
	/*Init Record End*/
	
	/*Init Help Begin*/
	strcpy(Windows[1].word[0],"  Number in blocks stands");
	strcpy(Windows[1].word[1],"for the number of mines in");
	strcpy(Windows[1].word[2],"the nearby 8 blocks.");
	strcpy(Windows[1].word[3],"  Using the left button to");
	strcpy(Windows[1].word[4],"dig out a block.");
	strcpy(Windows[1].word[5],"  Using the right button to");
	strcpy(Windows[1].word[6],"flag a block.");
	strcpy(Windows[1].word[7],"  Have FUN!");
	/*Init Help End*/
	
	/*Init About Begin*/
	strcpy(Windows[2].word[0],"Author:");
	strcpy(Windows[2].word[1],"Chen Shihan");
	strcpy(Windows[2].word[2],"Zhang Zhuohao");
	strcpy(Windows[2].word[3],"Yi Mingqi");
	/*Init About End*/
}

void Close_Window(int num)
{
	if (num<0 || num>=Window_Cnt) return;
	Windows[num].open=0;
	tmp_window=Windows[num];
	setfillstyle(SOLID_FILL,BLACK);
	bar(tmp_window.startx,tmp_window.starty,tmp_window.endx,tmp_window.endy);
}

void Close_Other_Windows(int num)
{
	int i;
	for (i=0;i<Window_Cnt;i++)
	if (i!=num)
		Close_Window(i);
}

void Open_Window(int num)
{
	int i; 
	if (num<0 || num>=Window_Cnt) return;
	Close_Other_Windows(num);
	Windows[num].open=1;	
	tmp_window=Windows[num];
	setcolor(WHITE);
	rectangle(tmp_window.startx,tmp_window.starty,tmp_window.endx,tmp_window.endy);
	setfillstyle(SOLID_FILL,BLUE);
	setcolor(WHITE);
	bar(tmp_window.startx+1,tmp_window.starty+1,tmp_window.endx-1,tmp_window.starty+Title_Height);
	outtextxy(tmp_window.startx+5,tmp_window.starty+5,tmp_window.Title); 
	for (i=0;i<Word_Row;i++)
		outtextxy(tmp_window.startx+5,tmp_window.starty+Title_Height+5+i*Letter_Height,tmp_window.word[i]);
}

void Switch_Window(int num)
{
	if (Windows[num].open)
		Close_Window(num);
	else
		Open_Window(num);
}

int Click_Menu(int men,int opt)//����˵��е�ĳ��ѡ�� 
{
	switch(men)
	{
		case 0:
			switch(opt)
			{
				case 0:					//NewGame
					newGame();
				    flag_cnt=0;
				    draw_loading();
					BeginTime=clock();
					LastTime=-1;
					break;
					
				case 1:					//BestRecords
					Switch_Window(0); 
					break;
					
				case 2:					//Exit
					return 1;
					break;
			}
			break;
			
		case 1:
			switch(opt)
			{
				case 0:					//Help
					Switch_Window(1); 
					break;
							
				case 1:					//About
					Switch_Window(2); 
					break;
			}
			break;
	}
	return 0;
} 

void Close_Other_Menus(int num)//�رճ���num֮������в˵��� 
{
	int i;
	for (i=0;i<Menu_Cnt;i++)
	if (i!=num)
		Close_Menu_Group(i);
	if (Menus[num].open)
		Open_Menu_Group(num);
}

void Init_Menus()
{
	int i;
	
	strcpy(Menus[0].name,"Game");
	strcpy(Menus[1].name,"Help");
	for (i=0;i<Menu_Cnt;i++)
	{
	    Menus[i].startx=STARTX+i*Menu_Length;
	    Menus[i].starty=STARTY-2*Menu_Height;
	    Menus[i].open=0;
	    Paint_Menu_Group(i);
	}
	Menus[0].size=3;
	strcpy(Menus[0].option[0],"NewGame");
	strcpy(Menus[0].option[1],"Record");
	strcpy(Menus[0].option[2],"Exit");
	
	Menus[1].size=2;
	strcpy(Menus[1].option[0],"Help");
	strcpy(Menus[1].option[1],"About");
	
	//Open_Menu_Group(0);
}

int In_Range(int x,int y,int x0,int y0,int x1,int y1)
{
	if (x>x0 && x<x1 && y>y0 && y<y1) 
	    return 1;
	else 
	    return 0; 
} 

int In_Menu_Range(int x,int y,int men,int opt)
{
	return In_Range(x,y,Menus[men].startx,Menus[men].starty+(opt+1)*Menu_Height,Menus[men].startx+Menu_Length,Menus[men].starty+(opt+2)*Menu_Height);
}

void Print_Time()
{
	TimeCount=(clock()-BeginTime)/CPS;
	if (TimeCount==LastTime) return;
	itoa(TimeCount,Trans_Num,10);
	setfillstyle(SOLID_FILL,BLACK);
	bar(25,25,65,65); 
	setcolor(WHITE);
	outtextxy(40,40,Trans_Num);
	LastTime=TimeCount;
}

/*-----------------------------------------�˵����ֺ�������------------------------------------------*/


/*����꺯��cursor()*/
/*�ú������û��ߺ���line()����һ��ʮ���ι��*/
void cursor(int a,int b)
{
	unsigned long gsize;
	rectangle(a-MSIZE,b-MSIZE,a+MSIZE,b+MSIZE);
	line(a-MSIZE,b-MSIZE,a+MSIZE,b+MSIZE);
	line(a-MSIZE,b+MSIZE,a+MSIZE,b-MSIZE);

	/* �������ͼ��λͼ */
	gsize=imagesize(a-MSIZE,b-MSIZE,a+MSIZE,b+MSIZE);
	imagep=malloc(gsize);
	getimage(a-MSIZE,b-MSIZE,a+MSIZE,b+MSIZE,imagep);
}

/*�������ʼ������init ()*/
/*�ú�����ͨ������int 33H��0�Ź��ܵ��ö���������г�ʼ��������7�ź�8�Ź��ܣ�����x��yλ�õ���С�����ֵ�����Ϊ������ƶ������˳�ʼ��׼��������0�Ź��ܵ����ǲ���������������Ƿ�װ����������иó���ǰ��������ִ�������������mouse.com�������øú���ִ����0�Ź��ܵ��ã�������ֵΪ0ʱ(�����ز���Ϊ0)����ʾδ��װ�ɹ�������������������������ĩ��װ����ʱ������ʾMouse or Mouse Driver Absent�����ص�ϵͳ��*/
int init(int xmi,int xma,int ymi,int yma)	
{
	int retcode;
	regs.w.ax=0;
	int86(51,&regs,&regs);
	retcode=regs.w.ax;
	if(retcode==0)
 		return 0;	/*	����0��ʾ���������������δ��װ	*/
	regs.w.ax=7;
	regs.w.cx=xmi;
	regs.w.dx=xma;
	int86(51,&regs,&regs);
	regs.w.ax=8;
	regs.w.cx=ymi;
	regs.w.dx=yma;
	int86(51,&regs,&regs);	/*	��ʾ����������������Ѱ�װ	*/
	return retcode;
}

/*������λ�úͰ�ť״̬����read()*/
/*�ú�����ͨ������int 33H��3�Ź��ܵ��ã�������λ�úͰ�ť״̬������x��yλ��ֵ����ָ��mx��my����������ť״̬����mbuttָ�������*/
int read(int *mx,int *my,int *mbutt)	
{
	int xx0=*mx,yy0=*my,but0=0,mb;
	int xnew, ynew;
	do	{
    		regs.w.ax=3;
    		int86(51,&regs,&regs);
    		xnew=regs.w.cx;
	    	ynew=regs.w.dx;
    		*mbutt=regs.w.bx;
	}	while(xnew==xx0 && ynew==yy0 && *mbutt == but0 );
	*mx=xnew;
	*my=ynew;
	mb=(*mbutt);
	if(mb){
		if(mb==1) return 1;  /*�������*/
		if (mb==2) return 2; /*�Ҽ�����*/
		return 3;           /*�����İ������*/
	}
	else
		return 0;
}

/*�ú�����ͨ������read()�������ж��Ƿ��а�ť���£������£������cursor()��������λ�û���һʮ�ֹ��*/
void newxy(int *mx,int *my,int *mbutt)
{
	int ch,xx0=*mx,yy0=*my,x,y,i,j,Clicked=0;
	int xm,ym;
	ch=read(&xm,&ym,mbutt);
	switch (ch) {
	case 0:
		putimage(xx0-MSIZE,yy0-MSIZE,imagep,XOR_PUT);
		putimage(xm-MSIZE,ym-MSIZE,imagep,XOR_PUT);
		break;
	case 1:
		if (LastButton==1) break;//��ֹ��ס���������� 
		for (i=0;i<Menu_Cnt;i++)
		{
			if (In_Menu_Range(xx0,yy0,i,-1))//����˲˵��� 
			{
				Switch_Menu_Group(i);
				Close_Other_Menus(i);
				Clicked=1; 
				break;
			}
			if (Menus[i].open)
			{
				for (j=0;j<Menus[i].size;j++)
					if (In_Menu_Range(xx0,yy0,i,j))
					{
						if (Click_Menu(i,j)) gameRes=2;
						Close_Other_Menus(-1);
						Clicked=1;
						break;
					}
			}
		}
		
		if (!Clicked)			//û�е����ť���ر����в˵��� 
			Close_Other_Menus(-1); 
		
		if (In_Range(xx0,yy0,STARTX,STARTY,STARTX+SIZEX*COL,STARTY+SIZEY*ROW) && !Clicked)
		{
		    gameRes = openMine((yy0-STARTY)/SIZEY,(xx0-STARTX)/SIZEX);
		    putimage(xx0-MSIZE,yy0-MSIZE,imagep,XOR_PUT);
		}
		break;
	case 2:
		if (LastButton==2) break;
		if (In_Range(xx0,yy0,STARTX,STARTY,STARTX+SIZEX*COL,STARTY+SIZEY*ROW))
		{
			flag_question_Block((yy0-STARTY)/SIZEY,(xx0-STARTX)/SIZEX);
			putimage(xx0-MSIZE,yy0-MSIZE,imagep,XOR_PUT);
		}
		break;
	case 3:
		cursor(xx0,yy0);
		cursor(xm,ym);
		putpixel(xm,ym,7);
		break;
	}
	LastButton=ch;
	*mx=xm;
	*my=ym;
}

void Init_Game()
{
	newGame();
    flag_cnt=0;
    draw_loading();
    Init_Menus(); 
	gameRes=0;
	LastButton=-1;
	BeginTime=clock();
	LastTime=-1;
}

/*-----------------------------------------��꼰��ʼ�����ֺ�������------------------------------------------*/


