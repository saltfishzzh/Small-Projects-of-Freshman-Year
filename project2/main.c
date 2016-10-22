#include "maze.h" 

int m,n,maze[MAXNUM][MAXNUM],len;

int main()  
{ 
    int flag1=1,flag2=1,flag3=1;
    char ch;
    while(flag1)
    {
        flag2=1;
        input();
        GenerateMaze();
        DrawMaze(len);  
        Find_DrawPath(len);
        getch();
        closegraph();
        printf("continue?\n");
        fflush(stdin);
        scanf("%c",&ch);
        while(flag2)
        {
            if(ch=='n'||ch=='N') {
                flag1=0;
                flag2=0;
            }
            else if(ch=='y'||ch=='Y') {
                flag1=1;
                flag2=0;
            }
            else
            {
                printf("enter again\n");
                fflush(stdin);
                scanf("%c",&ch);
            }
        }
    }
    return 0;
}

