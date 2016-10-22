#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRYTIME 1000
#define MAXLEN 100010

int CutOfPoint;
int arr1[MAXLEN], arr2[MAXLEN], tmp;
int value[MAXLEN], len;

/*************************************************
Function: // MergeSort
Description: // 归并排序
Calls: // itself;
Called By: // GetCutOfPoint;
Input: // int a[], int l, int, r
Output: // 无
Return: // 无
Others: // 无
*************************************************/
void MergeSort(int a[], int l, int r)
{
    int mid = (l+r) >> 1, i, nodel, noder, nodea;
    if (l >= r) return ;
    nodel = l;
    noder = mid+1;
    nodea = l;
    MergeSort(a, l, mid);
    MergeSort(a, mid+1, r);
    for (i = l; i <= mid; i++) arr1[i]=a[i];
    for (i = mid+1; i <= r; i++) arr2[i]=a[i];
    while (nodel <= mid && noder <= r)
    {
        if (arr1[nodel] < arr2[noder])
            a[nodea++] = arr1[nodel++];
        else
            a[nodea++] = arr2[noder++];
    }
    while (nodel <= mid)
        a[nodea++] = arr1[nodel++];
    while (noder <= r)
        a[nodea++] = arr2[noder++];
}

/*************************************************
Function: // SelectSort
Description: // 选择排序
Calls: // 无
Called By: // GetCutOfPoint, SortIntegerArray;
Input: // int a[], int l, int, r
Output: // 无
Return: // 无
Others: // 无
*************************************************/
void SelectSort(int a[], int l, int r)
{
    int i, j, minv, pos, tmp;
    for (i = l; i <= r; i++)
    {
        minv = a[i];
        pos = i;
        for (j = i + 1; j <= r; j++)
            if (a[j] < minv)
            {
                minv = a[j];
                pos = j;
            }
        if (pos != i)
        {
            tmp = a[i];
            a[i] = a[pos];
            a[pos] = tmp;
        }
    }
}

/*************************************************
Function: // SortIntegerArray
Description: // 融合选择归并排序
Calls: // itself;
Called By: // main;
Input: // int a[], int l, int, r
Output: // 无
Return: // 无
Others: // 无
*************************************************/
void SortIntegerArray(int a[], int l, int r)
{
    int mid = (l+r) >> 1, i, nodel, noder, nodea;
    if (r - l <=  CutOfPoint)
    {
        SelectSort(a, l, r);
        return;
    }
    nodel = l;
    noder = mid+1;
    nodea = l;
    SortIntegerArray(a, l, mid);
    SortIntegerArray(a, mid+1, r);
    for (i = l; i <= mid; i++) arr1[i]=a[i];
    for (i = mid+1; i <= r; i++) arr2[i]=a[i];
    while (nodel <= mid && noder <= r)
    {
        if (arr1[nodel] < arr2[noder])
            a[nodea++] = arr1[nodel++];
        else
            a[nodea++] = arr2[noder++];
    }
    while (nodel <= mid)
        a[nodea++] = arr1[nodel++];
    while (noder <= r)
        a[nodea++] = arr2[noder++];
}

/*************************************************
Function: // Randomize
Description: // 随机生成数组
Calls: // itself;
Called By: // GetCutOfPoint;
Input: // int a[], int N;
Output: // 无
Return: // 无
Others: // 无
*************************************************/
void Randomize(int a[], int N)
{
    int i;
    srand(time(0));
    for (i = 1; i <= N; i++)
        a[i] = rand();
    
}

/*************************************************
Function: // GetCutOfPoint
Description: // 求出排序的分界点
Calls: // Randomize, SelectSort, MergeSort;
Called By: // main;
Input: // int a[], int N;
Output: // 无
Return: // 无
Others: // 无
*************************************************/
void GetCutOfPoint()
{
    int i, j, MergeTime, SelectTime, length, count = 0;
    clock_t start, end;
    CutOfPoint = 0;
    for (length = 5; length <= 200; length++)
    {
        MergeTime = SelectTime = 0;
        for (i = 1; i <= TRYTIME; i++)
        {
            Randomize(value, length);
            start = clock();
            SelectSort(value, 1, length);
            end = clock();
            SelectTime += end - start;
            
            Randomize(value, length);
            start = clock();
            MergeSort(value, 1, length);
            end = clock();
            MergeTime += end - start;
        }
        if (MergeTime < SelectTime)
        {
            if (++count == 5) {
                CutOfPoint = length -4;
                break;
            }
        }
        else count = 0;
    }
}

int main()
{
    FILE *fp1, *fp2;
    int i;
    double start, end;
    GetCutOfPoint();
    if ((fp1 = fopen("input.txt","r")) == NULL){
        printf("File open error.\n");
        exit(0);
    }
    if ((fp2 = fopen("output.txt","w")) == NULL){
        printf("File open error.\n");
        exit(0);
    }
    fprintf(fp2, "Best split point is n=%d\n", CutOfPoint);
    
    i=0;
    while (fscanf(fp1,"%d",&value[i]) != EOF && i < 100001)
    {
        i++;
    }
    len = i;
    start = clock();
    SortIntegerArray(value, 1, len);
    end = clock();
    for (i=0; i<len; i++)
    {
        fprintf(fp2, "%d ", value[i]);
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
    printf("\nAll the data had been read and written in files(input.txt and output.txt).\n");
    return 0;
} 