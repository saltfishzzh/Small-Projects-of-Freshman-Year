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
/*以上为扫雷界面所需宏定义*/ 

#define ROW 16
#define COL 16
#define STARTX 75
#define STARTY 75
#define SIZEX 20
#define SIZEY 20

#define UNFLAG  0    /*未标记或挖开*/
#define FLAGED  1    /*已标记为雷*/
#define QUESTION 20   /*不能确定*/
#define EXPLOD 30     /*踩雷*/
#define OPEN 40        /*挖开*/

/*扫雷相关宏定义*/

extern char Trans_Num[10];//负责将数字转化成字符串的临时变量 

extern int table[ROW][COL];    /* 雷区各方块是否有雷*/
extern int num[ROW][COL];     /*雷区各方块周围的雷数*/
extern int flag[ROW][COL];     /*雷区各方块的状态*/
extern int pi,pj;                /*光标当前位置*/

extern int di[8];  /*方块八向偏移量*/
extern int dj[8];
extern int flag_cnt,totalMine;/**/

extern void *imagep;  
extern int gameRes; /*记录游戏结束的结果状态：0表示退出游戏；-1游戏失败； 1为胜利。*/
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
	char word[Word_Row][Word_Length],Title[Title_Length];//记录窗口的标题和内容 
}Windows[Window_Cnt],tmp_window;

extern clock_t BeginTime;
extern int TimeCount,LastTime;
extern int record[Record_Size];
/*以上菜单界面所需变量声明*/

/*初始化图形显示方式*/
void initGraph();

/*随机生成地雷的分布*/
void generateMine();

/*绘制小方块，输入第i行第j列，绘制当前坐标的方格*/
void drawBlock(int i, int j);

/*绘制雷区*/
void drawTable();

/*初始化游戏*/
void newGame();

/*判断游戏是否胜利*/
int checkWin();

/*判断游戏是否重新开始，输入res=1则游戏重新开始，反之亦然*/
int confirm(int res);

/*显示扫雷进度和笑哭脸的状态栏*/
void draw_loading();
void draw_face();

/*鼠标右键点击时标记雷，点一下标记F，点两下标记？*/
void flag_question_Block(int i,int j);

/*挖雷*/
int openMine(int i,int j);

/*自动挖开*/
int autoOpen(int i,int j);

/*绘制顶部的菜单栏主体 */
void Paint_Menu_Group(int num);

void Init_Record();

void Update_Record();

/*打开菜单栏 */
void Open_Menu_Group(int num);

/*关闭菜单栏 */
void Close_Menu_Group(int num);

/*切换某菜单栏的开闭*/
void Switch_Menu_Group(int num);

void Init_Windows();

void Close_Window(int num);

void Close_Other_Windows(int num);

void Open_Window(int num);

void Switch_Window(int num);

/*点击菜单中的某个选项 */ 
int Click_Menu(int men,int opt);

void Close_Other_Menus(int num);//关闭除了num之外的所有菜单组 

void Init_Menus();

int In_Range(int x,int y,int x0,int y0,int x1,int y1);

int In_Menu_Range(int x,int y,int men,int opt);

void Print_Time();


/*画光标函数cursor()*/
/*该函数将用画线函数line()画出一个十字形光标*/
void cursor(int a,int b);

/*鼠标器初始化函数init ()*/
/*该函数将通过调用int 33H的0号功能调用对鼠标器进行初始化，调用7号和8号功能，设置x和y位置的最小和最大值。这就为鼠标器移动进行了初始化准备。由于0号功能调用是测试鼠标驱动程序是否安装，因此在运行该程序前必须首先执行鼠标驱动程序mouse.com，若调用该函数执行了0号功能调用，当返回值为0时(即返回参数为0)，表示未安装成功，这可能是鼠标器或驱动程序末安装。这时程序将显示Mouse or Mouse Driver Absent，并回到系统。*/
int init(int xmi,int xma,int ymi,int yma);

/*读鼠标的位置和按钮状态函数read()*/
/*该函数将通过调用int 33H的3号功能调用，读鼠标的位置和按钮状态。鼠标的x、y位置值将由指针mx和my给出，而按钮状态则由mbutt指针给出。*/
int read(int *mx,int *my,int *mbutt);

/*该函数将通过调用read()函数来判断是否有按钮按下，若按下，则调用cursor()函数在新位置画出一十字光标*/
void newxy(int *mx,int *my,int *mbutt);

void Init_Game();

void lose_music();

/*播放结束音乐*/
void end_music();

/*播放开场动画*/
void cartoon();

/*绘制开场动画*/
void draw_bug(int x, int y);
