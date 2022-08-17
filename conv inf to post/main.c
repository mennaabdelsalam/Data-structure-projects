#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXSIZE 1000
/*
* Item: An item that is being pushed to or popped from the stack
* It may be float (to be used while evaluating the postfix)
* It may be char (to be used while converting infix to postfix)
*/
typedef union
{
    float fData;
    char  cData;
} Item;
/*
*
*/
typedef struct
{
    Item items[MAXSIZE];
    int top;
    /* TODO: ADD YOUR CODE HERE */
} Stack;
/*
*
*/
void init(Stack *s)
{
    s->top=0;
}

Stack * initialize()
{
    Stack *s = malloc(sizeof (Stack));
    s->top=0;
    return s;
/* TODO: ADD YOUR CODE HERE */
}
/*
*
*/
int isEmpty(Stack *s)
{

  if(s->top==0) return 1;
  else return 0;  /* TODO: ADD YOUR CODE HERE */
    return -1;
}
/*
*
*/
Item top(Stack *s)
{
    return s->items[s->top];
    /* TODO: ADD YOUR CODE HERE */
}
/*
*
*/
Item pop(Stack *s)
{
     return s->items[--s->top];
     /* TODO: ADD YOUR CODE HERE */
}
/*
*
*/
void push(Stack *s, Item val)
{
   s->items[s->top++]=val;
    /* TODO: ADD YOUR CODE HERE */
}
/* we should have a function to know the priority of operators for the conversion */

 int Priority (char *c)
  {
  if(c=='^')return 3;
  else if (c=='*' || c=='/')return 2;
  else if (c=='+' || c=='-')return 1;
  else return 0;
  }

/*
* infixToPostfix: converts an expression in infix notation to
* to a postfix notation (Reverse-Polish Notation)
* ASSUME single-digit operands
* ASSUME ^*+-/ operators
* e.g., 22+31 --> 22 31 +
* e.g., (2+3)*4 --> 2 3 + 4 *
*/
void infixToPostfix(char* infix, char* postfix)
{
     Stack s;
    char x,token;
    int i,j;
    init(&s);
    //Stack s=initialize();
    j=0;

    for(i=0;infix[i]!='\0';i++)
    {
        token=infix[i];
        if(isdigit(token))
            postfix[j++]=token;
        else
            if(token=='(')
               push(s,'(');
        else
            if(token==')')
                while((x=pop(&s))!='(')
                      postfix[j++]=x;
                else
                {
                    while(precedence(token)<=precedence(top(&s))&&!isempty(&s))
                    {
                        x=pop(&s);
                        postfix[j++]=x;
                    }
                    push(&s,token);
                }
    }

    while(!isempty(&s))
    {
        x=pop(&s);
        postfix[j++]=x;
    }

    postfix[j]='\0';
}/* TODO: ADD YOUR CODE HERE */
}
/*
* evaluatePostfix: Evaluates an expression in postfix notation
* (Reverse-Polish Notation)
* ASSUME single-digit operands
*/
float evaluatePostfix(char* postfix)
{
    /* TODO: ADD YOUR CODE HERE */
    return -1;
}
/*
*
*/
void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}
/*
*
*/
int main(int argc, char**argv)
{
    char infixExpr[256] = "";
    char postfixExpr[256] = "";
    printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    while(fgets(infixExpr, 255, stdin) != NULL)
    {
        replaceNewLineBySpace(infixExpr);
        infixToPostfix(infixExpr, postfixExpr);
        printf("Postfix : %s\n", postfixExpr);
        float result = evaluatePostfix(postfixExpr);
        printf("Result: %f\n\n", result);
        printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    }
    return 0;
}
