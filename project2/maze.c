#include "maze.h"

void initGraph()
{
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

void input() /*�����Թ��ĳ��Ϳ�ͬʱ���*/
{
    printf("Please Enter(both number should be in[2,50])\n:");
    scanf("%d%d",&m,&n);
    len=300/(m>n?m+1:n+1);	
}

void GenerateMaze()
{
	int i,j,x;
	for(i=0;i<=m+1;i++){ 
        for(j=0;j<=n+1;j++){ 
            if(i==0||j==0||i==m+1||j==n+1) 
                maze[i][j]=1; 
            else 
            { 
            x=rand()%1000; 
            if(x>700){maze[i][j]=1;} /*���ƾ�����1�ĸ�����̫��1�Թ��������߲�ͨ */
            else{maze[i][j]=0;} 
            } 
            if (i==m&&j==n) maze[i][j]=0;
			if (i==1&&j==1) maze[i][j]=0;			
			printf("%d ",maze[i][j]);
        } 
        printf("\n");
    } 
}

void DrawMaze(int len)
{
	int i,j;
	
	initGraph();  /*��ʼ��ͼ��ģʽ*/
	cleardevice();
	setbkcolor(10);
	setcolor(4);
	setfillstyle(1, 4);
	for (i = 0; i < m+2; i++)
		for (j = 0; j < n+2; j++)
		{
			if (1 == maze[i][j])
			{
				setfillstyle(1, 4);
				/*�趨ÿ�����ӿ�Ϊ20����λ����Ϊ20����λ*/
				bar(50+j*len,50+i*len,50+len+j*len,50+len+i*len);/*sleep(1);*/
			}
			else 
			{
				setfillstyle(1, 15);
				bar(50+j*len,50+i*len,50+len+j*len,50+len+i*len);/*sleep(1);*/
			}
		}
}

void Find_DrawPath(int len)
{
	int i,j;
    int move[4][2]={0,1,1,0,0,-1,-1,0}; 
    int *quei;/*������������� */
    int *quej;/*������������� */
    int *prep;/*����֮ǰһ���ڶ����е�λ�� */
    int head,rear,length;/*����ͷ������β�����г��� */
    int pos;/*��ǰ�ڵ��ڶ����е�λ�ã� */
    int ii,jj,ni,nj;/*��ǰ�ڵ�����꣬�½ڵ������ */
    int dir;/*�ƶ����� */
    
    quei=(int *)malloc(sizeof(int)*m*n);
    quej=(int *)malloc(sizeof(int)*m*n);
    prep=(int *)malloc(sizeof(int)*m*n);
    head=0;rear=1;length=1; 
    quei[head]=1;quej[head]=1;prep[head]=-1;/*���λ�ý����� */
	if(maze[1][1]==1)length=0;/*��һ��Ͳ���ͨ�� */
    else maze[1][1]=1; 
    while(length)/*���зǿռ��� */
    { 
        for(pos=head;pos<head+length;pos++)/*Ѱ����һ�����нڵ� */
        { 
            ii=quei[pos];jj=quej[pos];/*��ǰλ������ */
            if(ii==m&&jj==n)break; 
            for(dir=0;dir<4;dir++)/*Ѱ��8������ */
            { 
                ni=ii+move[dir][0];nj=jj+move[dir][1];/*������ */
                if(maze[ni][nj]==0)/*���û���߹� */
                { 
                    quei[rear]=ni;quej[rear]=nj;prep[rear]=pos;/*�½ڵ���� */
                    rear=rear+1; 
                    maze[ni][nj]=1;/*����Ѿ��߹� */
                } 
            } 
        } 
        if(ii==m&&jj==n)break; 
        head=head+length; 
        length=rear-head;/*��һ��ڵ���� */
    } 
	if(ii==m&&jj==n) 
    { 
        while(pos!=-1) 
        { 
            setfillstyle(1, 6);
	     	setcolor(2);
	     	circle(50+(quej[pos])*len+len/2,50+(quei[pos])*len+len/2, len/2);
            pos=prep[pos]; 
        } 
    } 
    else 
    { 
        printf("THERE IS NO PATH.");
    }
}
