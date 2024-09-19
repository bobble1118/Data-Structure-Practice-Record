#include <stdio.h>
#include <stdlib.h>

#define TSize 1000
#define File_name "test_3.txt" // test file name
#define output_file "Quadratic_probing_3.txt" // output file name

void initialize(int []);
int hashing(int);
void dump_HT(int [], int, int);

int main(int argc, const char * argv[]) {
    FILE *inp = fopen(File_name, "r");
    if (inp == NULL) {
        printf("Error opening file %s\n", File_name);
        return 1;
    }

    int key, i, count = 0, total_execution_times = 0;
    int HT[TSize];

    initialize(HT);
    while (fscanf(inp, "%d", &key) != EOF) {
        i = hashing(key); // i 是 key 在哈希表的位置
        if (HT[i] == -1) {
            HT[i] = key;
            total_execution_times++;
        } else {
            printf("Collision at %d for %d\n", i, key);
            count++;
            int step = 1;
            while (HT[i] != -1) {
                i = (i + step * step) % TSize; // 使用 %TSize 來確保 i 不超過哈希表大小
                total_execution_times++;
                step++;
                if (step >= TSize) { // 當 step 超過 TSize 時跳出迴圈，防止無限迴圈
                    break;
                }
            }
            if (HT[i] == -1) {
                HT[i] = key;
            }
        }
    }

    dump_HT(HT, count, total_execution_times);
    fclose(inp);
    return 0;
}

void initialize(int T[]) { // 初始化哈希表
    for (int i = 0; i < TSize; ++i)
        T[i] = -1;
}

int hashing(int k) { // 哈希函數
    return (k % TSize);
}

void dump_HT(int T[], int count, int total) { // 輸出哈希表，並觀察碰撞次數
    FILE *oup = fopen(output_file, "w");
    if (oup == NULL) {
        printf("Error opening output file %s\n", output_file);
        return;
    }

    printf("-----Hashing Table------\n");
    fprintf(oup, "-----Hashing Table------\n");
    for (int i = 0; i < TSize; ++i) {
        printf(" [ %d ]-> %d\n", i, T[i]);
        fprintf(oup, " [ %d ]-> %d\n", i, T[i]);
    }
    printf("\nCollision times is: %d\n", count);
    printf("Total execution times is: %d\n", total);
    fprintf(oup, "\nCollision times is: %d\n", count);
    fprintf(oup, "Total execution times is: %d\n", total);
    fclose(oup);
}
