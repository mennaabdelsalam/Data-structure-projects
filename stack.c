#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include<conio.h>
#include<ctype.h>

#define TYPE float
#define STACKSIZE 1000

typedef struct
{
    int top ;
    TYPE items[STACKSIZE];
} Stack;

Stack *initialize ()
{
    Stack*s=(Stack*)malloc(sizeof(Stack));
    s->top=-1;
}
TYPE top(Stack *s)
{
    return (s->items[s->top-1]);
}
void push(Stack *s, TYPE val)
{

    s->items[++s->top]=val;
}
TYPE pop(Stack *s)
{
    return (s->items[s->top--]);

}
int isEmpty(Stack *s)
{
    return(s->top==-1?1:0);
}


int isOperator(char *c)
{
    if (c=='+'|| c=='-'|| c=='*'|| c=='/' || c=='%'|| c=='^')
        return 1;
    return 0;
}

int precedence (char x)
{
    switch(x)
    {
    case '+':
    case '-':
        return 1;
        break;
    case '^':
        return 3;
        break;
    case '*':
    case '/':
        return 2;
        break;

    }
}
void infixToPostfix(char* infix,char* postfix)
{
    Stack* s= initialize();
    *(infix+strlen(infix)-1)='\0';
    char c=' ';
    char* token=strtok(infix," ");
    while(*token!=NULL)
    {
        if (isdigit(token))
        {
            printf("%s\n\n",token);
            strcat(postfix,token);
            strcat(postfix," ");
        }
        else if (*token == ')')
        {
            while(top(s)!='(')
            {
                *(postfix+strlen(postfix))=pop(s);
                *(postfix+strlen(postfix))='\0';
                strcat(postfix," ");
            }
            pop(s);
        }
        else
        {
            while(!isEmpty(s) && top(s)!='(' && precedence(*token)<=precedence(top(s)))
            {
                char b=pop(s);
                if(b!='(')
                    *(postfix+strlen(postfix))=b;
                *(postfix+strlen(postfix))='\0';
                strcat(postfix," ");
            }
            push(s,*token);

        }
        token=strtok(NULL," ");
    }
    while(!isEmpty(s))
    {
        *(postfix+strlen(postfix))=pop(s);
        *(postfix+strlen(postfix))='\0';
        strcat(postfix," ");
    }
    *(postfix+strlen(postfix)-1)='\0';
}
TYPE evaluatePostfix(char* postfix)
{
    Stack *s=initialize();
    char *token=strtok(postfix," ");
    while (token!=NULL)
    {


        if(isdigit(token))
        {
            float t =atof(token);
            push(s,t);

        }
        else
        {
            float op1=pop(s);
            float op2=pop(s);
            switch(*token)
            {
            case '+':
                push(s,op2+op1);
                break;
            case '-':
                push(s,op2-op1);
                break;
            case '*':
                push(s,op2*op1);
                break;
            case '/':
                push(s,op2/op1);
                break;
            case '^':
                push(s,pow(op2,op1));
            default:
                printf("ERROR");
                return -1;
                break;
            }
        }
        token=strtok(NULL," ");
    }
    return pop(s);
}

main(int argc, char**argv)
{
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
