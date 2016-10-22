#include <stdio.h>
#include <stdlib.h>

main()
{
	FILE *fp;
	int *num;
	long int i, n;
    scanf("%d",&n);
	num = (int *)malloc(sizeof(int)*100000);
	if ((fp = fopen("input.txt","w")) == NULL){
        printf("File open error.\n");
        exit(0);
    }
	for (i=0; i<n; i++)
    {
    	num[i]=rand()%n;
    	fprintf(fp,"%d ",num[i]);
	}
	if (fclose(fp))
	{
		printf("Can not close the file.\n");
		exit(0);
	}
	free(num);
} 

