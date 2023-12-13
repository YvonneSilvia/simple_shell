#include "shell.h"
/**
*_free_list - frees a linked list
*@head: - - pointer param to first node
*Return: - returns nothing
*/
void _free_list(list_t **head_ptr)
{
	list_t *node, *head, *next;

	if (!head_ptr || !*head_ptr)
		return;
	head  = *head_ptr;
	node = head;
	while (node)
	{
		next = node->next;
		free(node->str);
		free(node);
		node = next;
	}
	*head_ptr = NULL;
}
/**
*_add_node_end - adds a node at the end of a list
*@head: - first node of a list
*@str: - node of strings param
*@num: - number of data fields
*Return: - returns pointer to new node
*/
list_t *add_node_at_end(list_t **head, const char *str, int num)
{
	list_t *node, *new_node;

	if (!head)
		return (NULL);
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	new_node->num = num;
	new_node->str = str ? _strdup(str) : NULL;
	new_node->next = NULL;
	if (*head)
	{
		node = *head;
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}
/**
*_delete_at_someindex - deletes a node at a given position
*@head: first node
*@index: - position of the node
*Return: - returns1 success 0 invalid or empty list
*/
int delete_node_at_someindex(list_t **head, unsigned int index)
{
	list_t *node = *head, *prev = NULL;

	if (!head || !*head)
		return (0);
	if (!index)
	{
		*head = node->next;
		free(node->str);
		free(node);
		return (1);
	}
	while (node && index--)
	{
		prev = node;
		node = node->next;
	}
	if (node)
	{
		prev->next = node->next;
		free(node->str);
		free(node);
		return (1);
	}
	return (0);
}
/**
*_add_node - adds a node
*@head: - first node
*@str: - string node
*@num: - number of nodes
*Return: - returns a pointer to new node
*/
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_node;

	if (!head)
		return (NULL);
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	new_node->num = num;
	new_node->str = str ? _strdup(str) : NULL;
	new_node->next = *head;
	*head = new_node;
	return (new_node);
}
/**
*_print_list_str - prints node strings
*@head: - first node
*Return: - returns the size of list
*/
size_t _print_list_str(const list_t *head)
{
	size_t i = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		i++;
	}
	return (i);
}
