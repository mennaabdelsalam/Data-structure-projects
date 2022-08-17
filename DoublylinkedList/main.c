#include <stdio.h>
#include <stdlib.h>
/*
 *
 */
typedef struct Node
{
    int data;
    struct Node* next;
    struct Node* prev;
} Node;
/*
 *
 */
typedef struct
{
    Node* head;
    Node* tail;
} DoublyLinkedList;
/*
 *
 */

DoublyLinkedList* init()
{
    DoublyLinkedList *list =malloc(sizeof(DoublyLinkedList));
    list->head=NULL;
    list->tail=NULL;
}

Node* newNode(int x)
{
    Node*m=malloc(sizeof(Node));
    m->data=x;
    m->next=NULL;
    m->prev=NULL;
    return m;
}

void insertEnd(DoublyLinkedList *list,int x)
{
    Node * n =newNode(x);
    if(list->head==NULL)
        list->head=list->tail=n;
    else
    {
        list->tail->next=n;
        n->prev=list->tail;
        list->tail=n;
    }
}

void deleteEnd(DoublyLinkedList* list)
{

    if(list->head!=NULL)
    {
        Node* temp=list->tail;
        list->tail=list->tail->prev;
        free(temp);
        if(list->tail==NULL)           //only one node
            list->head=NULL;
    }
}

/*
 * convertArrayToDoublyLinkedList
 */
DoublyLinkedList* convertArrayToDoublyLinkedList(int array[], int size)
{
    DoublyLinkedList *list = init();
    /* TODO: ADD YOUR CODE HERE */
    int i;
    for(i=0; i<size; i++)
    {
        insertEnd(list,array[i]);
    }

    return list;

}


void toapp(DoublyLinkedList* list,int value)
{
    Node *n=newNode(value);
    if(list->head==NULL)
    {
        list->head=list->tail=n;
    }
    else
    {
        list->tail->next=n;
        n->prev=list->tail;
        list->tail=n;

    }

}
int Existence( DoublyLinkedList* list2,int value)
  {
  Node* temp=list2->head;
  int flag=0;
  while(temp!=NULL)
  {

  if(temp->data==value)
  {
  flag=1;
  break;
  }
  else
  { flag=0;
  temp=temp->next;

  }
  }
  return flag;
  }
/*
 * destroy
 */
void destroy(DoublyLinkedList* list)
{
    /* TODO: ADD YOUR CODE HERE */

    while(list->tail!=NULL)
    {
        deleteEnd(list);

    }
}
/*
 * copy: copy list into a new list and return the new one.
 */


    DoublyLinkedList* copy(DoublyLinkedList* list)
{
    DoublyLinkedList *newlist = init();
    /* TODO: ADD YOUR CODE HERE */
    Node *temp;
    for(temp=list->head; temp != NULL; temp=temp->next)
        insertEnd(newlist,temp->data);
    printf("\nTEST COPY\n");
    for(temp=newlist->head; temp!=NULL; temp=temp->next)
        printf("%d ",temp->data);
    return newlist;
}

/*

 * concatenate: concatenates the second list to the first one
 */
void concatenate(DoublyLinkedList*  list1, DoublyLinkedList*  list2)
{
    /* TODO: ADD YOUR CODE HERE */
    Node* temp;
    temp=list1->head;
    while(temp->next!=NULL)
    {
        temp=temp->next;
    }
    temp->next=list2->head;
    list2->head->prev=temp;
}
/*
 * getDifferenceBetweenLists: get all elements in the first list that don't exist in  the second one.
 */
int isFound(int value, DoublyLinkedList*  list2)
{
    int flag=0;
    Node* q=list2->head;

    while(q!=NULL)
    {

        if(q->data==value)
        {
            flag=1;
            break;
        }
        return flag;
    }
}
DoublyLinkedList* getDifferenceBetweenLists(DoublyLinkedList*  list1, DoublyLinkedList*  list2)
{
    DoublyLinkedList *newlist = init();
 if (list1->head==NULL ||list2->head==NULL)
 {
 return newlist;
 }
 else{
// bubbleSort(list1);
 //bubbleSort(list2);
 Node *temp1=list1->head;
 while(temp1!=NULL)
 {
 if(Existence(list2,temp1->data)==1)
 {

 temp1=temp1->next;

 }
 else
 {
 toapp(newlist,temp1->data);
 temp1=temp1->next;
 }

 }
 }
 return newlist;
}

size_t length(DoublyLinkedList*  list)
{
    size_t count = 0;
 if(list->head==NULL)
 {

 return count;
 }
 else {
 Node* temp=list->head;
 while(temp!=NULL)
 {
 count++;
 temp=temp->next;
 }
 }

 return count;
}
/*
 * checkSumofFirstHalfEqualSumOfSecondHalf: check  if sum of first n/2 elements equals sum of the last n/2 elements.
 */
int checkSumofFirstHalfEqualSumOfSecondHalf(DoublyLinkedList*  list)
{
    /* TODO: ADD YOUR CODE HERE */
    int sumLeft=0;
    int sumRight=0;
    int n = length(list);

    if(n%2!=0)
        return 0;

    for(int i=0; i<n/2; i++)
    {
        sumLeft+=list->head->data;
        list->head=list->head->next;
    }
    for(int j=n; j>n/2; j--)
    {
        sumRight+=list->tail->data;
        list->tail=list->tail->prev;
    }
    if(sumLeft==sumRight)
        return 1;
    else
        return 0;
}

/*
 * isPalindrome: returns 1 if list is palindrome
 *               returns 0 if list is not palindrome
 *               a palindrome prints forwards as backwards
 *               e.g., 1 2 3 2 1
 *               e.g., 1 2 3 3 2 1
 */
int isPalindrome(DoublyLinkedList * list)
{
    /* TODO: ADD YOUR CODE HERE */
    if(list->head==NULL)
        return 1;
    while(list->head!=list->tail)
    {
        if(list->head->data!=list->tail->data)
            return 0;
        list->head=list->head->next;
        list->tail=list->tail->prev;
    }
    return 0;

}

/*
 * areEqual: returns 1 if both lists contain same elements
 *               returns 0 otherwise
 */
int areEqual(DoublyLinkedList*  list1, DoublyLinkedList*  list2)
{
    /* TODO: ADD YOUR CODE HERE */

    Node* p=list1->head;
    Node* q=list2->head;
    while(p!=NULL&&q!=NULL)
    {
        if(p->data==q->data)
        {

            p=p->next;
            q=q->next;
            return 1;
        }
        else
            return 0;
    }
}
/*
 * printlnListForward: prints the list {1, 3, 5, 7} as 1 3 5 7
 *                    prints end of line at the end
 */
void printlnListForward(DoublyLinkedList * list)
{
    /* TODO: ADD YOUR CODE HERE */

    Node * temp=list->head;
    while(temp!=NULL)
    {
        printf("%d ",temp->data);
        temp=temp->next;
    }
    printf("\n");
}
/*
 * printlnListBackward: prints the list {1, 3, 5, 7} as 7 5 3 1
 *                    prints end of line at the end
 */
void printlnListBackward(DoublyLinkedList * list)
{
    /* TODO: ADD YOUR CODE HERE */
    Node * temp=list->tail;
    while(temp!=NULL)
    {
        printf("%d",temp->data);
        temp=temp->prev;
    }

    printf("\n");
}
/*
 *
 */
void Investigate(char* title, DoublyLinkedList * list)
{
    printf("%s\n", title);
    printf("List =         ");
    printlnListForward(list);
    printf("Reverse List = ");
    printlnListBackward(list);
    printf("List Length = %u\n", length(list));
    printf("List isPalindrome = %d\n", isPalindrome(list));
    printf("...................................................\n");
}
/*
 *
 */
void testConcatenate1(DoublyLinkedList *list1)
{
    puts("\nSTART testConcatenate1\n");
    DoublyLinkedList * EmptyList =init();

    DoublyLinkedList* list3,*emptyList1;
    list3 = copy(list1);
    Investigate("List3 = copy(List1)\n==================", list3);
    puts("\nMenna \n");
    puts("menna");
    emptyList1 = copy(EmptyList);
    Investigate("EmptyList1 = copy(EmptyList)\n===========================", EmptyList);
    concatenate(list3, emptyList1);
    Investigate("List3<->EmptyList1\n==========================", list3);
    destroy(list3);
    Investigate("List3 (after destroy)\n=====================", list3);
    destroy(emptyList1);
    puts("\nEND testConcatenate1\n");
}
/*
 *
 */
void testConcatenate2(DoublyLinkedList * list1)
{
    puts("\nSTART testConcatenate2\n");
    DoublyLinkedList * EmptyList =init();
    DoublyLinkedList * list3, * emptyList1;
    list3 = copy(list1);
    Investigate("List3 = copy(List1)\n==================", list3);
    emptyList1 = copy(EmptyList);
    Investigate("EmptyList1 = copy(EmptyList)\n===========================", EmptyList);
    concatenate(emptyList1, list3);
    Investigate("EmptyList1<->List3\n==========================", emptyList1);
    destroy(emptyList1);
    Investigate("EmptyList1 (after destroy)\n=====================", emptyList1);
    puts("\nEND testConcatenate2\n");

}
/*

void testConcatenate3(DoublyLinkedList *list1, DoublyLinkedList *list2)
{
    puts("\nSTART testConcatenate3\n");
    DoublyLinkedList* list3, list4, emptyList1;
    list3 = copy(list1);
    Investigate("List3 = copy(List1)\n==================", list3);
    list4 = copy(list2);
    Investigate("list4 = copy(List2)\n==================", list4);
    concatenate(list3, list4);
    Investigate("List3<->List4\n=====================", list3);
    destroy(list3);
    Investigate("list3 (after destroy)\n=====================", list3);
    puts("\nEND testConcatenate3\n");

}
*/

void testConcatenate()
{
    int array1[] = {0, 1, 2, 3, 4, 5, 6};
    int array2[] = {7, 8, 9};

    DoublyLinkedList *list1 = convertArrayToDoublyLinkedList(array1, sizeof(array1)/sizeof(*array1));
    Investigate("List1\n=====", list1);
    DoublyLinkedList *list2 = convertArrayToDoublyLinkedList(array2, sizeof(array2)/sizeof(*array2));
    Investigate("List2\n=====", list2);

    testConcatenate1(list1);
    testConcatenate2(list1);
//    testConcatenate3(list1, list2);

    destroy(list1);
    destroy(list2);
}
/*
 *
 */
void testPalindrome()
{
    puts("\nSTART testPalindrome\n");
    int array3[] = {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1, 0};
    int array4[] = {7, 8, 9, 9, 8, 7};

    DoublyLinkedList* list5 = convertArrayToDoublyLinkedList(array3, sizeof(array3)/sizeof(*array3));
    puts("menna");
    Investigate("List5\n=====", list5);
    puts("menna");
    DoublyLinkedList *list6 = convertArrayToDoublyLinkedList(array4, sizeof(array4)/sizeof(*array4));
    puts("menna");
    Investigate("List6\n=====", list6);
    puts("menna");

    destroy(list5);
    destroy(list6);
    puts("\nEND testPalindrome\n");

}
/*
 *
 */
void testAreEqual()
{
    puts("\nSTART testAreEqual\n");
    int array7[] = {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1, 0};
    int array8[] = {7, 8, 9, 9, 8, 7};
    int array9[] = {0, 1, 2, 3, 4, 5};
    DoublyLinkedList * EmptyList =init();
    DoublyLinkedList *list7 = convertArrayToDoublyLinkedList(array7, sizeof(array7)/sizeof(*array7));
    Investigate("List7\n=====", list7);
    DoublyLinkedList *list8 = convertArrayToDoublyLinkedList(array8, sizeof(array8)/sizeof(*array8));
    Investigate("List8\n=====", list8);
    DoublyLinkedList *list9 = convertArrayToDoublyLinkedList(array9, sizeof(array9)/sizeof(*array9));
    Investigate("List9\n=====", list9);
    DoublyLinkedList *emptyList1 = copy(EmptyList);
    Investigate("EmptyList1 = copy(EmptyList)\n===========================", emptyList1);
    DoublyLinkedList *emptyList2 = copy(EmptyList);
    Investigate("EmptyList2 = copy(EmptyList)\n===========================", emptyList2);

    printf("areEqual(list7, list7) = %d\n", areEqual(list7, list7));
    printf("areEqual(list7, list8) = %d\n", areEqual(list7, list8));
    printf("areEqual(list7, list9) = %d\n", areEqual(list7, list9));
    printf("areEqual(list8, list7) = %d\n", areEqual(list8, list7));
    printf("areEqual(list7, EmptyList1) = %d\n", areEqual(list7, emptyList1));
    printf("areEqual(EmptyList1, list7) = %d\n", areEqual(emptyList1, list7));
    printf("areEqual(EmptyList1, EmptyList2) = %d\n", areEqual(emptyList1, emptyList2));

    destroy(list7);
    destroy(list8);
    destroy(list9);
    puts("\nEND testAreEqual\n");

}
/*
 *
 */
void testDifference()
{
    puts("\nSTART testDifference\n");
    int array10[] = {2, 4, 8, 9, 13, 17,20};
    int array11[] = {2, 8, 17,20};
    DoublyLinkedList *list10 = convertArrayToDoublyLinkedList(array10, sizeof(array10)/sizeof(*array10));
    Investigate("list10\n=====", list10);
    DoublyLinkedList *list11 =convertArrayToDoublyLinkedList(array11, sizeof(array11)/sizeof(*array11));
    Investigate("List11\n=====", list11);
    DoublyLinkedList *list12 = getDifferenceBetweenLists(list10,list11);
    Investigate("list12\n=====", list12);
    destroy(list10);
    destroy(list11);
    destroy(list12);
    puts("\nEND testDifference\n");

}
void testSum()
{
    puts("\nSTART testSum\n");
    int array5[] = {12, 4, 8, 9, 13, 2};
    int array6[] = {2, 18, 17,4};
    int array7[]= {2,3,4};
    DoublyLinkedList *list13 = convertArrayToDoublyLinkedList(array5, sizeof(array5)/sizeof(*array5));
    Investigate("list13\n=====", list13);
    DoublyLinkedList *list14 =convertArrayToDoublyLinkedList(array6, sizeof(array6)/sizeof(*array6));
    Investigate("list14\n=====", list14);
    DoublyLinkedList *list15 =convertArrayToDoublyLinkedList(array7, sizeof(array7)/sizeof(*array7));
    Investigate("list15\n=====", list15);
    printf("checkSumofFirstHalfEqualSumOfSecondHalf(list13) = %d\n", checkSumofFirstHalfEqualSumOfSecondHalf(list13));
    printf("checkSumofFirstHalfEqualSumOfSecondHalf(list14) = %d\n", checkSumofFirstHalfEqualSumOfSecondHalf(list14));
    printf("checkSumofFirstHalfEqualSumOfSecondHalf(list15) = %d\n", checkSumofFirstHalfEqualSumOfSecondHalf(list15));

    destroy(list13);
    destroy(list14);
    destroy(list15);
    puts("\nEND testSum\n");
}
main()
{
    //testConcatenate();
    //testPalindrome();
    //testAreEqual();
    //testDifference();
    //testSum();
     testDifference();


    return 0;
}
