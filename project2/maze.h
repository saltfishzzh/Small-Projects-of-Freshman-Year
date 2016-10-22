#include <stdio.h> 
#include <time.h>  
#include <stdlib.h>
#include "graphics.h" 

#define MAXNUM 55

extern int m,n,maze[MAXNUM][MAXNUM],len;

void initGraph();
void input();
void GenerateMaze();
void DrawMaze(int len);
void Find_DrawPath(int len);

