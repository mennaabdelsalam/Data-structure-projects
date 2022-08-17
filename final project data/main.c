#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include<math.h>
#define  MAXCHAR 1000


// A structure to represent a stack
struct Stack_double {
	double data;
	struct Stack_double* next;
};

struct Stack_double* newNodeDouble(double data)
{
	struct Stack_double* stk = (struct Stack_double*)malloc(sizeof(struct Stack_double));
	stk->data = data;
	stk->next = NULL;
	return stk;
}

double isEmptyDouble(struct Stack_double* root)
{
	return !root;
}

void pushDouble(struct Stack_double** root, double data)
{
	struct Stack_double* stk = newNodeDouble(data);
	stk->next = *root;
	*root = stk;
}

bool popDouble(struct Stack_double** root)
{
	if (isEmptyDouble(*root))
		return false;
	struct Stack_double* temp = *root;
	*root = (*root)->next;
	free(temp);

	return true;
}

double peekDouble(struct Stack_double* root)
{
	if (isEmptyDouble(root))
		return -1;
	return root->data;
}

void deleteStackDouble(struct Stack_double** root)
{
	struct Stack_double* ptr = *root;
	struct Stack_double* tmp;
	while (ptr != NULL)
	{
		tmp = ptr->next;
		free(ptr);
		ptr = tmp;
	}
	*root = NULL;
}

// A structure to represent a stack
struct Stack_string {
	char data[10];
	struct Stack_string* next;
};

struct Stack_string* newNodeStr(char* data)
{
	struct Stack_string* stk = (struct Stack_string*)malloc(sizeof(struct Stack_string));
	strcpy(stk->data, data);
	stk->next = NULL;
	return stk;
}

double isEmptyStr(struct Stack_string* root)
{
	return !root;
}

void pushStr(struct Stack_string** root, char* data)
{
	struct Stack_string* stk = newNodeStr(data);
	stk->next = *root;
	*root = stk;
}

bool popStr(struct Stack_string** root)
{
	if (isEmptyStr(*root))
		return false;
	struct Stack_string* temp = *root;
	*root = (*root)->next;
	free(temp);

	return true;
}

char* peekStr(struct Stack_string* root)
{
	if (isEmptyStr(root))
		return -1;
	return root->data;
}

void deleteStackStr(struct Stack_string** root)
{
	struct Stack_string* ptr = *root;
	struct Stack_string* tmp;
	while (ptr != NULL)
	{
		tmp = ptr->next;
		free(ptr);
		ptr = tmp;
	}
	*root = NULL;
}

struct node
{
	char key;
	double value;
	struct node* left, * right;
};

struct Pair
{
	char key;
	double value;
};

int bstSize(struct node* node)
{
	if (node == NULL)
		return 0;
	else
		return(bstSize(node->left) + 1 + bstSize(node->right));
}

// C function to search a given key in a given BST
struct node* search(struct node* root, char key)
{
	// Base Cases: root is null or key is present at root
	if (root == NULL || root->key == key)
		return root;

	// Key is greater than root's key
	if (root->key < key)
		return search(root->right, key);

	// Key is smaller than root's key
	return search(root->left, key);
}

// A utility function to create a new BST node
struct node* newNode(char item, double val)
{
	struct node* temp = (struct node*)malloc(sizeof(struct node));
	temp->key = item;
	temp->value = val;
	temp->left = temp->right = NULL;
	return temp;
}

// A utility function to do inorder traversal of BST
void inorder(struct node* root)
{
	if (root != NULL)
	{
		inorder(root->left);
		printf("%c = %.2lf\n", root->key, root->value);
		inorder(root->right);
	}
}

/* A utility function to insert a new node with given key in BST */
struct node* insert(struct node* node, char key, double val)
{
	/* If the tree is empty, return a new node */
	if (node == NULL) return newNode(key, val);

	/* Otherwise, recur down the tree */
	if (key < node->key)
		node->left = insert(node->left, key, val);
	else if (key > node->key)
		node->right = insert(node->right, key, val);

	/* return the (unchanged) node podoubleer */
	return node;
}

void copyBSTToArray(struct node* root, struct Pair* arr, int* idx)
{
	if (root == NULL)
		return;

	arr[*idx].key = root->key;
	arr[*idx].value = root->value;
	(*idx)++;

	copyBSTToArray(root->left, arr, idx);
	copyBSTToArray(root->right, arr, idx);
}

// To heapify a subtree rooted with node i which is
// an index in arr[]. n is size of heap
void heapify(struct Pair arr[], int n, int i)
{
	int largest = i; // Initialize largest as root
	int l = 2 * i + 1; // left = 2*i + 1
	int r = 2 * i + 2; // right = 2*i + 2

	// If left child is larger than root
	if (l < n && arr[l].value > arr[largest].value)
		largest = l;

	// If right child is larger than largest so far
	if (r < n && arr[r].value > arr[largest].value)
		largest = r;

	// If largest is not root
	if (largest != i)
	{
		struct Pair temp = arr[largest];
		arr[largest] = arr[i];
		arr[i] = temp;
		// Recursively heapify the affected sub-tree
		heapify(arr, n, largest);
	}
}

// main function to do heap sort
void heapSort(struct Pair arr[], int n)
{
	// Build heap (rearrange array)
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	struct Pair temp;

	// One by one extract an element from heap
	for (int i = n - 1; i > 0; i--)
	{
		// Move current root to end
		temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;

		// call max heapify on the reduced heap
		heapify(arr, i, 0);
	}
}

/*  This function traverses tree in post order to
	to delete each and every node of the tree */
void deleteTree(struct node* node)
{
	if (node == NULL) return;

	/* first delete both subtrees */
	deleteTree(node->left);
	deleteTree(node->right);

	/* then delete the node */
	free(node);
}


int precedence(char symbol)
{
	if (symbol == '^')/* exponent operator, highest precedence*/
	{
		return(3);
	}
	else if (symbol == '*' || symbol == '/')
	{
		return(2);
	}
	else if (symbol == '+' || symbol == '-')          /* lowest precedence */
	{
		return(1);
	}
	else
	{
		return(0);
	}
}

bool isOperator(char symbol)
{
	return (symbol == '^' || symbol == '*' || symbol == '/' || symbol == '+' || symbol == '-');
}
double performOperation(double d1, double d2, char opr)
{
	switch (opr)
	{
	case '*':
		return d1 * d2;
	case '/':
		return d1/d2;
	case '+':
		return d1 + d2;
	case '-':
		return d1 - d2;
	case '^':
		return pow(d1,d2);
	}
	return 0;
}
int findChar(const char* str, int len, char c)
{
	for (int i = 0; i < len; i++)
		if (str[i] == c)
			return i;
	return -1;
}
bool isValidExpression(char *str)
{
	int len = strlen(str);
	int pos;
	//Check '=' availability
	pos = findChar(str,len,'=');
	if (pos == -1)
		return false;

	//Invalid LHS
	if (pos != 1)
		return false;

	//Invalid LHS-Symbol
	if (isalpha(str[0]) == 0)
		return false;



	return true;
}
void removeWhiteSpaces(char input[])
{
	int i, j;
	char* output = input;
	for (i = 0, j = 0; i < strlen(input); i++, j++)
	{
		if (input[i] != ' ')
			output[j] = input[i];
		else
			j--;
	}
	output[j] = '\0';
}
bool evaluateExpression(char *infix, double* value,struct node*bstRoot)
{
	char* end;
	struct Stack_double* stk_db = NULL;
	struct Stack_string* stk_str = NULL;
	double num;
	double num1;
	char ch;
	struct node* tmpBSTNode;

	pushStr(&stk_str, "(");
	strcat(infix, ")");

	while (infix[0] != '\0')
	{
		if (isalpha(infix[0])!=0)
		{
			//Variable
			tmpBSTNode = search(bstRoot, infix[0]);
			if (tmpBSTNode == NULL)
			{
				deleteStackDouble(&stk_db);
				deleteStackStr(&stk_str);
				return false;
			}
			pushDouble(&stk_db, tmpBSTNode->value);
			infix++;
		}
		else if (isdigit(infix[0]) != 0)
		{
			//Constant
			num = strtod(infix, &end);
			infix = end;
			pushDouble(&stk_db, num);
		}
		else if (infix[0] == '(')
		{
			//Opening Braces
			ch = infix[1];
			infix[1] = '\0';
			pushStr(&stk_str, infix);
			infix[1] = ch;
			infix = infix + 1;
		}
		else if (infix[0] == ')')
		{
			//Closing Braces
			if (isEmptyStr(stk_str))
			{
				deleteStackDouble(&stk_db);
				return false;
			}

			if (peekStr(stk_str)[0] == '(')
			{
				infix = infix + 1;
				popStr(&stk_str);
			}
			else
			{
				ch = peekStr(stk_str)[0];
				popStr(&stk_str);
				//Top Double
				if (isEmptyDouble(stk_db) == true)
				{
					deleteStackStr(&stk_str);
					return false;
				}
				num = peekDouble(stk_db);
				popDouble(&stk_db);

				//Second Top Double
				if (isEmptyDouble(stk_db) == true)
				{
					deleteStackStr(&stk_str);
					return false;
				}
				num1 = peekDouble(stk_db);
				popDouble(&stk_db);

				pushDouble(&stk_db, performOperation(num1, num, ch));
			}
		}
		else if (isOperator(infix[0]))
		{
			//Operator
			if (isEmptyStr(stk_str) != 0)
			{
				ch = peekStr(stk_str)[0];

				if (isOperator(ch) == true &&
					precedence(ch) > precedence(infix[0]))
				{
					//Top Double
					if(isEmptyDouble(stk_db)==true)
					{
						deleteStackStr(&stk_str);
						return false;
					}
					num = peekDouble(stk_db);
					popDouble(&stk_db);

					//Second Top Double
					if (isEmptyDouble(stk_db) == true)
					{
						deleteStackStr(&stk_str);
						return false;
					}
					num1 = peekDouble(stk_db);
					popDouble(&stk_db);

					pushDouble(&stk_db, performOperation(num1, num, ch));
					popStr(&stk_str);
				}
				else
				{
					ch = infix[1];
					infix[1] = '\0';
					pushStr(&stk_str, infix);
					infix[1] = ch;
					infix = infix + 1;
				}
			}
			else
			{
				ch = infix[1];
				infix[1] = '\0';
				pushStr(&stk_str, infix);
				infix[1] = ch;
				infix = infix + 1;
			}

		}
	}

	if (isEmptyDouble(stk_db) == 1 || isEmptyStr(stk_str) == 0)
	{
		deleteStackDouble(&stk_db);
		deleteStackStr(&stk_str);
		return false;
	}

	*value = peekDouble(stk_db);
	deleteStackDouble(&stk_db);
	deleteStackStr(&stk_str);
	return true;
}





int main() {
	double val = 0;;
	FILE* fp;
	char str[MAXCHAR];
	char* filename = "input.txt";
	int count = 0;
	char *infix;
	bool validExp = true;
	int lineNo = 0;
	char variable;
	struct node* bstRoot = NULL;



	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Could not open file %s", filename);
		return 1;
	}


	while (fgets(str, MAXCHAR, fp) != NULL && validExp==true)
	{
		lineNo++;
		removeWhiteSpaces(str);
		validExp = isValidExpression(str);

		if (validExp)
		{
			printf("%s", str);
			char* token = strtok(str, "=");

			variable= token[0];
			token = strtok(NULL, "\n");
			if (evaluateExpression(token, &val, bstRoot) == false)
				validExp = false;
			else
			{
				bstRoot = insert(bstRoot, variable, val);
			}
		}
	}
	fclose(fp);

	if (validExp == false)
	{
		printf("Invalid Syntax On Line-%d", lineNo);
	}
	else
	{
		printf("\n\n");
		inorder(bstRoot);

		int size = bstSize(bstRoot);
		struct Pair* arr = (struct Pair*) malloc(sizeof(struct Pair) * size);
		int idx = 0;
		copyBSTToArray(bstRoot, arr,&idx);

		printf("\n\n");
		heapSort(arr, size);
		for (int i = 0; i < size; i++)
			printf("%c = %.2lf\n", arr[i].key, arr[i].value);

		free(arr);
		deleteTree(bstRoot);
	}

	return 0;
}



//int main()
//{
//	/*struct Stack_string* stk=NULL;
//	char str[] = "Hariss";
//	for (int i = 0; i < 10; i++)
//	{
//		pushStr(&stk, str);
//	}
//
//	while (isEmptyStr(stk)==false)
//	{
//		printf("%s\n", peekStr(stk));
//		popStr(&stk);
//	}*/
//
//
//	/*struct Stack_double* stk=NULL;
//	for (int i = 0; i < 10; i++)
//	{
//		pushDouble(&stk, i+1);
//	}
//
//	while (isEmptyDouble(stk)==false)
//	{
//		printf("%lf\n", peekDouble(stk));
//		popDouble(&stk);
//	}*/
//
//	return 0;
//}
