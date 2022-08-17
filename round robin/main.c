#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#define Process int

/*
 * Process: Each process has a name and has an execution time.
 *          We keep track of how long the process still needs
 *          to run on the processor. "remaining_time" is the
 *          remaining execution time of the process.
 */
typedef struct
{
    char *name;
    int starting_time;
    int remaining_time;

} Process;
/*
 *
 */
typedef struct Node
{
    Process data;
    struct Node* next;
} Node;
/*
 *
 */
typedef struct
{
    /* TODO: ADD YOUR CODE HERE */
    Node * head;
    Node * tail;

} Queue;
/*
 *
 */
Queue* init()
{
    /* TODO: ADD YOUR CODE HERE */
    Queue* q =malloc(sizeof(Queue));
    q->head=NULL;
    q->tail=NULL;
    return q;
}
/*
 *
 */
Node* newNode(Process val)
{
    Node *n =malloc(sizeof(Node));
    n->data=val;
    n->next=NULL;
    return n;
}

int isEmpty(Queue *q)
{
    /* TODO: ADD YOUR CODE HERE */
    if(q->head==NULL)
        return 1;
    else
        return 0;
    return -1;
}
/*
 *
 */
Process dequeue(Queue *q)
{
    if(q->head)
    {
        Process result;
        Node*temp=q->head;
        result=temp->data;
        q->head=temp->next;
        free(temp);
        if(q->head==NULL)
            q->tail=NULL;
        return result;
    }
}
/*
 *
 */
void enqueue(Queue *q, Process val)
{
    /* TODO: ADD YOUR CODE HERE */
    Node* ptr =newNode(val);
    if(q->head==NULL)//list is empty
        q->head=q->tail=ptr;
    else
    {
        q->tail->next=ptr;
        q->tail=ptr;
    }
}
void destroy(Queue *q)
{
    /* TODO: ADD YOUR CODE HERE */
    while(isEmpty(q)==0)
    {
        dequeue( q);

    }

}
/*
 *

void destroy(Queue *q)
{
/* TODO: ADD YOUR CODE HERE

while(!(q->head==NULL && q->tail==NULL))
{
   dequeue(q);
 }
}

  RoundRobin Scheduling
 */
void RoundRobin(char* filename)
{
    Queue*q=init();


    FILE* fp=fopen(filename,"r");
    int timeslots;

    char t[260];
    if(fp==NULL)
    {
        printf("Error File doesn't exist!\n\a");
    }
    else
    {
        fscanf(fp,"%[^=]=%d",t,&timeslots);
        fscanf(fp,"\n");
        printf("%d\n",timeslots);

    }
    int k=0;
    int count=0;
    Process p[100];

    while(!feof(fp))
    {
        p[k].name=malloc(10);
        fscanf(fp,"%s %d %d",p[k].name,&p[k].starting_time,&p[k].remaining_time);

        k++;
        count++;


    }
    int numprocesses=count;
    int i,j;

    //number of processes

    for(j=0; j<timeslots; j++)
    {

        for(i=0; i<numprocesses; i++)
        {
            if(p[i].starting_time==j)
            {

                enqueue(q,p[i]);

            }

        }
        if(isEmpty(q)==1)
        {
            printf("\nidle   %d--->%d\n",j,j+1);

        }
        else
        {

            Process x=dequeue(q);
            x.remaining_time--;
            printf("\n%s     %d--->%d",x.name,j,j+1);
            if(x.remaining_time!=0)
            {
                enqueue(q,x);

            }
            else {
                 printf ("  %s aborts\n",x.name);

            }


        }




    }



}
/*
 *
 */
int main()
{
    char filename[261];
    puts("Enter file name or Ctrl+Z to exit:");
    puts("----------------------------------");
    while(fgets(filename, 260, stdin) != NULL)
    {
        filename[strlen(filename)-1]='\0';
        if(fopen(filename,"r"))
            RoundRobin(filename);
        else
        {
            puts("File Not Found!");
            puts("----------------------------------");
        }
        puts("Enter file name or Ctrl+Z to exit:");
        puts("----------------------------------");
    }

    return 0;

}
