#include <stdio.h>
#include <stdlib.h>
#define bool int
  
struct s_node {
    char data;
    struct s_node* next;
};
  

void Push(struct s_node** top_ref, int new_data);
int Pop(struct s_node** top_ref);
bool IsMatchingPair(char character1, char character2);
bool AreBracketsBalanced(char arr[]);

int main()
{
    char arr[100] = "{()}[]";
  
    if (AreBracketsBalanced(arr))
        printf("Balanced ");
    else
        printf("Not Balanced ");
    return 0;
}

bool AreBracketsBalanced(char arr[])
{
    int i = 0;
  
    struct s_node* stack = NULL;
  
    while (arr[i]) 
    {
        if (arr[i] == '{' || arr[i] == '(' || arr[i] == '[')
        {
            push(&stack, arr[i]);
        }
  
        if (arr[i] == '}' || arr[i] == ')' || arr[i] == ']') 
        {
            if (stack == NULL)
            {
                return 0;
  			}
 
            else if (!IsMatchingPair(pop(&stack), arr[i]))
            {
                return 0;
            }
        }
        ++i;
    }
  
    if (stack == NULL)
    {
        return 1; 
    }
    
    return 0; 
}
bool IsMatchingPair(char character1, char character2)
{
    if (character1 == '(' && character2 == ')')
        return 1;
    else if (character1 == '{' && character2 == '}')
        return 1;
    else if (character1 == '[' && character2 == ']')
        return 1;
    else
        return 0;
}


  
void Push(struct s_node** top_ref, int new_data)
{
    struct s_node* new_node = (struct s_node*)malloc(sizeof(struct s_node));
  
    if (new_node == NULL) 
    {
        printf("Stack overflow n");
        getchar();
        exit(0);
    }
  
    new_node->data = new_data;
    new_node->next = (*top_ref);
    (*top_ref) = new_node;
}
  
int Pop(struct s_node** top_ref)
{
    char res;
    struct s_node* top;
  
    if (*top_ref == NULL) {
        printf("Stack overflow n");
        getchar();
        exit(0);
    }
    else {
        top = *top_ref;
        res = top->data;
        *top_ref = top->next;
        free(top);
        return res;
    }
}
