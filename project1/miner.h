#include <graphics.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "time.h" 
#include <dos.h>

#define Menu_Height 20
#define Menu_Length 80
#define Menu_Name_Length 10
#define Menu_Max_Size 5
#define Window_Cnt 3
#define Title_Height 20 
#define MSIZE 5
#define Menu_Cnt 2
#define MAXX 500	
#define MAXY 500
#define Record_Size 3 
#define CPS CLOCKS_PER_SEC
#define INF 1000000000
#define Word_Row 20
#define Word_Length 45
#define Title_Length 20 
#define Letter_Height 20
/*����Ϊɨ�׽�������궨��*/ 

#define ROW 16
#define COL 16
#define STARTX 75
#define STARTY 75
#define SIZEX 20
#define SIZEY 20

#define UNFLAG  0    /*δ��ǻ��ڿ�*/
#define FLAGED  1    /*�ѱ��Ϊ��*/
#define QUESTION 20   /*����ȷ��*/
#define EXPLOD 30     /*����*/
#define OPEN 40        /*�ڿ�*/

/*ɨ����غ궨��*/

extern char Trans_Num[10];//��������ת�����ַ�������ʱ���� 

extern int table[ROW][COL];    /* �����������Ƿ�����*/
extern int num[ROW][COL];     /*������������Χ������*/
extern int flag[ROW][COL];     /*�����������״̬*/
extern int pi,pj;                /*��굱ǰλ��*/

extern int di[8];  /*�������ƫ����*/
extern int dj[8];
extern int flag_cnt,totalMine;/**/

extern void *imagep;  
extern int gameRes; /*��¼��Ϸ�����Ľ��״̬��0��ʾ�˳���Ϸ��-1��Ϸʧ�ܣ� 1Ϊʤ����*/
extern union REGS regs;
extern int xmin,xmax,ymin,ymax,x_max,y_max,LastButton;

typedef struct
{
   char shape, color;
} NODE;
NODE bug[5];

struct Menu_Group
{
	int open,size,startx,starty;
	char name[Menu_Name_Length];
	char option[Menu_Max_Size][Menu_Name_Length];
}Menus[Menu_Cnt],Menu;

struct Window
{
	int startx,starty,endx,endy,open;
	char word[Word_Row][Word_Length],Title[Title_Length];//��¼���ڵı�������� 
}Windows[Window_Cnt],tmp_window;

extern clock_t BeginTime;
extern int TimeCount,LastTime;
extern int record[Record_Size];
/*���ϲ˵����������������*/

/*��ʼ��ͼ����ʾ��ʽ*/
void initGraph();

/*������ɵ��׵ķֲ�*/
void generateMine();

/*����С���飬�����i�е�j�У����Ƶ�ǰ����ķ���*/
void drawBlock(int i, int j);

/*��������*/
void drawTable();

/*��ʼ����Ϸ*/
void newGame();

/*�ж���Ϸ�Ƿ�ʤ��*/
int checkWin();

/*�ж���Ϸ�Ƿ����¿�ʼ������res=1����Ϸ���¿�ʼ����֮��Ȼ*/
int confirm(int res);

/*��ʾɨ�׽��Ⱥ�Ц������״̬��*/
void draw_loading();
void draw_face();

/*����Ҽ����ʱ����ף���һ�±��F�������±�ǣ�*/
void flag_question_Block(int i,int j);

/*����*/
int openMine(int i,int j);

/*�Զ��ڿ�*/
int autoOpen(int i,int j);

/*���ƶ����Ĳ˵������� */
void Paint_Menu_Group(int num);

void Init_Record();

void Update_Record();

/*�򿪲˵��� */
void Open_Menu_Group(int num);

/*�رղ˵��� */
void Close_Menu_Group(int num);

/*�л�ĳ�˵����Ŀ���*/
void Switch_Menu_Group(int num);

void Init_Windows();

void Close_Window(int num);

void Close_Other_Windows(int num);

void Open_Window(int num);

void Switch_Window(int num);

/*����˵��е�ĳ��ѡ�� */ 
int Click_Menu(int men,int opt);

void Close_Other_Menus(int num);//�رճ���num֮������в˵��� 

void Init_Menus();

int In_Range(int x,int y,int x0,int y0,int x1,int y1);

int In_Menu_Range(int x,int y,int men,int opt);

void Print_Time();


/*����꺯��cursor()*/
/*�ú������û��ߺ���line()����һ��ʮ���ι��*/
void cursor(int a,int b);

/*�������ʼ������init ()*/
/*�ú�����ͨ������int 33H��0�Ź��ܵ��ö���������г�ʼ��������7�ź�8�Ź��ܣ�����x��yλ�õ���С�����ֵ�����Ϊ������ƶ������˳�ʼ��׼��������0�Ź��ܵ����ǲ���������������Ƿ�װ����������иó���ǰ��������ִ�������������mouse.com�������øú���ִ����0�Ź��ܵ��ã�������ֵΪ0ʱ(�����ز���Ϊ0)����ʾδ��װ�ɹ�������������������������ĩ��װ����ʱ������ʾMouse or Mouse Driver Absent�����ص�ϵͳ��*/
int init(int xmi,int xma,int ymi,int yma);

/*������λ�úͰ�ť״̬����read()*/
/*�ú�����ͨ������int 33H��3�Ź��ܵ��ã�������λ�úͰ�ť״̬������x��yλ��ֵ����ָ��mx��my����������ť״̬����mbuttָ�������*/
int read(int *mx,int *my,int *mbutt);

/*�ú�����ͨ������read()�������ж��Ƿ��а�ť���£������£������cursor()��������λ�û���һʮ�ֹ��*/
void newxy(int *mx,int *my,int *mbutt);

void Init_Game();

void lose_music();

/*���Ž�������*/
void end_music();

/*���ſ�������*/
void cartoon();

/*���ƿ�������*/
void draw_bug(int x, int y);
