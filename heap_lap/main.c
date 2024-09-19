#include <stdio.h>
#include <stdlib.h>

#define SIZE 100
#define filename "test2.txt"
typedef int aType; //ADT


int readArray (aType []);
void printArray (aType [], int);
void heapify(aType [], int);
void reheapup(aType [], int);
void extractKMax(aType [],int *);
int delete(aType [], int*);

int main(void)
{
    int count;
    int K;
    aType array[SIZE];

    count=readArray(array);
    printf("\nContent of array:\n");
    printArray(array, count);

    printf("\nProcessing heapify:\n");
    heapify(array,count);
    
    printf("Enter K number...\n");
   //scanf("%d",&K);
    K=count;
    if (K>count)K=count;
    puts("Max:");
    for (int i=0; i<K; i++) {
        printf("%d->",i+1);
        extractKMax(array,&count);
    }
    puts("");
    
}

int readArray (aType a[])
{
    FILE * fp;
    int count=0;

    printf("Please enter a filename: ");
    fp = fopen (filename, "r"); //open file

    while (fscanf(fp, "%d", &a[count++]) != EOF); //將數據輸入 a[]且尚未heapify

    fclose(fp);

    return (count-1); //多做一次
}

void printArray (aType a[], int count)
{
    int i;

    for (i=0; i<count; ++i)  //print出整個陣列
        printf ("%d ", a[i]);
    printf("\n");
}

void heapify(aType H[], int size)
{
    int i;

    for (i=1;i<size; ++i){
        if (H[i] > H[(i-1)/2]) //跟 parent 比較，如果比較大就 rotate
            reheapup(H, i);
        printArray(H,size);
    }
}

void reheapup(aType H[], int start)
{
    int i = start, temp;

    for (i=start; i>0; i=(i-1)/2) //符合條件交換
        if (H[i] > H[(i-1)/2]) {
            temp=H[(i-1)/2];
            H[(i-1)/2] = H[i];
            H[i] = temp;
        }
}

void extractKMax(aType H[],int *size)
{
    printf("%d  ",delete(H, size));
}

int delete(aType H[], int *size)
{
    int MAX=H[0];
    H[0]=H[--(*size)];
    for (int i=1;i<*size; ++i){
        if (H[i] > H[(i-1)/2]) //跟 parent 比較，如果比較大就 rotate
            reheapup(H, i);
    }
    return MAX;
}
