#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int data;
    struct  Node * next;
} Node;


typedef struct
{
    Node * head;
    Node * tail;
} Queue;
Queue* init()
{
    Queue* q =malloc(sizeof(Queue));
    q->head=NULL;
    q->tail=NULL;
    return q;
}
Node* newNode(int value)
{
    Node *n =malloc(sizeof(Node));
    n->data=value;
    n->next=NULL;
    return n;
}

void Enqueue(Queue * q,int value)
{
    Node* n =newNode(value);
    if(q->head==NULL)//list is empty
        q->head=q->tail=n;
    else
    {
        q->tail->next=n;
        q->tail=n;
    }
}
int isEmpty(Queue *q)
{
    if(q->head==NULL)
        return 1;
    else
        return 0;

}
int Dequeue(Queue*q)
{
    if(q->head)
    {
        int result;
        Node*temp=q->head;
        result=temp->data;
        q->head=temp->next;
        free(temp);
        if(q->head==NULL)
            q->tail=NULL;
        return result;
    }
}

int main()
{
   Queue*q=init();
   Enqueue(q,5);
   Enqueue(q,6);
   Enqueue(q,7);
   while(!isEmpty(q))
    printf("%d\t",Dequeue(q));


    return 0;
}
