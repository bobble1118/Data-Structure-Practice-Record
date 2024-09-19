#include <stdio.h>
#include <stdlib.h>

#define TSize 1000
#define File_name "test_3.txt"
#define ouput_file "Double probing 3.txt"


void initialize(int []);
int hashing(int);
void dump_HT(int [],int,int);
int doubleHashing(int, int);


int main(int argc, const char * argv[]) {
    
    FILE * inp=fopen(File_name,"r");
    int key=1, i,count=0,total_excution_times=0;
    int HT[TSize];
    
    initialize(HT);
    while (fscanf(inp,"%d",&key)!=EOF) {  // Enter 0 to stop
        i = hashing(key);//i 是 key 在 hashing table 的位置

        if (HT[i] == -1)
        {
            HT[i] = key;
            total_excution_times++;
        }
        else
        {
            int step = 1;
            printf("Collision at %d for %d\n", i, key);
            count++;
            while(HT[i]!=-1){
                i = doubleHashing(key, step);
                step++;
                total_excution_times++;
                if(i>=TSize)break;
            }
            if(i<TSize)
                HT[i] = key;
        }
    }
    
    dump_HT(HT,count,total_excution_times);
    fclose(inp);
    return 0;
}
void initialize(int T[])//初始化哈希表
{
    for (int i=0; i<TSize; ++i)
        T[i] = -1;
}

int hashing(int k)//hasing function
{
    return (k%(TSize+98));
}

void dump_HT(int T[],int count,int total)//輸出哈希表,並觀察碰撞次數
{
    FILE * oup=fopen(ouput_file, "w");
    int i;
    printf("-----Hasing Table------\n");
    fprintf(oup, "-----Hasing Table------\n");
    for (i=0; i<TSize; ++i) {
        printf(" [ %d ]-> %d\n",i,T[i]);
        fprintf(oup," [ %d ]-> %d\n",i,T[i]);
    }
    printf("\nCollision times is : %d\n",count);
    printf("Total excution times is : %d\n",total);
    fprintf(oup, "\nCollision times is : %d\n",count);
    fprintf(oup, "Total excution times is : %d\n",total);
    fclose(oup);
}

int doubleHashing(int k, int step) {
    // 選擇第二個哈希函數
    return (hashing(k) + step * (7 - (k % 7)));
}
