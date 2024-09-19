/*** external sorting using insertion sort ***/
// 我使用內部記憶體size個與兩個檔案搭配使用
// 先將input 分成兩半部
// 再把其中一個的內容存到內部記憶體
// 再把兩者 merge 輸出

#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

void prepare(void);
void mergeWrite(void);
void readArray(FILE *, int [], int);
void writeArray(FILE *, int [], int);
void insertionSort(int [], int);
int makeroom(int [], int, int);

int main(void)
{
    // fp1 is input file; fp2 is output file
    prepare();
    //將資料分割成兩份
    mergeWrite();
    //排序後合併到 input
}

void prepare(void)
{
    int data[SIZE];
    FILE * f1;
    FILE * f2;
    
    f1 = fopen("data1.txt", "r");
    f2 = fopen("data2.txt", "w");

    readArray(f1, data, SIZE); //一次只讀五個
    insertionSort(data, SIZE); //排序
    writeArray(f2, data, SIZE);//寫進第二個檔案

    readArray(f1, data, SIZE); //另外五個
    fclose(f1);
    f1 = fopen("data1.txt", "w");
    insertionSort(data, SIZE);
    writeArray(f1, data, SIZE);//寫進inputfile
    fclose(f1);
    fclose(f2);
}

void mergeWrite(void)
{
    int d2=0, count1=0, count2=0;
    int f1_data[SIZE];
    FILE *f1;
    FILE *f2;
    
    f1=fopen("data1.txt", "r");
    f2=fopen("data2.txt", "r");
    
    readArray(f1, f1_data, SIZE);
    fclose(f1);
    f1=fopen("data1.txt", "w");
    fscanf(f2, "%d", &d2);
    
    while (count1 < SIZE && count2 < SIZE)//確保沒有超出５個
        if (f1_data[count1] > d2) {       //比較將小的輸出
            fprintf(f1, "%d ", d2);
            ++count2;
            if (count2 < SIZE) fscanf(f2, "%d", &d2);
            //小於五個時再讀一個
        }
        else {
            fprintf(f1, "%d ", f1_data[count1]);
            ++count1;
        }
    if (count1 == SIZE)
        while (count2 < SIZE) {
            fprintf(f1, "%d ", d2);
            ++count2;
            if (count2 < SIZE) fscanf(f2, "%d", &d2);
        }
    else
        while (count1 < SIZE) {
            fprintf(f1, "%d ", f1_data[count1]);
            ++count1;
        }
    fclose(f1);
    fclose(f2);
}
    
void readArray(FILE *fp, int a[], int size)
{
    int i=0;

    while (i<size) //將資料輸入進陣列
        fscanf(fp, "%d", &a[i++]);
}

void writeArray(FILE *fp, int a[], int size)
{
    for (int i=0; i<size; i++) //輸出陣列
        fprintf(fp, "%d ", a[i]);
    putchar('\n');
}

void insertionSort(int a[], int size)
{
    int temp;

    for (int i=1; i<size; i++) {
        temp = a[i];
        a[makeroom(a, temp, i)] = temp;
    }
}

int makeroom(int a[], int key, int end)
{
    int location = end;

    for (int i=end-1; i>=0; i--)
        if (a[i] > key ) {
            a[i+1] = a[i];
            location = i;
        }
        else if (a[i] < key )break; //我增加的改動，因為讀到 a[i]<key 後剩下的因為排序過所以也都會符合 a[i] < key
    return location;
}

