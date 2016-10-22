#include <graphics.h>
#include <math.h>

#define MAXNUM 20000
#define PLUS 1
#define MINUS 2
#define MULTIPLY 3
#define ENTER 0x000d //13
#define BACKSPACE 0x0008 //8
#define TEXT_X 20
#define TEXT_Y 210

struct node
{
	int coe;
	int exp;
	struct node *next;
};

char *exp1, *exp2;
int number1[1000] = {0},number2[1000] = {0};

void Input_Data(char *p, int num);
int Create_Calculator();
int Get_Choice();
void Pick_Out_Nums(int num);
struct node *Expression1();
struct node *Expression2();
int Transform_Nums(char *p, int start, int end);
void Plus(struct node *head1, struct node *head2);
void Minus(struct node *head1, struct node *head2);
void Multiply(struct node *head1, struct node *head2);
void Sort(struct node *head);
void Merge_Same(struct node *head);
void Print(struct node *head);
void Delete_Zero(struct node *head);

//注意事项：将常数项放在最后一项 

void main()
{
	int a;
	struct node *HeadOfExpression1;
	struct node *HeadOfExpression2;
	
	a = Create_Calculator();
	HeadOfExpression1 = Expression1();
	HeadOfExpression2 = Expression2();
	
	switch(a)
	{
		case PLUS:Plus(HeadOfExpression1, HeadOfExpression2); break;
		case MINUS:Minus(HeadOfExpression1, HeadOfExpression2); break;
		case MULTIPLY:Multiply(HeadOfExpression1, HeadOfExpression2); break;
	}
 } 

/*************************************************
Function: // Create_Calculator
Description: // 整个输入界面的建立
Calls: // initgraph(); setfillstyle(); setcolor(); outtextxy(); 等来自graphics.h的函数
Pick_Out_Nums(int num); 等本程序函数
Called By: // main(); 主函数
Input: // 无
Output: // 输出整个输入界面的构件。
Return: // 返回选择的运算（加减乘）
Others: // 无
*************************************************/
int Create_Calculator()
{
	int i, j, flag = 0, choice;
	int driver = 0, mode = VESA_1024x768x8bit;
	exp1 = (char *)malloc(200*sizeof(char));
	exp2 = (char *)malloc(200*sizeof(char));
    initgraph(&driver, &mode, "");
    setfillstyle(1, 12);
    
    for(i = 0; i < 51; i++)
    {
    	flag = (i+1)%2;
    	for(j = 0; j < 5; j++)
    	{
    		if(1 == flag)
    		{
    			bar(20*i, 20*j, 20*i+20, 20*j+20);
    			bar(20*i, 668+20*j, 20*i+20, 668+20*j+20);
			}
    		flag = (flag+1)%2;
		}
	}
	setcolor(12);
	outtextxy(TEXT_X, TEXT_Y, "Enter the first expression:");
	outtextxy(TEXT_X, TEXT_Y+160, "Enter the second expression:");
	outtextxy(TEXT_X, TEXT_Y+320, "The calculation results:");
	Input_Data(exp1, 1);/*输入多项式*/
	Input_Data(exp2, 2);
    outtextxy(TEXT_X, TEXT_Y+250, "Enter the choice: 1.Plus; 2.Minus; 3.Multiply");
    choice = Get_Choice();
	getchar();
	return choice;
}


/*************************************************
Function: // Input_Data
Description: // 利用bioskey读入键盘逐个输入的字符，并进行处理，同时处理回车、退格键的输入，达到输入字符串的效果
Calls: // bioskey(); setcolor(); outtextxy(); 等来自graphics.h的函数
Input_Data(char *p, int num); Get_Choice(); 等本程序函数
Called By: // Create_Calculator()
Input: // char *p, int num p为储存字符串的指针，num为字符串编号，取值为1，2
Output: // 无
Return: // 无
Others: // 无
*************************************************/
void Input_Data(char *p, int num)
{
	char key, keyc;
	int flag = 1, TEXT_HEIGHT, offset=0;
	if (1 == num)
	    TEXT_HEIGHT = 30;
	else
	    TEXT_HEIGHT = 190;
	while(flag){
	    if(bioskey(1)){
		    key = bioskey(0);
		    keyc = (key&0x00FF)-0x0061+'a';
		    if((keyc == 'X' || keyc == 'x') && offset < 100)
		    {
			    setcolor(12);
			    p[offset] = keyc;
			    p[offset+1] = '\0';
			    outtextxy(TEXT_X, TEXT_Y+TEXT_HEIGHT, p);
			    offset++;
		    } 
		    if((keyc == '+'||keyc == '-'||keyc == '*'||keyc == '^') && offset < 100)
		    {
			    setcolor(12);
			    p[offset] = keyc;
			    p[offset+1] = '\0';
			    outtextxy(TEXT_X, TEXT_Y+TEXT_HEIGHT, p);
			    offset++;
		    } 
		    if(keyc >= '0' && keyc <= '9' && offset < 100)
		    {
			    setcolor(12);
			    p[offset] = keyc;
			    p[offset+1] = '\0';
			    outtextxy(TEXT_X, TEXT_Y+TEXT_HEIGHT, p);
			    offset++;
		    } 
		    else if(key == BACKSPACE && offset > 0)
		    {
			    setcolor(0);
			    outtextxy(TEXT_X, TEXT_Y+TEXT_HEIGHT, p);
			    p[--offset] = '\0';
			    setcolor(12);
			    outtextxy(TEXT_X, TEXT_Y+TEXT_HEIGHT, p);
		    }
		    else if(key == ENTER && offset != 0)
		    {
				flag = 0;
		    }
	    }
    }
    p[offset++] = '+';
    p[offset] = '\0';
    Pick_Out_Nums(num);
    return;
}

/*************************************************
Function: // Transform_Nums
Description: // 将字符串转换成数字
Calls: // 无
Called By: // Pick_Out_Nums(int num);
Input: // char *p, int start, int end 字符指针，从start到end位置的转换成数字
Output: // 无
Return: // num，转换的数字
Others: // 无
*************************************************/
int Transform_Nums(char *p, int start, int end)
{
	int i, num = 0;
	for(i = start; i <= end; i++)
		num = num*10+(p[i]-'0');
	return num;
}

/*************************************************
Function: // Pick_Out_Nums
Description: // 处理输入的字符串，将含有x的多项式提取出系数和指数来
Calls: // Transform_Nums();
Called By: // Input_Data(int num);
Input: // int num 表示是第几个字符串，取值为1，2
Output: // 无
Return: // 无
Others: // 结果存在全局变量number1,number2里面
*************************************************/
void Pick_Out_Nums(int num)
{
	char *p;
	char *temp;
	int i, j, k = 0, last, expos, xpos, neg, coe, exp;
	int *arr;
	temp = (char *)malloc(200*sizeof(char));
	p = (char *)malloc(200*sizeof(char));
	if (1 == num)
	{
		arr = number1;
		p = exp1;
	}
	else
	{
		arr = number2;
		p = exp2;
	}
	last = 0;
	i = 0;
	neg = 0;
	if (p[0] == '-')
	{
		neg = 1;
		last = 1;
		i = 1;
	}
	while(p[i] != '\0')
	{
		if (p[i] == '+' || p[i] == '-')
		{
			xpos = -1;
			expos = -1;
			for (j = last; j < i; j++)
			{
				if (p[j] == 'X' || p[j] == 'x') xpos = j;
				if (p[j] == '^') expos = j;
			}
			if (xpos == -1)
			{
				coe = Transform_Nums(p, last, i-1);
				exp = 0; 
			}
			else
			{
				if (expos == -1)
				{
					coe = Transform_Nums(p, last, xpos-1);
					exp = 1;
				}
				else
				{
					coe = Transform_Nums(p, last, xpos-1);
					exp = Transform_Nums(p, expos+1, i-1);
				}
			}
			if (xpos == last) coe = 1;
			if (expos == i-1) exp = 1;
			if (neg == 1) coe = -coe;
			arr[k++] = coe;
			arr[k++] = exp;
			if (p[i] == '-')
				neg = 1;
			else
				neg = 0;
			last = i+1;
		}
		i++;
	}
	arr[k] = MAXNUM;
	
}

/*************************************************
Function: // Get_Choice
Description: // 读取输入（1，2，3）代表加减乘
Calls: // 来自graphics.h的函数
Called By: // Create_Calculator();
Input: // 无
Output: // 无
Return: // 输入的键值
Others: // 无
*************************************************/
int Get_Choice()
{
	int key;
	char keyc;
	while(1){
		if(bioskey(1))
	    {
		    keyc = (bioskey(0)&0x00FF)-0x0061+'a';;
		    if(keyc >= '1' && keyc <= '3')
		    {
			    key = keyc-'0';
			    return key;
		    }
		    else
		        outtextxy(TEXT_X, TEXT_Y+410, "Please enter 1, 2, or 3!");
	    }	
	}
	
}

/*************************************************
Function: // Expression1
Description: // 建立表达式1的链表
Calls: // 来自graphics.h的函数
Called By: // 主函数
Input: // 无
Output: // 无
Return: // 链表的第一个结点head
Others: // 无
*************************************************/
struct node *Expression1()
{
	int i = 0;
	int size = sizeof(struct node);
	struct node *head, *tail, *p;
	head = tail = NULL;
	while (number1[i] < MAXNUM)
	{
		p = (struct node *)malloc(size);
		p ->coe = number1[i++];
		p ->exp = number1[i++];
		p ->next = NULL;
		if (head == NULL)
		    head = p;
		else
		    tail ->next = p;
		tail = p;
	}
	if(number1[i] < MAXNUM)
    {
        p = (struct node *)malloc(size);
        p ->coe = number1[i];
        p -> exp = 0;
        p ->next = NULL;
        if (head == NULL)
            head = p;
        if (tail != NULL)
            tail ->next = p;
        tail = p;
    }
	return head;
}

/*************************************************
Function: // Expression2
Description: // 建立表达式2的链表
Calls: // 来自graphics.h的函数
Called By: // 主函数
Input: // 无
Output: // 无
Return: // 链表的第一个结点head
Others: // 无
*************************************************/
struct node *Expression2()
{
	int i = 0;
	int size = sizeof(struct node);
	struct node *head, *tail, *p;
	head = tail = NULL;
	while (number2[i] < MAXNUM)
	{
		p = (struct node *)malloc(size);
		p ->coe = number2[i++];
		p ->exp = number2[i++];
		p ->next = NULL;
		if (head == NULL)
		    head = p;
		//else
		if (tail != NULL)
		    tail ->next = p;
		tail = p;
	}
	if(number2[i] < MAXNUM)
    {
        p = (struct node *)malloc(size);
        p ->coe = number2[i];
        p ->exp = 0;
        p ->next = NULL;
        if (head == NULL)
            head = p;
        else
            tail ->next = p;
        tail = p;
    }
	return head;
}

/*************************************************
Function: // Plus
Description: // 加法，最后结果通过函数Print输出
Calls: // Merge_Same(); Delete_Zero(); Print();
Called By: // 主函数
Input: // struct node *head1, struct node *head2 两条链表
Output: // 无
Return: // 无
Others: // 无
*************************************************/
void Plus(struct node *head1, struct node *head2)
{
    struct node *p1, *p2, *temp;
    int flag;
    Sort(head1);
    Sort(head2);
    p1 = head1;
    p2 = head2;
    while (p2 != NULL) {
        flag = 1;
        while (p1 != NULL && flag)
        {
            if (p1 ->exp == p2 ->exp) {
                p1 ->coe += p2 ->coe;
                flag = 0;
            }
            else if (p1 == head1 && p1 ->exp < p2 ->exp) {
                temp = (struct node*)malloc(sizeof(struct node));
                temp ->coe = p2 ->coe;
                temp ->exp = p2 ->exp;
                temp ->next = p1;
                p1 = temp;
                head1 = p1;
                flag = 0;
            }
            else if (p1 ->exp > p2 ->exp && p1 ->next ->exp < p2 ->exp) {
                temp = (struct node*)malloc(sizeof(struct node));
                temp ->coe = p2 ->coe;
                temp ->exp = p2 ->exp;
                temp ->next = p1 ->next;
                p1 ->next = temp;
                flag = 0;
            }
            p1 = p1 ->next;
        }
        p1 = head1;
        p2 = p2 ->next;
    }
    Merge_Same(p1);
    Delete_Zero(p1);
    Print(p1);
}

/*************************************************
Function: // Minus
Description: // 减法，最后结果通过函数Print输出
Calls: // Merge_Same(); Delete_Zero(); Print();
Called By: // 主函数
Input: // struct node *head1, struct node *head2 两条链表
Output: // 无
Return: // 无
Others: // 无
*************************************************/
void Minus(struct node *head1, struct node *head2)
{
	struct node *p1, *p2, *temp;
    int flag;
    Sort(head1);
    Sort(head2);
	p1 = head1;
    p2 = head2;
    while (p2 != NULL) {
        flag = 1;
        while (p1 != NULL && flag)
        {
            if (p1 ->exp == p2 ->exp) {
                p1 ->coe -= p2 ->coe;
                flag = 0;
            }
            else if (p1 == head1 && p1 ->exp < p2 ->exp) {
                temp = (struct node*)malloc(sizeof(struct node));
                temp ->coe = -1*p2 ->coe;
                temp ->exp = p2 ->exp;
                temp ->next = p1;
                p1 = temp;
                head1 = p1;
                flag = 0;
            }
            else if (p1 ->exp > p2 ->exp && p1 ->next ->exp < p2 ->exp) {
                temp = (struct node*)malloc(sizeof(struct node));
                temp ->coe = -1*p2 ->coe;
                temp ->exp = p2 ->exp;
                temp ->next = p1 ->next;
                p1 ->next = temp;
                flag = 0;
            }
            p1 = p1 ->next;
        }
        p1 = head1;
        p2 = p2 ->next;
    }
    Merge_Same(p1);
    Delete_Zero(p1);
    Print(p1);
}

/*************************************************
Function: // Multiply
Description: // 乘法，最后结果通过函数Print输出
Calls: // Merge_Same(); Print();
Called By: // 主函数
Input: // struct node *head1, struct node *head2 两条链表
Output: // 无
Return: // 无
Others: // 无
*************************************************/
void Multiply(struct node *head1, struct node *head2)
{
	int size = sizeof(struct node);
	struct node *p1, *p2, *temp, *res;
    int flag;
    
    p1 = head1;
    res = (struct node*)malloc(size);
    res = NULL;
    while (p1 != NULL)
    {
    	
    	p2 = head2;
    	while (p2 != NULL)
    	{
    		printf("%d^%d*%d^%d\n", p1 ->coe, p1 ->exp, p2 ->coe, p2 ->exp);
    		temp = (struct node*)malloc(size);
    		temp ->coe = p1 ->coe * p2 ->coe;
    		temp ->exp = p1 ->exp + p2 ->exp;
    		if (temp ->coe != 0)
    		{
    			temp ->next = res;
    			res = temp;
    		}
    		p2 = p2 ->next;
    	}
    	p1 = p1 ->next;
	}
	Sort(res);
	Merge_Same(res);
	Print(res);
}  

/*************************************************
Function: // Sort
Description: // 将head开头的多项式链表按次数降序排序 
Calls: // 无;
Called By: // Plus(); Minus(); Multiply();
Input: // struct node *head 一条链表
Output: // 无
Return: // 无
Others: // 无
*************************************************/
void Sort(struct node *head)
{
	struct node *p1, *p2, *max;
	int temp;
	p1 = head;
	while (p1 != NULL)
	{
		p2 = p1;
		max = p2;
		while (p2 != NULL)
		{
			if (p2 ->exp > max ->exp)
				max = p2;
			p2 = p2 ->next;
		}
		
		temp = p1 ->exp;
		p1 ->exp = max ->exp;
		max ->exp = temp;
		
		temp = p1 ->coe;
		p1 ->coe = max ->coe;
		max ->coe = temp;
		p1 = p1 ->next;
	}
}

/*************************************************
Function: // Merge_Same
Description: // 将head开头的有序链表合并同类项
Calls: // 无;
Called By: // Plus(); Minus(); Multiply();
Input: // struct node *head 一条链表
Output: // 无
Return: // 无
Others: // 无
*************************************************/
void Merge_Same(struct node *head) 
{
	struct node *p1, *p2;
	p1=head;
	while (p1 != NULL)
	{
		p2 = p1 ->next;
		while (p2 != NULL && p2 ->exp == p1 ->exp)
		{
			p1 ->coe += p2 ->coe;
			p2 = p2 ->next; 
			p1 ->next = p2;
		}
		p1 = p1 ->next;
	}
}

/*************************************************
Function: // Delete_Zero
Description: // 去除链表中的0项
Calls: // 无;
Called By: // Plus(); Minus();
Input: // struct node *head 一条链表
Output: // 无
Return: // 无
Others: // 无
*************************************************/
void Delete_Zero(struct node *head)
{
	struct node *p;
	p = head;
	while (p != NULL)
	{
		while (p ->next != NULL && p ->next ->coe == 0)
			p ->next = p ->next ->next;
		p = p ->next;
	}
}

/*************************************************
Function: // Print
Description: // 打印链表中代表的多项式
Calls: // 无;
Called By: // Plus(); Minus(); Multiply();
Input: // struct node *head 一条链表
Output: // 链表代表的多项式，指数和系数由链表给出
Return: // 无
Others: // 无
*************************************************/
void Print(struct node *head)
{
	struct node *p;
	text_mode();
	p = head;
	if (p ->next == NULL && p ->coe == 0)
	{
		printf("0\n");
		return;
	}
    if (head ->exp == 1) {
        if (p ->coe == 1) printf("x");
        else if (p ->coe == -1) printf("-x");
        else printf("%dx", p ->coe);
    }
    else if (p ->exp == 0) printf("%d", p ->coe);
    else if (p ->coe == 1) printf("x^%d", p ->exp);
    else if (p ->coe == -1) printf("-x^%d", p ->exp);
    else printf("%dx^%d", p ->coe, p ->exp);
    p = p ->next;
    while (p != NULL) {
        if (p ->exp == 1) {
            if (p ->coe == 1) printf("+x");
            else if (p ->coe == -1) printf("-x");
            else if (p ->coe > 0) printf("+%dx", p ->coe);
            else if (p ->coe < 0) printf("%dx", p ->coe);
        }
        else if (p ->exp == 0) {
        	if (p ->coe > 0) printf("+%d", p ->coe);
        	else if (p ->coe < 0) printf("%d", p ->coe);
		}
        else if (p ->coe == 1) printf("+x^%d", p ->exp);
        else if (p ->coe == -1) printf("-x^%d", p ->exp);
        else if (p ->coe > 0) printf("+%dx^%d", p ->coe, p ->exp);
        else if (p ->coe < 0) printf("-%dx^%d", p ->coe, p ->exp);
        p = p ->next;
    }
    puts("");
}