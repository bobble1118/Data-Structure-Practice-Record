//
//  stack practice
//
//  Created by Huang on 2023/11/15.
//

#include <stdio.h>
#include <stdlib.h>

typedef char storage;
typedef struct Stack{
    storage data;
    struct Stack * next;
}stack;

stack * push (stack *,storage);
stack * pop ( stack* );
void delete ( stack* );
int empty ( stack * );



int main(void)
{
    stack bottom= {'\0',NULL}; // 定義stack底部
    stack * head = &bottom; // 使用 head 去指向stack的頂部
    storage buffer[50] ;
    
    printf("Please enter an experession: ");
    scanf("%s", buffer);
    printf("This is what entered: %s\n",buffer);

    int i,check=1;
    for ( i=0;i<50;i++ )
    {
        if ( (buffer[i]=='(') || (buffer[i]=='[') || (buffer[i]=='{'))
        {
            head = push(head,buffer[i]);
        }
        else if ( (buffer[i]==')') || (buffer[i]==']') || (buffer[i]=='}'))
        {
            if ( head->next==NULL)// 使用check標誌不符合時的狀況
            {
                check=0;
                break;
            }
            else if ( buffer[i]==')'&& head->data=='(' )
                head = pop(head);
            else if ( buffer[i]==']'&& head->data=='[' )
                head = pop(head);
            else if ( buffer[i]=='}'&& head->data=='{' )
                head = pop(head);
            else
                break;
        }
    }
    if (empty(head)&&check)
        printf("All matched.\n");
    else
        printf("Unmatch with -> %c\n", buffer[i]);
    delete(head);
    return 0;
}

stack * push ( stack * temp , storage data )
{
    stack *top =malloc(sizeof(stack));
    top->data=data;
    top->next=temp;
    return top;
}

stack * pop ( stack * temp)
{
    stack * top;
    top=temp->next;
    free(temp);
    return top;
}

void delete(stack * temp)
{
    stack * top;
    while(temp->next!=NULL)
    {
        top=temp;
        temp=temp->next;
        free(top);
    }
}

int empty( stack * temp )
{
    if(temp->next==NULL)
        return 1;
    return 0;
}
