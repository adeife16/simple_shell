#include "main.h"

/**
 * addSeparatorNodeEnd - adds a separator found at the end
 * of a list_sep.
 * @head: head of the linked list.
 * @sep: separator found (; | &).
 * Return: address of the head.
 */
list_sep *addSeparatorNodeEnd(list_sep **head, char sep)
{
    list_sep *newNode, *tempNode;

    newNode = malloc(sizeof(list_sep));
    if (newNode == NULL)
      return (NULL);

    newNode->separator = sep;
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
 * freeSeparatorList - frees a list_sep
 * @head: head of the linked list.
 * Return: no return.
 */
void freeSeparatorList(list_sep **head)
{
    list_sep *tempNode;
    list_sep *currentNode;

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

/**
 * addCommandLineNodeEnd - adds a command line at the end
 * of a list_line.
 * @head: head of the linked list.
 * @line: command line.
 * Return: address of the head.
 */
list_line *addCommandLineNodeEnd(list_line **head, char *line)
{
    list_line *newNode, *tempNode;

    newNode = malloc(sizeof(list_line));
    if (newNode == NULL)
      return (NULL);

    newNode->line = line;
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
 * freeLineList - frees a list_line
 * @head: head of the linked list.
 * Return: no return.
 */
void freeLineList(list_line **head)
{
    list_line *tempNode;
    list_line *currentNode;

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
