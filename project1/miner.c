#include "miner.h"


int table[ROW][COL];    /* �����������Ƿ�����*/
int num[ROW][COL];     /*������������Χ������*/
int flag[ROW][COL];     /*�����������״̬*/
int pi,pj;                /*��굱ǰλ��*/

int di[8]={-1,-1,0,1,1,1,0,-1};  /*�������ƫ����*/
int dj[8]={0,1,1,1,0,-1,-1,-1};

int flag_cnt,totalMine;/**/

void *imagep;  
int gameRes; /*��¼��Ϸ�����Ľ��״̬��0��ʾ�˳���Ϸ��-1��Ϸʧ�ܣ� 1Ϊʤ����*/
union REGS regs;
int xmin,xmax,ymin,ymax,x_max,y_max,LastButton;

/*��ʼ��ͼ����ʾ��ʽ*/
void initGraph(){
   /* Ҫ���Զ���� */
   int gdriver = DETECT, gmode, errorcode;

   /* ��ʼ��ͼ��ģʽ */
   initgraph(&gdriver, &gmode, "");

   /* ��ȡ��ʼ����� */
   errorcode = graphresult();

   if (errorcode != grOk)  /* �������� */
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1);             /* ���д������ķ��� */
   }
}

/*������ɵ��׵ķֲ�*/
void generateMine(){
  int i,k;
  int ri,rj;
  int ni,nj;
  static int seed=0;

  totalMine = ROW * COL / 6;
  memset(table, 0 ,sizeof(table));
  memset(num, 0 ,sizeof(num));

  srand(seed++);
  for(i=0;i<totalMine;i++){
    do{
      ri = rand()%ROW;
      rj = rand()%COL;
    }while(table[ri][rj]);
    for(k=0;k<8;k++){
      ni = ri + di[k];
      nj = rj + dj[k];
      if(ni>=0 && ni< ROW && nj>=0 && nj<COL) num[ni][nj]++;
    }
    table[ri][rj] = 1;
  }
  memset(flag,UNFLAG,sizeof(flag));
}

/*����С����*/
void drawBlock(int i, int j){
  int x,y,xx,yy;
  int color;
  int mx,my;

  x = STARTX+j*SIZEX;
  y = STARTY+i*SIZEY;
  xx = x+SIZEX-1;
  yy = y+SIZEY-1;

  color = (flag[i][j]==UNFLAG)?LIGHTGRAY:DARKGRAY;
  setcolor(WHITE);
  rectangle(x,y,xx,yy);
  setfillstyle(SOLID_FILL,color);
  //floodfill(x+1,y+1,WHITE);
  bar(x+1,y+1,xx-1,yy-1);

  setcolor(WHITE); line(x,y,xx,y);line(x,y,x,yy);
  setcolor(BLACK); line(xx,y,xx,yy);line(x,yy,xx,yy);

  if(pi==i && pj==j){
     setcolor(RED);
     rectangle(x+1,y+1,xx-1,yy-1);
  }
  mx = x+5;
  my = y+5;
  setcolor(LIGHTGRAY);
  switch(flag[i][j]){
  case UNFLAG:
  	  outtextxy(mx,my," ");
  	  break;
  case FLAGED:
  	  setcolor(RED); 
      outtextxy(mx,my,"F");
      break;
  case QUESTION:
      outtextxy(mx,my,"?");
      break;
  case EXPLOD:
      outtextxy(mx,my,"*");
      break;
  case OPEN:
      if(num[i][j]>=1 && num[i][j]<=8){
		char buf[3];
		itoa(num[i][j],buf,10);
		outtextxy(mx,my,buf);
      }
      break;
  }
}

/*��������*/
void drawTable(){
  int i,j;
  for(i=0;i<ROW;i++)
    for(j=0;j<COL;j++) drawBlock(i,j);
}

/*��ʼ����Ϸ*/
void newGame(){
  cleardevice();
  generateMine();
  pi = pj = 0;
  drawTable();
}

/*�ж���Ϸ�Ƿ�ʤ��*/
int checkWin(){
   int i,j;
   for(i=0;i<ROW;i++){
     for(j=0;j<COL;j++){
       if(table[i][j] == 0 && flag[i][j] != OPEN) {
		return 0;
	   }
     }
   }
   return 1;
}

/*�ж���Ϸ�Ƿ����¿�ʼ*/
int confirm(int res){
  char buffer[100];
  int kk;
  if(res == 1) {
    strcpy(buffer,"You win the game , play again (Y/N)?");
  }
  else if(res == -1){
  	lose_music(); 
  	draw_face(0);
    strcpy(buffer,"You lose the game ,play again (Y/N)?");
  }
  else {
    strcpy(buffer,"Exit game ,play again (Y/N)?");
  }
  setcolor(WHITE);
  outtextxy(0,0,buffer);
  kk = bioskey(0);
  kk = (kk&0xff);
  if(kk == 'Y' || kk == 'y') return 0;
  return 1;
}

/*�������*/
/*void flagBlock(int i,int j){
	if(flag[i][j] == FLAGED){
	   flag[i][j] = UNFLAG;
	}
	else if(flag[i][j] == UNFLAG){
	   flag[i][j] = FLAGED;
	}
	drawBlock(i,j);
}*/

/*��ǲ�ȷ��*/
/*void questBlock(int i,int j){
	if(flag[i][j] == QUESTION){
	  flag[i][j] = UNFLAG;
	}
	else {
	  if(flag[i][j] == UNFLAG) flag[i][j] = QUESTION;
	}
	drawBlock(i,j);
}*/

void draw_loading()
{
	setfillstyle(SOLID_FILL,BLUE);
	bar(STARTX,STARTY+SIZEY*ROW+20,STARTX+SIZEX*COL,STARTY+SIZEY*ROW+40);
	setfillstyle(SOLID_FILL,GREEN);
	bar(STARTX,STARTY+SIZEY*ROW+20,STARTX+SIZEX*COL*flag_cnt/totalMine,STARTY+SIZEY*ROW+40); 
}

void draw_face(int res)
{
	setcolor(YELLOW);
	circle(275,41,10);
	circle(296-25,37,2);
	circle(304-25,37,2);
	circle(296-25,37,1);
	circle(304-25,37,1);
	if (res==1) arc(300-25,45,180,360,4);
	else if (res==0) arc(300-25,49,0,180,4);
}

void flag_question_Block(int i,int j){
	if(flag[i][j] == FLAGED){
	   flag_cnt--; 
	   draw_loading();
	   flag[i][j] = QUESTION;
	}
	else if(flag[i][j] == UNFLAG){
	   flag_cnt++;
	   draw_loading();
	   flag[i][j] = FLAGED;
	}
	else if(flag[i][j] == QUESTION){
		flag[i][j] = UNFLAG;
	}
	drawBlock(i,j);
}

/*����*/
int openMine(int i,int j){
  int ii,jj,k;
  if(flag[i][j] == OPEN) return 0;
  if(table[i][j]){ /*meet a mine*/
      for(ii=0;ii<ROW;ii++){
      for(jj=0;jj<COL;jj++){
		if(table[ii][jj] && flag[ii][jj] == UNFLAG){
		   flag[ii][jj] = EXPLOD;
		   drawBlock(ii,jj);
		}
      }
    }
    draw_face(0);
    return -1; /*��Ϸʧ��*/
  }
  else{
    flag[i][j] = OPEN;
    drawBlock(i,j);
    if(num[i][j]==0){
      for(k=0;k<8;k++){
		int ni = i + di[k];
		int nj = j + dj[k];
		if(ni>=0 && ni< ROW && nj>=0 && nj<COL)
		  openMine(ni,nj);
   	  }
    }
    return 0;
  }
}
/*�Զ��ڿ�*/
int autoOpen(int i,int j){
  int k,c=0;
  int ni,nj;
  int ret=0;
  if(! (flag[i][j] == OPEN)) return 0;
  for(k=0;k<8;k++){
    ni = i + di[k];
    nj = j + dj[k];
    if(ni>=0 && ni< ROW && nj>=0 && nj<COL)
	if(flag[ni][nj] == FLAGED) c++;
  }
  if(c == num[i][j]){
    for(k=0;k<8;k++){
      int ni = i + di[k];
      int nj = j + dj[k];
      if(ni>=0 && ni< ROW && nj>=0 && nj<COL)
		if(flag[ni][nj] == UNFLAG){
		   if(openMine(ni,nj) == -1) ret = -1;
		}
    }
  }
  return ret;
}
/*-----------------------------------------�ļ�miner.c���ײ��ֺ�������------------------------------------------*/


