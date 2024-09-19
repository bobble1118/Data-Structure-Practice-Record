//
//  main.c
//  lab07_sort
//
//  Created by Huang on 2023/12/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define size 14

void resetArray(int [],int []);
void printArray(int [],int) ;
void selectionSort(int [], int);
void insertionSort(int [], int);
void heap_sort(int [], int);
void bubblesort_plus(int [],int);
void bubblesort(int [],int);

void heapify(int [],int,int *);
void reheapup(int [], int, int*);

int main(int argc, const char * argv[]) {
    
    int std_arr[size]={0};
    int arr[size]={0};
    int check=0;
    srand((unsigned)time(NULL));
    
    for (int i=0; i<size; i++) {
        std_arr[i]=(rand()%100)+1;
    }
    
    while (1) {
        resetArray(arr, std_arr);
        printf("Oringinal\n");
        printArray(arr, size);
        printf("1. selectionSort\n2. insertionSort\n3. heap_sort\n4. bubblesort_plus\n5. bubblesortothers->end\nEnter the operation number:");
        scanf("%d",&check);
        switch (check) {
            case 1:
                selectionSort(arr, size);
                break;
            case 2:
                insertionSort(arr, size);
                break;
            case 3:
                heap_sort(arr, size);
                break;
            case 4:
                bubblesort_plus(arr, size);
                break;
            case 5:
                bubblesort(arr, size);
        }
        if(check>5)break;
    }
    return 0;
}

void resetArray(int arr[],int std_arr[]){
    for (int i=0; i<size; i++) {
        arr[i]=std_arr[i];
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void selectionSort(int arr[], int n) {
    int i, j, min_idx,count=0;
    
    printf("\n---selectionSort---\n");
    for (i = 0; i < n ; i++) {
        // 尋找未排序部分的最小元素
        printArray(arr, n);
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
                count++; //比較的次數
            }
        }
        // 將找到的最小元素與第 i 個元素交換
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
        count++;
        // 交換的次數
    }
    printf("Executed %d times in total\n\n",count);
}

void insertionSort(int arr[], int n) {
    int i, key, j, count=0;
    printf("\n---insertionSort---\n");
    
    
    for (i = 0; i < n; i++) {
        printArray(arr, n);
        key = arr[i];
        j = i - 1;
        // 將 arr[0...i-1] 中比 key 大的元素向右移動一個位置
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
            count++;
            // 比較的次數
        }
        arr[j + 1] = key;
        count++;
        // 移動的次數
    }
    printArray(arr, n);
    printf("Executed %d times in total\n\n",count);
}

void bubblesort(int arr[],int n){
    int i, j, count=0;
    printf("\n---bubbleSort---\n");
    for (i = 0; i < n - 1; i++) {
        // 最後 i 個元素已經排好，不需要再比較
        for (j = 0; j < n - i - 1; j++) {
            //比較的次數
            count++;
            if (arr[j] > arr[j + 1]) {
                // 交換相鄰元素
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                count++;
                //交換的次數
            }
        }
        printArray(arr, n);
    }
    printf("Executed %d times in total\n\n",count);
}

void bubblesort_plus(int arr[], int n) {
    int i, j, count=0;
    int flag=0;
    printf("\n---bubbleSortPlus---\n");
    for (i = 0; i < n - 1; i++) {
        flag=0;//用來確認本次是否交換過
        // 最後 i 個元素已經排好，不需要再比較
        for (j = 0; j < n - i - 1; j++) {
            //比較的次數
            count++;
            if (arr[j] > arr[j + 1]) {
                // 交換相鄰元素
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                count++;
                //交換的次數
                flag++;
            }
        }
        if(!flag)break;
        printArray(arr, n);
    }
    printf("Executed %d times in total\n\n",count);
}

void heap_sort(int arr[], int n) {
    int count = 0;
    printf("\n---HeapSort---\n");

    heapify(arr, n,NULL);

    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, &count);

        printArray(arr, n);
    }

    printf("Executed %d times in total\n\n", count);
}

void heapify(int arr[], int n, int *count){
    for (int i = 1; i < n; ++i){
        if (arr[i] > arr[(i-1)/2]) {
            reheapup(arr, i, count);
            }
    }
}

void reheapup(int arr[], int start, int *count){
    int i, temp;

    for (i = start; i > 0; i = (i - 1) / 2) {
        if(count!=NULL)
            (*count)++;
        //紀錄次數
        if (arr[i] > arr[(i - 1) / 2]) {
            temp = arr[(i - 1) / 2];
            arr[(i - 1) / 2] = arr[i];
            arr[i] = temp;
        }
    }
}
