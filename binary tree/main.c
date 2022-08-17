#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char data[20];
    struct node *left;
    struct node *right;
} node;

node* NewNode(char* key)
{
    node* n=malloc(sizeof(node));
    strcpy(n->data,key);
    n->left=NULL;
    n->right=NULL;
    return n;
}
node* insert(node* node, char* key)
{
    if (node == NULL)
        return NewNode(key);
    else if (strcasecmp(key,node->data)<0)
    {
        node->left= insert(node->left, key);
        //printf("left\n");
    }
    else
    {
        node->right = insert(node->right, key);
       // printf("right\n");
    }
    return node;
}
int count (node* root)
{
    if(root==NULL)
        return 0;
    else
        return 1+count(root->left)+count(root->right);
}
int max(int a, int b)
{
    return a>b?a:b;
}
int height (node* root)
{
    if(root==NULL)
        return -1;
    else
        return 1+max(height(root->left),height(root->right));
}
node* ReadFromFile(node* root)
{
    char s[50];
    FILE* f=fopen("EN-US-Dictionary.txt","r");
    if(f==NULL)
        printf("File not found \n");
    else
    {
        while(!feof(f))
        {
            fscanf(f,"%s",s);
           root= insert(root,s);

        }
        printf("Dictionary loaded successfully\n");
        printf("Size=%d\n",count(root));
        printf("Height=%d\n",height(root));


    }
    return root;
}
node* SubSearch(node* root, char* key)
{
    if (root==NULL)
        return NULL;
    if (strcasecmp(key,root->data)==0)
        return root;
    else if(strcasecmp(key,root->data)<0)
        return SubSearch(root->left,key);
    else
        return SubSearch(root->right,key);
}
node* GetLeaf(node* root, char*key)
{
    while(root!=NULL)
    {
        if(strcasecmp(key,root->data)<0)
        {
            if(root->left==NULL)
                return root;
            else
                root=root->left;
        }
        else if (strcasecmp(key,root->data)>0)
        {
            if(root->right==NULL)
                return root;
            else
                root=root->right;
        }
    }
}

node* FindMin(node *root)
{
    if(root==NULL)
        return NULL;
    else if(root->left!=NULL)
        return FindMin(root->left);
    else
        return root;
}

node* FindMax(node *root)
{
    if(root==NULL)
        return NULL;
    else if(root->right!=NULL)
        return FindMax(root->right);
    else
        return root;
}

node* GetSucessor(node* n,node* root)
{
    if( n->right != NULL )
        return FindMin(n->right);
    node *succ = NULL;
    while (root != NULL)
    {
        if (strcasecmp(n->data,root->data)<0)
        {
            succ = root;
            root = root->left;
        }
        else if (strcasecmp(n->data,root->data)>0)
            root = root->right;
        else
            break;
    }
    return succ;
}
node* GetPredecessor(node* n,node* root)
{
    if( n->left != NULL )
        return FindMax(n->left);
    node *pre = NULL;
    while (root != NULL)
    {
        if (strcasecmp(n->data,root->data)>0)
        {
            pre = root;
            root = root->right;
        }
        else if (strcasecmp(n->data,root->data)<0)
            root = root->left;
        else
            break;
    }
    return pre;
}

void Search(node* root,char*key)
{
    node* leaf;
    node* succ;
    node* pre;

    if(SubSearch(root,key)!=NULL)
        printf("%s  Correct spelling\n",key);
    else
    {
        printf("%s Incorrect spelling!\n Here are a few suggestions :\n",key);
        leaf= GetLeaf(root,key);
        succ=GetSucessor(leaf,root);
        pre= GetPredecessor(leaf,root);
        printf("%s\n%s\n%s\n",leaf->data,pre->data,succ->data);
    }
}
int main()
{
    node *root =NULL;
    char statement [50];
    node* temp ;
    root= ReadFromFile(root);
    printf("Enter a sentence\n");
    gets(statement);
    char* token = strtok(statement," ");
    while(token!=NULL)
    {
        Search(root,token);
        token=strtok(NULL," ");
    }



    return 0;
}
