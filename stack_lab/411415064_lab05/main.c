/*** constructing a BST
 data from file: test.txt
 each line: phone, room, first name, last name
 ***/
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int phone;
    char room[10];
    char fname[10];
    char lname[10];
    struct node *left;
    struct node *right;
} bstType;

typedef struct ListNode {
    bstType *node;
    struct ListNode *next;
} ListNode;

typedef struct queue {
    int count;
    ListNode * front;
    ListNode * rear;
}Qtype;

void insert (bstType **, bstType *);
void search (bstType *, int);
bstType * getData (int, FILE *);
void inorder (bstType *);
void preorder_traversal(bstType *);
void postorder_traversal (bstType *);

void enqueue(Qtype *, bstType *); //queue 的處理
bstType *dequeue(Qtype *);
void bread_first_traversal(bstType *);
bstType *getdata (ListNode ** s);

int main(void)
{
    bstType * tree, * data;
    int phone;
    FILE *fp = fopen("test.txt", "r");//開檔
    tree = NULL;
    while ( fscanf(fp, "%d", &phone) != EOF ) { // 讀取資料
        data = getData(phone, fp);
        insert (&tree, data);
    }
    printf("Please enter a phone number to search: "); //print
    scanf("%d", &phone);
    search (tree, phone);
    printf("\n");
    printf("---inorder---\n");
    inorder (tree);
    printf("\n---postorder_traversal---\n");
    postorder_traversal(tree);
    printf("\n---preorder_traversal---\n");
    preorder_traversal(tree);
    printf("\n---bread_first_traversal---\n");
    bread_first_traversal(tree);
    fclose(fp);
}
bstType * getData (int phone, FILE * fp)//call by refrence ,傳入tree的位置而不是傳tree的值
{
    bstType * data = malloc(sizeof(bstType));
    data->left = data->right = NULL;
    data->phone = phone;
    fscanf(fp, "%s", data->room);
    fscanf(fp, "%s", data->fname);
    fscanf(fp, "%s", data->lname);
    return data;
}
void insert (bstType ** t, bstType * data)
{
    if (*t == NULL)
        *t = data;
    else
        if ((*t)->phone > data->phone) //比較大小去分配
            insert (&((*t)->left), data);
        else insert(&((*t)->right), data);
}
void search (bstType * t, int key)
{
    if (t == NULL)
        printf("Empty!\n");
    else if (t->phone == key) { // 找到 print
        printf("Phone: %d\n", key);
        printf("Room: %s\n", t->room);
        printf("Name: %s %s\n", t->fname, t->lname);
    }
    else
        if (t->phone > key)
            search (t->left, key);
        else search (t->right, key);
}
void inorder (bstType * t)// left->root->right
{
    if (t != NULL) {
        inorder(t->left);
        printf("Phone: %d\n", t->phone);
        printf("Room: %s\n", t->room);
        printf("Name: %s %s\n", t->fname, t->lname);
        inorder(t->right);
    }
}

void preorder_traversal( bstType *t )  //root->left->right
{
    if (t != NULL) {
        printf("Phone: %d\n", t->phone);
        printf("Room: %s\n", t->room);
        printf("Name: %s %s\n", t->fname, t->lname);
        preorder_traversal(t->left);
        preorder_traversal(t->right);
    }
}

void postorder_traversal (bstType * tree) // left->right->root
{
    if(tree!=NULL)
    {
        preorder_traversal(tree->left);
        preorder_traversal(tree->right);
        printf("Phone: %d\n", tree->phone);
        printf("Room: %s\n", tree->room);
        printf("Name: %s %s\n", tree->fname, tree->lname);
    }
}

void enqueue(Qtype *q, bstType *node)
{
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    newNode->node = node;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front=q->rear =newNode;
    }
    else
    {
        q->rear->next = newNode;
        q->rear=q->rear->next;
    }
    q->count+=1;
}

bstType *dequeue(Qtype *q)
{
    bstType * item=NULL;
    
    if (q->front == NULL) {
        return NULL;
    }
    else if (q->count == 1) {//只有一個的話
        item = getdata(&(q->front));
        q->rear = NULL;
    }
    else{
        item = getdata(&(q->front));
    }
    return item;
}

void bread_first_traversal(bstType *tree )
{
    if (tree == NULL) {
        printf("Tree is empty\n");
        return;
    }
    Qtype *q=malloc(sizeof(Qtype)); //創建Queue
    q->rear=NULL;
    q->front=NULL;
    q->count=0;
    
    enqueue(q, tree);//先queue相當于New();
    
    while (q->front != NULL) {
        bstType *current; //儲存當下讀到的 subtree
        current=dequeue(q); // 拿掉front 並指派 current = front
        if (current != NULL) { // 有東西就print
            printf("Phone: %d\n", current->phone);
            printf("Room: %s\n", current->room);
            printf("Name: %s %s\n", current->fname, current->lname);
            
            if (current->left != NULL) { //subtree 左邊leaf有東西就enqueue
                enqueue(q,current->left);
            }
            if (current->right != NULL) { //subtree 右邊leaf有東西enqueue
                enqueue(q, current->right);
            }
        }
    }
}

bstType* getdata (ListNode ** s)
{
    bstType* data;
    ListNode * p = *s; //將原來front的位置放在p
    data = p->node;//data存出來
    *s = (*s)->next;//front 指向 front->next
    free(p); //free 掉原本的front
    return data;//回傳data
}


