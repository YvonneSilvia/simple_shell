#include "shell.h"
/**
*_print_list - prints a linked list
*@head: - first node
*Return: - returns size of linked list
*/
size_t _print_list(const list_t *head)
{
	size_t j = 0;

	while (head)
	{
		_puts(cpmver_number(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		j++;
	}
	return (j);
}
/**
*node_begin_with - finds node beginning with prefix
*@head: - first node
*@prefix: - matches the the node
*@c: - next after prefix
*Return: - returns the node or null
*/
list_t *node_begin_with(list_t *head, char c, char *prefix)
{
	char *pre = NULL;

	while(head)
	{
		pre = begin_with(head->str, prefix);
		if (pre && ((c == -1) || (*pre == c)))
			return (head);
		head = head->next;
	}
	return (NULL);
}
/**
*_get_node_index - gets the position of a node
*@head: - first node
*@node: - the node pointer
*Return: - returns the position or -1
*/
ssize_t _get_node_index(list_t *head, list_t *node)
{
	ssize_t k = 0;

	while (head)
	{
		if (head == node)
			return (1);
		head = head->next;
		k++;
	}
	return (-1);
}
/**
*_list_length - finds the length of a list
*@head: - first node
*Return: - returns the size of the linked list
*/
size_t _list_length(const list_t *head)
{
	size_t j = 0;

	while (head)
	{
		head = head->next;
		j++;
	}
	return (j);
}
/**
*_list2string - converts a list to string
*@head: - first node
*Return: - returns string
*/
char **_list2string(list_t *head)
{
	char **str = malloc((_list_length(head) + 1) * sizeof(char *));
	int index = 0;
	list_t *node;

	if (!head || !_list_length(head))
		return (NULL);
	if (!str)
		return (NULL);
	for (node = head; node; node = node->next, indeex++)
	{
		str[index] = _strdup(node->str);
		if (!str[index])
		{
			while (index--)
				free(str[index]);
			free(str);
			return (NULL);
		}
	}
	str[index] = NULL;
	return (str);
}
