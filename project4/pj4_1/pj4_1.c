#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

/*************************************************
Function: // QuickSort
Description: // 快速排序
Calls: // itself;
Called By: // main;
Input: // int a[], long int l, long int, r
Output: // 无
Return: // 无
Others: // 无
*************************************************/
void QuickSort(int *a,long int left,long int right);

int main()
{
    FILE *fp1, *fp2;
    int *num;
    long int i, len;
    double start, end;
    num = (int *)malloc(sizeof(int)*100001);
    if ((fp1 = fopen("input.txt","r")) == NULL){
        printf("File open error.\n");
        exit(0);
    }
    if ((fp2 = fopen("output.txt","w")) == NULL){
        printf("File open error.\n");
        exit(0);
    }
    i=0;
    while (fscanf(fp1,"%d",&num[i]) != EOF && i < 100001)
    {
        i++;
    }
    len = i;
    start = clock();
    QuickSort(num, 0, len-1);
    end = clock();
    for (i=0; i<len; i++)
    {
        fprintf(fp2, "%d ", num[i]);
    }
    fprintf(fp2, "\ntime:%.2lfms", end-start);
    if (fclose(fp1))
    {
        printf("Can not close the file.\n");
        exit(0);
    }
    if (fclose(fp2))
    {
        printf("Can not close the file.\n");
        exit(0);
    }
    free(num);
    printf("\nAll the data had been read and written in files(input.txt and output.txt).\n");
    return 0;
}

void QuickSort(int *a,long int left,long int right)
{
    int i = left;
    int j = right;
    int key = a[left];
    
    if(left >= right)
    {
        return ;
    }
    while(i < j)
    {
        while(i < j && key <= a[j])
        {
            j--;
        }
        a[i] = a[j];
        while(i < j && key >= a[i])
        {
            i++;
        }
        a[j] = a[i];
    }
    a[i] = key;
    QuickSort(a, left, i - 1);
    QuickSort(a, i + 1, right);
}
