#include "shell.h"
/**
*_realloc - allocates more memory
*@ptr:- pointer to previously allocated block
*@old: - old memory block
*@new: - new memory block
*Return: - returns nothing
*/
void *_realloc(void *ptr, unsigned int old, unsigned int new)
{
	char *mem;

	mem = !ptr ? malloc(new) : !new ? (free(ptr), NULL)
	: new == old ? ptr : malloc(new);
	if (!mem || mem == ptr)
		return (mem);
	old = old < new ? old : new;
	while(old--)
		mem[old] = ((char *)ptr)[old];
	free(ptr);
	return (mem);
}
/**
*_ffree - frees string of string
*@str: - string param
*Return: - returns nothing
*/
void _ffree(char **str)
{
	int i;

	if (!str)
		return;
	for (i = 0; str[i]; i++)
		free(str[i]);
	free(str);
}
/**
*_memset - flls a block of memory with value
*@ptr: - pointer to memory
*@b: - byte to fill in memory
*@size: block size
*Return: - returns pointer to block of memory
*/
char *_memset(char *ptr, char b, unsigned int size)
{
	unsigned int i;

	for (i = 0; i < size; i++)
		*(ptr + i) = b;
	return (ptr);
}
