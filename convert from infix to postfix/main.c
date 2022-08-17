#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
/*
*
*/
#define TYPE float
#define STACKSIZE 1000
typedef struct {
    int top;
    TYPE items[STACKSIZE];
} Stack;
/*
*
*/

void err() {printf("Error in expression");exit(0);}

int isOperator(char *s)
{
   // if(*s == '+' || *s == '-' || *s == '' || *s == '/' )
        return 1;
    return 0;
}

int isNumber(char *s)
{
    while((*s)!='\0')
    {
        if(!(*s>='0' && *s<='9' || *s=='.'))
        {
            return 0;
        }
          s++;
    }
    return 1;
}

int parse(char *str)
{
    int len=-1;
    char *copyOfStr=str;
    while(*copyOfStr!='.'&&*copyOfStr!=NULL)
    {
        len++;copyOfStr++;
    }
    int result=0;
    while((*str)!=NULL)
    {
        if((*str)=='.')
        {
            str++;
        }

        else
        {
           result+=(*str-'0')*pow(10,len);
            str++;len--;
        }

    }
    return result;
}


int priority(char x)
    {
        switch(x)
        {
        case '+':
        case '-':return 1;break;
        case '#':return 4;break;
        case '*':
        case '/': return 2;break;
        case '(' : return 9;break;
        }
    }

int isLowerPriority(char x, char y)
    {
        return(priority(x)<priority(y)?1:0);
    }
void init(Stack *s) {
    s->top=0;
}
/*
*
*/
int isEmpty(Stack *s) {
    return(s->top==0?1:0);
}
/*
*
*/
TYPE top(Stack *s) {
    return (s->items[s->top-1]);
}
/*
*
*/
TYPE pop(Stack *s) {
    return (s->items[--s->top]);
return -1;
}
/*
*
*/
void push(Stack *s, TYPE val) {

    s->items[s->top++]=val;
}
/*
*
*/
void destroy(Stack *s) {
    free(s->items);
    free(s);
}
/*
* infixToPostfix: converts an expression in infix notation to
* to a postfix notation (Reverse-Polish
Notation)
* e.g., 2 + 3 --> 2 3 +
* e.g., (2 + 3) * 4 --> 2 3 + 4 *
*/
void infixToPostfix(char* infix, char* postfix)

{
    Stack s;
    init(&s);
    *(infix+strlen(infix)-1)='\0';
    char z = ' ';
    char *word=strtok(infix," ");
    while(word!=NULL)
    {
        if(isNumber(word))
        {
            printf("%s\n\n",word);
            strcat(postfix,word);
            strcat(postfix," ");
        }
        else if(*word==')')
        {
            while(top(&s)!='(')
            {
                *(postfix+strlen(postfix))=pop(&s);
                *(postfix+strlen(postfix))='\0';
                strcat(postfix," ");
            }
        }
        else
        {
          while(!isEmpty(&s) && top(&s)!='(' && priority(*word)<=priority(top(&s)))
                {char x=pop(&s); if (x!='(') (postfix+strlen(postfix))=x;(postfix+strlen(postfix))='\0';strcat(postfix," ");}
                push(&s,*word);
        }
        word=strtok(NULL," ");
    }
    while(!isEmpty(&s))
            {
                *(postfix+strlen(postfix))=pop(&s);
                *(postfix+strlen(postfix))='\0';
                strcat(postfix," ");
            }
            *(postfix+strlen(postfix)-1)='\0';
}





/*
* evaluatePostfix: Evaluates an expression in postfix notation
* (Reverse-Polish Notation)
*/
TYPE evaluatePostfix(char* postfix)
{
    Stack s;
    init(&s);
    char *word = strtok(postfix," ");
    while(word!=NULL)
    {

        if(isNumber(word))
        {
            float x=atof(word);
            push(&s,x);
        }
        else
        {
            if(*word=='#')
            {
                push(&s,-(pop(&s)));
            }
            else
            {
                float x1=pop(&s);
                float x2=pop(&s);
                switch(*word)
                {
                case '+':push(&s,x2+x1);break;
                case '-':push(&s,x2-x1);break;
                case '*':push(&s,x2*x1);break;
                case '/':push(&s,x2/x1);break;
                //default:printf("ERROR");return -1;break;
                }
            }
        }
        word=strtok(NULL," ");
    }
    return pop(&s);
}
/*
*
*/
main(int argc, char**argv) {
char infixExpr[256] = "";
char postfixExpr[256] = "";
printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
while(fgets(infixExpr, 255, stdin) != NULL)
{
infixToPostfix(infixExpr, postfixExpr);
printf("Postfix : %s\n", postfixExpr);

TYPE result = evaluatePostfix(postfixExpr);

printf("Result: %0.2f\n\n", result);

memset(postfixExpr,NULL,255);
printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
}
return 0;
}
