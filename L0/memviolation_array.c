// program3.c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
    int *a;

    //now a is sufficiently large :)
    a = calloc(11, sizeof(int));

    for(int i=0;i <= 10; i++)
    {
        // the following line tried to save to mem not allocated to a
        a[i] = i; 
    }
    for(int i=0;i <= 10; i++)
    {
        printf("%d\n", a[i]);
    }

    free(a);

}
