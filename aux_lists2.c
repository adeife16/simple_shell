#include "main.h"

/**
 * addRVarNode - adds a variable at the end
 * of a var_r list.
 * @head: head of the linked list.
 * @lenVar: length of the variable.
 * @val: value of the variable.
 * @lenVal: length of the value.
 * Return: address of the head.
 */
var_r *addRVarNode(var_r **head, int lenVar, char *val, int lenVal)
{
    var_r *newNode, *tempNode;

    newNode = malloc(sizeof(var_r));
    if (newNode == NULL)
      return (NULL);

    newNode->var_len = lenVar;
    newNode->value = val;
    newNode->val_len = lenVal;

    newNode->next = NULL;
    tempNode = *head;

    if (tempNode == NULL)
    {
      *head = newNode;
    }
    else
    {
      while (tempNode->next != NULL)
	tempNode = tempNode->next;
      tempNode->next = newNode;
    }

    return (*head);
}

/**
 * freeRVarList - frees a var_r list
 * @head: head of the linked list.
 * Return: no return.
 */
void freeRVarList(var_r **head)
{
    var_r *tempNode;
    var_r *currentNode;

    if (head != NULL)
    {
      currentNode = *head;
      while ((tempNode = currentNode) != NULL)
      {
	currentNode = currentNode->next;
	free(tempNode);
      }
      *head = NULL;
    }
}
